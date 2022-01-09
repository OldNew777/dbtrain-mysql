#include "index/index.h"

#include "macros.h"
#include "os/os.h"
#include "settings.h"

namespace dbtrain_mysql {

Index::Index(FieldType iType, Size nSize) {
  // 建立一个新的根结点，注意需要基于类型判断根结点的属性
  // 根结点需要设为中间结点
  rootPage = new NodePage(nSize, iType, true);

  // 记录RootID
  _nRootID = rootPage->GetPageID();
}

Index::Index(PageID nPageID) {
  _nRootID = nPageID;
  rootPage = new NodePage(_nRootID);
}

Index::~Index() { delete rootPage; }

void Index::Clear() {
  // 利用根结点的Clear函数清除全部索引占用页面
  rootPage->Clear();
}

PageID Index::GetRootID() const { return _nRootID; }

bool Index::Insert(Field *pKey, const PageSlotID &iPair) {
  // 利用根结点的Insert执行插入
  // 根结点满时，需要进行分裂操作，同时更新RootID

  bool ans = rootPage->Insert(pKey, iPair);
  if (!ans) return false;

  // 若子节点容量超过最大容量，分裂
  if (rootPage->Overflow()) {
    NodePage *newRootPage =
        new NodePage(rootPage->_nKeyLen, rootPage->_iKeyType, false);
    _nRootID = newRootPage->GetPageID();
    NodePage *splitPage = rootPage->Split();
    newRootPage->_iKeyVec.push_back(rootPage->LastKey()->Clone());
    newRootPage->_iKeyVec.push_back(splitPage->LastKey()->Clone());
    newRootPage->_iChildVec.push_back(
        PageSlotID(rootPage->GetPageID(), NULL_SLOT));
    newRootPage->_iChildVec.push_back(
        PageSlotID(splitPage->GetPageID(), NULL_SLOT));
    delete splitPage;
    delete rootPage;
    rootPage = newRootPage;
  }

  _bModified = true;

#ifdef INDEX_DEBUG
  print();
#endif

  return true;
}

Size Index::Delete(Field *pKey) {
  // 利用根结点的Delete执行删除
  if (_bModified) {
    delete rootPage;
    rootPage = new NodePage(_nRootID);
    _bModified = false;
  }
  Size ans = rootPage->Delete(pKey);
  if (ans > 0) {
    _bModified = true;
    // merge node here
    rootPage->Arange(0, rootPage->size());
  }

#ifdef INDEX_DEBUG
  print();
#endif

  return ans;
}

bool Index::Delete(Field *pKey, const PageSlotID &iPair) {
  // 利用根结点的Delete执行删除
  bool ans = rootPage->Delete(pKey, iPair);
  if (!ans) return false;

  // merge node here
  while (rootPage->size() == 1 && !rootPage->_bLeaf) {
    NodePage child(rootPage->_iChildVec[0].first);
    rootPage->_bLeaf = child._bLeaf;
    rootPage->_iKeyVec.clear();
    rootPage->_iChildVec.clear();
    rootPage->PushBackNodes(child.PopAll());
    OS::GetOS()->DeletePage(child.GetPageID());
    child._bModified = false;
    rootPage->_bModified = true;
  }
  if (rootPage->size() == 0) {
    rootPage->_bLeaf = true;
  }

  _bModified = true;

#ifdef INDEX_DEBUG
  print();
#endif

  return true;
}

bool Index::Update(Field *pKey, const PageSlotID &iOld,
                   const PageSlotID &iNew) {
  // 利用根结点的Update执行删除
  _bModified = true;
  return rootPage->Update(pKey, iOld, iNew);

#ifdef INDEX_DEBUG
  print();
#endif
}

std::vector<PageSlotID> Index::Range(Field *pLow, Field *pHigh) {
  // 利用根结点的Range执行范围查找
  if (_bModified) {
    delete rootPage;
    rootPage = new NodePage(_nRootID);
    _bModified = false;
  }
  std::vector<PageSlotID> ans = rootPage->Range(pLow, pHigh);

#ifdef INDEX_DEBUG
  std::cout << "\n--------------------------------------------\n";
  std::cout << "$$$$$$$ Index::Range [" << pLow->ToString() << ", "
            << pHigh->ToString() << ") $$$$$$$$\n";
  for (Size i = 0; i < ans.size(); ++i)
    printf("(%d, %d)\n", (int)ans[i].first, (int)ans[i].second);
  std::cout << "--------------------------------------------\n\n";
#endif

  return ans;
}

void Index::print() const {
  std::cout << "\n++++++++++++++++++++++++++++++++++++++\n";
  std::cout << "Start to Print Index : Root PageID = " << rootPage->GetPageID()
            << std::endl;
  rootPage->print();
  std::cout << "++++++++++++++++++++++++++++++++++++++\n" << std::endl;
}

}  // namespace dbtrain_mysql
