#include "page/node_page.h"

#include <assert.h>
#include <float.h>

#include "algorithm"
#include "exception/exceptions.h"
#include "field/fields.h"
#include "macros.h"
#include "os/os.h"
#include "settings.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

const PageOffset BLEAF_OFFSET = 12;
const PageOffset LEAF_OFFSET = 16;
const PageOffset USED_SLOT_OFFSET = 20;
const PageOffset KEY_LEN_OFFSET = 24;
const PageOffset KEY_TYPE_OFFSET = 28;

const PageOffset DATA_OFFSET = 0;

using namespace std;

NodePage::NodePage(Size nKeyLen, FieldType iKeyType, bool bLeaf)
    : LinkedPage(), _nKeyLen(nKeyLen), _iKeyType(iKeyType), _bLeaf(bLeaf) {
  // 基于自己实现的Store算法确定最大容量
  // 如果为中间结点，注意可能需要初始化第一个子结点
  CalculateCap();
  _bModified = true;
}

NodePage::NodePage(Size nKeyLen, FieldType iKeyType, bool bLeaf,
                   const std::vector<Field *> &iKeyVec,
                   const std::vector<PageSlotID> &iChildVec)
    : LinkedPage(),
      _nKeyLen(nKeyLen),
      _iKeyType(iKeyType),
      _bLeaf(bLeaf),
      _iKeyVec(iKeyVec),
      _iChildVec(iChildVec) {
  // 基于自己实现的Store算法确定最大容量
  CalculateCap();
  _bModified = true;
}

NodePage::NodePage(PageID nPageID) : LinkedPage(nPageID) {
  // 从格式化页面中导入结点信息
  // 确定最大容量
  Load();
  CalculateCap();
  _bModified = false;
}

NodePage::~NodePage() {
  // 将结点信息格式化并写回到页面中
  // 注意析构KeyVec中的指针
  if (_bModified) Store();
  for (Size i = 0; i < _iKeyVec.size(); ++i) delete _iKeyVec[i];
}

bool NodePage::Insert(Field *pKey, const PageSlotID &iPair) {
  _bModified = true;

  // 需要基于结点类型判断执行过程
  // 叶结点：
  // 1.确定插入位置后插入数据即可
  if (_bLeaf) {
    // 包含了empty的情况
    Size child_index = LowerBound(pKey);
    _iKeyVec.insert(_iKeyVec.begin() + child_index, pKey->Clone());
    _iChildVec.insert(_iChildVec.begin() + child_index, iPair);
  }

  // 中间结点:
  // 1.确定执行插入函数的子结点
  // 2.对应的子结点执行插入函数
  // 3.判断子结点是否为满结点，满结点时执行分裂
  // 4.子结点分裂情况下需要更新KeyVec和ChildVec
  else {
    // 中间节点必定非空
    Size child_index = LowerBound(pKey);
    if (child_index >= _iChildVec.size()) {
      // larger than max
      child_index = _iChildVec.size() > 0 ? _iChildVec.size() - 1 : 0;
    }

    NodePage *childNodePage = new NodePage(_iChildVec[child_index].first);
    childNodePage->Insert(pKey, iPair);

    // 若子节点容量超过最大容量，需要调整（向左右节点匀一些过去）
    vector<Size> check_index;

    // 目前仍然是伪B+树，因此只看prev和next，不看其他的
    if (childNodePage->Overflow()) {
      bool processed = false;

      //   // prev节点少于一半，可以匀元素过去
      //   if (!processed && child_index > 0) {
      //     NodePage prevPage(_iChildVec[child_index - 1].first);
      //     if (prevPage.LessThanHalf()) {
      //       processed = true;
      //       check_index.push_back(child_index - 1);
      //       Size move_num = (childNodePage->size() - prevPage.size()) >> 1;
      //       std::pair<std::vector<Field *>, std::vector<PageSlotID>> nodes =
      //           childNodePage->PopFrontNodes(move_num);
      //       prevPage.PushBackNodes(nodes);
      //     }
      //   }
      //   // next节点少于一半，可以匀元素过去
      //   if (!processed && child_index + 1 < size()) {
      //     NodePage nextPage(_iChildVec[child_index + 1].first);
      //     if (nextPage.LessThanHalf()) {
      //       processed = true;
      //       Size move_num = (childNodePage->size() - nextPage.size()) >> 1;
      //       std::pair<std::vector<Field *>, std::vector<PageSlotID>> nodes =
      //           childNodePage->PopBackNodes(move_num);
      //       nextPage.PushFrontNodes(nodes);
      //     }
      //   }
      // 没有可以调整的且超出最大容量，即分裂该节点
      if (!processed) {
        processed = true;
        NodePage *childNodePage_split = childNodePage->Split();
        // 插入分裂之后的新节点key和pageid
        _iKeyVec.insert(_iKeyVec.begin() + child_index,
                        childNodePage->LastKey()->Clone());
        delete _iKeyVec[child_index + 1];
        _iKeyVec[child_index + 1] = childNodePage_split->LastKey()->Clone();
        _iChildVec.insert(
            _iChildVec.begin() + child_index + 1,
            PageSlotID(childNodePage_split->GetPageID(), NULL_SLOT));
        delete childNodePage_split;
      }
    }

    // child_index一定需要检查
    // 这是大部分情况仅有的需要检查的部分，因此占耗时很大部分
    // 不放在check_index中统一处理，可以节约一次构造页面的时间
    if (!Equal(_iKeyVec[child_index], childNodePage->LastKey())) {
      delete _iKeyVec[child_index];
      _iKeyVec[child_index] = childNodePage->LastKey()->Clone();
    }
    delete childNodePage;

    // 若更新了子节点的LastKey，需要刷新_iKeyVec
    for (int i = 0; i < check_index.size(); ++i) {
      Size index = check_index[i];
      if (index < size()) {
        NodePage node(_iChildVec[index].first);
        if (!Equal(_iKeyVec[index], node.LastKey())) {
          delete _iKeyVec[index];
          _iKeyVec[index] = node.LastKey()->Clone();
        }
      }
    }
  }

  // ALERT:
  // 中间结点执行插入过程中，需要考虑到实际中间结点为空结点的特殊情况进行特判
  // ALERT: 对于头结点的插入可能更新头结点的Key值
  // ALERT: KeyVec中的Key的赋值需要使用深拷贝，否则会出现析构导致的问题
  // ALERT: 上层保证每次插入的iPair不同
  return true;
}

Size NodePage::Delete(Field *pKey) {
  bool ans = 0;
  if (Empty()) return 0;
  Size left_index = LowerBound(pKey);

  // 需要基于结点类型判断执行过程
  // 叶结点：
  // 1.确定删除位置后删除数据即可
  if (_bLeaf) {
    Size left_index = LowerBound(pKey), right_index = UpperBound(pKey);
    if (left_index >= right_index && !Equal(pKey, _iKeyVec[left_index]))
      return 0;
    for (Size i = left_index; i <= right_index; ++i) {
      delete _iKeyVec[i];
    }
    ans += right_index - left_index + 1;
    EraseNodes(left_index, right_index + 1);
    return ans;
  }

  // 中间结点:
  // 1.确定执行删除函数的子结点
  // 2.对应的子结点执行删除函数
  // 3.判断子结点是否为满结点，空结点时清除空结点
  // 4.删除空结点情况下需要更新KeyVec和ChildVec
  else {
    NodePage *pPage = new NodePage(_nPageID);
    // 递归地找到区间左端点
    while (!pPage->_bLeaf) {
      if (pPage->Empty()) return ans;
      Size child_index = pPage->LowerBound(pKey);
      if (child_index >= pPage->_iChildVec.size()) {
        // larger than max
        delete pPage;
        return ans;
      }
      PageID pageID = pPage->_iChildVec[child_index].first;
      delete pPage;
      pPage = new NodePage(pageID);
    }

    Size leaf_ans = pPage->Delete(pKey);
    ans += leaf_ans;

    // 按链表向右寻找符合条件的，直到某个页面不全符合条件
    while (leaf_ans > 0 &&
           Equal(pKey, pPage->_iKeyVec[pPage->_iKeyVec.size() - 1]) &&
           pPage->GetNextID() != NULL_PAGE) {
      PageID pageID_next = pPage->GetNextID();
      delete pPage;
      pPage = new NodePage(pageID_next);
      leaf_ans = pPage->Delete(pKey);
      ans += leaf_ans;
    }
    delete pPage;
  }

  // ALERT: 注意删除结点过程中如果清除了Key则需要析构
  // ALERT:
  // 注意存在键值相同的情况发生，所以需要保证所有需要执行删除函数的子结点都执行了删除函数
  // ALERT: 可以适当简化合并函数，例如不删除空的中间结点
  return ans;
}

bool NodePage::Delete(Field *pKey, const PageSlotID &iPair) {
  bool ans = false;
  if (Empty()) return false;

  // 需要基于结点类型判断执行过程
  // 叶结点：
  // 1.确定删除位置后删除数据即可
  if (_bLeaf) {
    for (Size i = LowerBound(pKey); i < size(); ++i) {
      if (!Equal(pKey, _iKeyVec[i])) return ans;
      if (iPair == _iChildVec[i]) {
        delete _iKeyVec[i];
        _iChildVec.erase(_iChildVec.begin() + i);
        _iKeyVec.erase(_iKeyVec.begin() + i);
        ans = true;
        _bModified = true;
      }
    }
    return ans;
  }

  // 中间结点:
  // 1.确定执行删除函数的子结点
  // 2.对应的子结点执行删除函数
  // 3.判断子结点是否为满结点，空结点时清除空结点
  // 4.删除空结点情况下需要更新KeyVec和ChildVec
  else {
    Size child_index = LowerBound(pKey);
    if (child_index >= _iChildVec.size()) {
      // larger than max
      return ans;
    }

#ifdef INDEX_DEBUG
    printf("Children sum = %d, child_index = %d\n", int(_iChildVec.size()),
           int(child_index));
#endif

    NodePage *childNodePage = new NodePage(_iChildVec[child_index].first);
    ans = childNodePage->Delete(pKey, iPair);
    if (!ans) {
      return false;
    }
    _bModified = true;

    // 以下皆为删除成功的情况
    // 若将子节点删得 < _nCap / 2，则需要进行调整（向左右节点借一些过来）
    vector<Size> check_index;
    vector<Size> deleted_index;

    bool pageArrange = childNodePage->LessThanHalf();
#ifdef INDEX_DEBUG
    if (pageArrange)
      printf("\n----------- Delete iPair Page Arrange -----------\n");
#endif

    // 目前仍然是伪B+树，因此只看prev和next，不看其他的
    if (pageArrange) {
      bool processed = false;

      // 可以与prev节点调整
      if (!processed && child_index > 0) {
        processed = true;
        NodePage *prevPage = new NodePage(_iChildVec[child_index - 1].first);
        // 可以借元素
        if (childNodePage->size() + prevPage->size() >= _nCap) {
#ifdef INDEX_DEBUG
          printf("Average prev %d\n", int(prevPage->GetPageID()));
#endif
          check_index.push_back(child_index - 1);
          Size move_num = (prevPage->size() - childNodePage->size()) >> 1;
          childNodePage->PushFrontNodes(prevPage->PopBackNodes(move_num));
          delete prevPage;
        }
        // 合并节点
        else {
#ifdef INDEX_DEBUG
          printf("Merge prev %d\n", int(prevPage->GetPageID()));
#endif
          deleted_index.push_back(child_index - 1);
          delete prevPage;
          childNodePage->MergePrev();
        }
      }
      // 可以与next节点调整
      if (!processed && child_index + 1 < size()) {
        processed = true;
        NodePage *nextPage = new NodePage(_iChildVec[child_index + 1].first);
        // 可以借元素
        if (childNodePage->size() + nextPage->size() >= _nCap) {
#ifdef INDEX_DEBUG
          printf("Average next %d\n", int(nextPage->GetPageID()));
#endif
          check_index.push_back(child_index);
          Size move_num = (nextPage->size() - childNodePage->size()) >> 1;
          childNodePage->PushBackNodes(nextPage->PopFrontNodes(move_num));
          delete nextPage;
        }
        // 合并节点
        else {
#ifdef INDEX_DEBUG
          printf("Merge next %d\n", int(nextPage->GetPageID()));
#endif
          check_index.push_back(child_index);
          deleted_index.push_back(child_index + 1);
          delete nextPage;
          childNodePage->MergeNext();
        }
      }
      // 没有左右节点的情况：只有根节点存在，交给Index处理根节点情况
    }

    // child_index一定需要检查
    // 这是大部分情况仅有的需要检查的部分，因此占耗时很大部分
    // 不放在check_index中统一处理，可以节约一次构造页面的时间

#ifdef INDEX_DEBUG
    if (pageArrange)
      printf("page %d, childNodePage %d\n", int(_nPageID),
             int(childNodePage->GetPageID()));
#endif

    delete childNodePage;

    // 若更新了子节点的LastKey，需要刷新_iKeyVec
    for (int i = 0; i < check_index.size(); ++i) {
      Size index = check_index[i];
      if (index < size()) {
#ifdef INDEX_DEBUG
        printf("check_index %d, ", int(_iChildVec[index].first));
#endif

        NodePage node(_iChildVec[index].first);
        Field *pLastKey = node.LastKey();
        if (pLastKey != nullptr && !Equal(_iKeyVec[index], pLastKey)) {
          delete _iKeyVec[index];
          _iKeyVec[index] = pLastKey->Clone();
        }
      }
    }

    std::sort(deleted_index.begin(), deleted_index.end());
    for (int i = deleted_index.size() - 1; i >= 0; --i) {
      int index = deleted_index[i];

#ifdef INDEX_DEBUG
      printf("deleted_index %d, ", _iChildVec[index]);
#endif

      delete _iKeyVec[index];
      _iKeyVec.erase(_iKeyVec.begin() + index);
      _iChildVec.erase(_iChildVec.begin() + index);
    }

#ifdef INDEX_DEBUG
    printf("\n");
    if (pageArrange)
      printf("-------------------------------------------------\n\n");
#endif
  }

  // ALERT:
  // 由于Insert过程中保证了没用相同的Value值，所以只要成功删除一个结点即可保证删除成功
  return ans;
}

bool NodePage::Update(Field *pKey, const PageSlotID &iOld,
                      const PageSlotID &iNew) {
  bool ans = false;
  if (Empty()) return false;

  // 需要基于结点类型判断执行过程
  // 叶结点：
  // 1.确定更新位置后更新数据即可
  if (_bLeaf) {
    for (Size i = LowerBound(pKey); i < size(); ++i) {
      if (!Equal(pKey, _iKeyVec[i])) return ans;
      if (iOld == _iChildVec[i]) {
        _iChildVec[i] = iNew;
        ans = true;
        _bModified = true;
      }
    }
    return ans;
  }
  // 中间结点:
  // 1.确定执行更新函数的子结点
  // 2.对应的子结点执行更新函数
  else {
    Size child_index = LowerBound(pKey);
    if (child_index >= _iChildVec.size()) {
      // larger than max
      return ans;
    }
    NodePage childNodePage(_iChildVec[child_index].first);
    ans = childNodePage.Update(pKey, iOld, iNew);
    _bModified = _bModified || ans;
    if (!ans) return false;
    // 若更新了子节点的LastKey，需要刷新_iKeyVec
    if (!Equal(_iKeyVec[child_index], childNodePage.LastKey())) {
      delete _iKeyVec[child_index];
      _iKeyVec[child_index] = childNodePage.LastKey()->Clone();
    }
  }

  // ALERT: 由于更新函数不改变结点内存储的容量，所以不需要结构变化
  // ALERT:
  // 由于Insert过程中保证了没用相同的Value值，所以只要成功更新一个结点即可保证更新成功
  return ans;
}

NodePage *NodePage::Split() {
  _bModified = true;
  std::pair<std::vector<Field *>, std::vector<PageSlotID>> nodes = PopHalf();
  NodePage *newNodePage =
      new NodePage(_nKeyLen, _iKeyType, _bLeaf, nodes.first, nodes.second);
  PushBack(newNodePage);
  return newNodePage;
}

void NodePage::MergePrev() {
  // 保证prev page
  assert(GetPrevID() != NULL_PAGE);
  // 保证合并后不超过最大容量
  NodePage *pPrevPage = new NodePage(GetPrevID());
  assert(size() + pPrevPage->size() <= _nCap);

  _bModified = true;
  PushFrontNodes(pPrevPage->PopAll());
  LinkedPage *pPageDeleted = PopPrev();
  delete pPageDeleted;

  pPrevPage->Clear();
  delete pPrevPage;
}

void NodePage::MergeNext() {
  // 保证next page
  assert(GetNextID() != NULL_PAGE);
  // 保证合并后不超过最大容量
  NodePage *pNextPage = new NodePage(GetNextID());
  assert(size() + pNextPage->size() <= _nCap);

  _bModified = true;
  PushBackNodes(pNextPage->PopAll());
  LinkedPage *pPageDeleted = PopBack();
  delete pPageDeleted;

  pNextPage->Clear();
  delete pNextPage;
}

void NodePage::Arange(Size left, Size right) {
  // TODO
}

std::vector<PageSlotID> NodePage::Range(Field *pLow, Field *pHigh) {
#ifdef INDEX_DEBUG
  // std::cout << "Range start : [" << pLow->ToString() << ", "
  //           << pHigh->ToString() << ")\n";
#endif

  // 需要基于结点类型判断执行过程
  // 叶结点：
  // 1.确定上下界范围，返回左闭右开区间[pLow, pHigh)内的所有Value值
  std::vector<PageSlotID> ans;
  if (Empty()) return ans;

  if (_bLeaf) {
    Size left_index = LowerBound(pLow), right_index = LessBound(pHigh);

#ifdef INDEX_DEBUG
    std::cout << "Leaf (index) : " << left_index << " -> " << right_index
              << std::endl;
#endif

    if (left_index == right_index &&
        (Less(_iKeyVec[left_index], pLow) ||
         GreaterEqual(_iKeyVec[right_index], pHigh)))
      return ans;
    ans.insert(ans.end(), _iChildVec.begin() + left_index,
               _iChildVec.begin() + right_index + 1);
  }

  // 中间结点:
  // 1.确定所有可能包含上下界范围的子结点
  // 2.依次对添加各个子结点执行查询函数所得的结果
  else {
    NodePage *pPage = new NodePage(_nPageID);
    // 递归地找到区间左端点
    while (!pPage->_bLeaf) {
      if (pPage->Empty()) return ans;
      Size child_index = pPage->LowerBound(pLow);
      if (child_index >= pPage->_iChildVec.size()) {
        // larger than max
        return ans;
      }

#ifdef INDEX_DEBUG
      printf("Children sum = %d, child_index = %d\n",
             int(pPage->_iChildVec.size()), int(child_index));
#endif

      PageID pageID = pPage->_iChildVec[child_index].first;
      delete pPage;
      pPage = new NodePage(pageID);
    }
    std::vector<PageSlotID> leaf_ans = pPage->Range(pLow, pHigh);
    ans.insert(ans.end(), leaf_ans.begin(), leaf_ans.end());

#ifdef INDEX_DEBUG
    // pPage->print();
    // std::cout << "\n$$$$$$$$$$$$$$$\n";
    // for (Size i = 0; i < leaf_ans.size(); ++i)
    //   printf("(%d, %d)\n", (int)leaf_ans[i].first, (int)leaf_ans[i].second);
    // std::cout << "$$$$$$$$$$$$$$$\n\n";
#endif

    // 按链表向右寻找符合条件的，直到某个页面不全符合条件
    while (leaf_ans.size() > 0 &&
           leaf_ans[leaf_ans.size() - 1] ==
               pPage->_iChildVec[pPage->_iChildVec.size() - 1] &&
           pPage->GetNextID() != NULL_PAGE) {
#ifdef INDEX_DEBUG
      std::cout << "-------> (" << leaf_ans[leaf_ans.size() - 1].first << ", "
                << leaf_ans[leaf_ans.size() - 1].second << ") == ("
                << pPage->_iChildVec[pPage->_iChildVec.size() - 1].first << ", "
                << pPage->_iChildVec[pPage->_iChildVec.size() - 1].second
                << ")\n";
#endif

      PageID pageID_next = pPage->GetNextID();
      delete pPage;
      pPage = new NodePage(pageID_next);
      leaf_ans = pPage->Range(pLow, pHigh);
      ans.insert(ans.end(), leaf_ans.begin(), leaf_ans.end());

#ifdef INDEX_DEBUG
      // pPage->print();
      // std::cout << "\n$$$$$$$$$$$$$$$\n";
      // for (Size i = 0; i < leaf_ans.size(); ++i)
      //   printf("(%d, %d)\n", (int)leaf_ans[i].first,
      //   (int)leaf_ans[i].second);
      // std::cout << "$$$$$$$$$$$$$$$\n\n";
#endif
    }
    delete pPage;
  }

#ifdef INDEX_DEBUG
  // std::cout << "Range end\n";
#endif

  // ALERT: 注意叶结点可能为空结点，需要针对这种情况进行特判
  return ans;
}

void NodePage::Clear() {
  // 需要基于结点类型判断执行过程
  // 叶结点：直接释放占用空间
  // 中间结点：先释放子结点空间，之后释放自身占用空间
  // 根节点： 不释放空间，由IndexManager来释放
  _bModified = false;
  if (!_bLeaf)
    for (Size i = 0; i < _iChildVec.size(); ++i) {
      NodePage nodePage(_iChildVec[i].first);
      nodePage.Clear();
    }
  OS::GetOS()->DeletePage(GetPageID());
}

void NodePage::print() const {
#ifdef PRINT_PAGE
  std::cout << "\n**************************************\n";
  std::cout << "_nPageID = " << _nPageID << "\n";
  std::cout << "_nPrevID = " << _nPrevID << "\n";
  std::cout << "_nNextID = " << _nNextID << "\n";
  std::cout << (_bLeaf ? "Leaf\n" : "Not Leaf\n");
  std::cout << "Key len = " << _nKeyLen << "\n";
  std::cout << "Key type = " << toString(_iKeyType) << "\n";
  std::cout << "Capacity = " << _nCap << "\n";
  for (int i = 0; i < size(); ++i) {
    std::cout << i << " : " << _iKeyVec[i]->ToString() << " -> ("
              << _iChildVec[i].first << ", " << _iChildVec[i].second << ")\n";
  }
  std::cout << "**************************************\n" << std::endl;
  if (!_bLeaf)
    for (int i = 0; i < _iChildVec.size(); ++i) {
      NodePage childNodePage(_iChildVec[i].first);
      childNodePage.print();
    }
#endif
}

void NodePage::CalculateCap() {
  _nCap = (DATA_SIZE - DATA_OFFSET) / (_nKeyLen + 8);
}
bool NodePage::Overflow() const { return size() > _nCap; }
bool NodePage::Full() const { return size() >= _nCap; }
bool NodePage::Empty() const { return size() == 0; }
bool NodePage::MoreThanHalf() const { return size() > (_nCap >> 1); }
bool NodePage::LessThanHalf() const { return size() < (_nCap >> 1); }

FieldType NodePage::GetType() const { return _iKeyType; }
Size NodePage::size() const { return _iKeyVec.size(); }

Field *NodePage::LastKey() const {
  if (Empty()) return nullptr;
  return _iKeyVec[_iKeyVec.size() - 1];
}

std::pair<std::vector<Field *>, std::vector<PageSlotID>> NodePage::PopHalf() {
  return PopBackNodes(size() / 2);
}
std::pair<std::vector<Field *>, std::vector<PageSlotID>> NodePage::PopAll() {
  return PopBackNodes(size());
}

std::pair<std::vector<Field *>, std::vector<PageSlotID>> NodePage::PopBackNodes(
    Size n) {
  _bModified = true;
  std::vector<Field *> iKeyVec{};
  std::vector<PageSlotID> iChildVec{};
  iKeyVec.insert(iKeyVec.end(), _iKeyVec.end() - n, _iKeyVec.end());
  iChildVec.insert(iChildVec.end(), _iChildVec.end() - n, _iChildVec.end());
  _iKeyVec.erase(_iKeyVec.end() - n, _iKeyVec.end());
  _iChildVec.erase(_iChildVec.end() - n, _iChildVec.end());
  return {iKeyVec, iChildVec};
}

std::pair<std::vector<Field *>, std::vector<PageSlotID>>
NodePage::PopFrontNodes(Size n) {
  _bModified = true;
  std::vector<Field *> iKeyVec{};
  std::vector<PageSlotID> iChildVec{};
  iKeyVec.insert(iKeyVec.end(), _iKeyVec.begin(), _iKeyVec.begin() + n);
  iChildVec.insert(iChildVec.end(), _iChildVec.begin(), _iChildVec.begin() + n);
  _iKeyVec.erase(_iKeyVec.begin(), _iKeyVec.begin() + n);
  _iChildVec.erase(_iChildVec.begin(), _iChildVec.begin() + n);
  return {iKeyVec, iChildVec};
}

void NodePage::PushFrontNodes(
    std::pair<std::vector<Field *>, std::vector<PageSlotID>> nodes) {
  _bModified = true;
  _iKeyVec.insert(_iKeyVec.begin(), nodes.first.begin(), nodes.first.end());
  _iChildVec.insert(_iChildVec.begin(), nodes.second.begin(),
                    nodes.second.end());
}

void NodePage::PushBackNodes(
    std::pair<std::vector<Field *>, std::vector<PageSlotID>> nodes) {
  _bModified = true;
  _iKeyVec.insert(_iKeyVec.end(), nodes.first.begin(), nodes.first.end());
  _iChildVec.insert(_iChildVec.end(), nodes.second.begin(), nodes.second.end());
}

void NodePage::EraseNodes(Size left, Size right) {
  _bModified = true;
  _iChildVec.erase(_iChildVec.begin() + left, _iChildVec.begin() + right);
  _iKeyVec.erase(_iKeyVec.begin() + left, _iKeyVec.begin() + right);
}

void NodePage::Load() {
  // 从格式化页面数据中导入结点信息
  GetHeader((uint8_t *)&_bLeaf, 1, BLEAF_OFFSET);
  GetHeader((uint8_t *)&_nKeyLen, 4, KEY_LEN_OFFSET);
  GetHeader((uint8_t *)&_iKeyType, 4, KEY_TYPE_OFFSET);

  SlotID nSlotUsed;
  GetHeader((uint8_t *)&nSlotUsed, 2, USED_SLOT_OFFSET);

  uint8_t *data = new uint8_t[(_nKeyLen + 8) * nSlotUsed];
  GetData(data, (_nKeyLen + 8) * nSlotUsed, DATA_OFFSET);

  SlotID keySlotID = 0, childSlotID = _nKeyLen * nSlotUsed;
  Field *field = nullptr;
  for (Size i = 0; i < nSlotUsed; ++i) {
    if (_iKeyType == FieldType::INT_TYPE) {
      field = new IntField();
    } else if (_iKeyType == FieldType::FLOAT_TYPE) {
      field = new FloatField();
    }
    field->SetData(data + keySlotID, _nKeyLen);
    _iKeyVec.push_back(field);
    _iChildVec.push_back(*(PageSlotID *)(data + childSlotID));
    keySlotID += _nKeyLen;
    childSlotID += 8;
  }
  delete[] data;
}

void NodePage::Store() {
  // 格式化结点信息并保存到页面中
  SetHeader((uint8_t *)&_bLeaf, 1, BLEAF_OFFSET);
  SetHeader((uint8_t *)&_nKeyLen, 4, KEY_LEN_OFFSET);
  SetHeader((uint8_t *)&_iKeyType, 4, KEY_TYPE_OFFSET);

  SlotID nSlotUsed = size();
  SetHeader((uint8_t *)&nSlotUsed, 2, USED_SLOT_OFFSET);

  uint8_t *data = new uint8_t[(_nKeyLen + 8) * nSlotUsed];

  SlotID keySlotID = 0, childSlotID = _nKeyLen * nSlotUsed;
  for (SlotID i = 0; i < nSlotUsed; ++i) {
    _iKeyVec[i]->GetData(data + keySlotID, _nKeyLen);
    *(PageSlotID *)(data + childSlotID) = _iChildVec[i];
    keySlotID += _nKeyLen;
    childSlotID += 8;
  }
  SetData(data, (_nKeyLen + 8) * nSlotUsed, DATA_OFFSET);
  delete[] data;
}

Size NodePage::LowerBound(Field *pField) {
  // 二分查找找下界，此处给出实现
  // 边界的理解非常重要
  Size nBegin = 0, nEnd = size();
  while (nBegin < nEnd) {
    Size nMid = (nBegin + nEnd) / 2;
    if (GreaterEqual(_iKeyVec[nMid], pField)) {
      nEnd = nMid;
    } else {
      nBegin = nMid + 1;
    }
#ifdef INDEX_DEBUG
    // PrintPageSlotID({nBegin, nEnd});
    // std::cout << std::endl;
#endif
  }
  return nBegin;
}

Size NodePage::MoreBound(Field *pField) {
  // 二分查找找上界，此处给出实现
  // 边界的理解非常重要
  Size nBegin = 0, nEnd = size();
  while (nBegin < nEnd) {
    Size nMid = (nBegin + nEnd) / 2;
    if (Greater(_iKeyVec[nMid], pField)) {
      nEnd = nMid;
    } else {
      nBegin = nMid + 1;
    }
  }
  return nBegin;
}

Size NodePage::LessBound(Field *pField) {
  Size nBegin = 0, nEnd = size();
  while (nBegin < nEnd) {
    Size nMid = (nBegin + nEnd) / 2;
    if (unlikely(nBegin == nEnd - 1)) {
      if (nEnd < size() && Less(_iKeyVec[nEnd], pField))
        return nEnd;
      else
        return nBegin;
    }
    if (Less(_iKeyVec[nMid], pField)) {
      nBegin = nMid;
    } else {
      nEnd = nMid - 1;
    }
  }
  return nBegin;
}

Size NodePage::UpperBound(Field *pField) {
  Size nBegin = 0, nEnd = size();
  while (nBegin < nEnd) {
    Size nMid = (nBegin + nEnd) / 2;
    if (unlikely(nBegin == nEnd - 1)) {
      if (nEnd < size() && !Greater(_iKeyVec[nEnd], pField))
        return nEnd;
      else
        return nBegin;
    }
    if (!Greater(_iKeyVec[nMid], pField)) {
      nBegin = nMid;
    } else {
      nEnd = nMid - 1;
    }
  }
  return nBegin;
}

}  // namespace dbtrain_mysql
