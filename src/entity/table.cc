#include "entity/table.h"

#include <assert.h>

#include <algorithm>

#include "macros.h"
#include "os/os.h"
#include "page/record_page.h"
#include "record/fixed_record.h"

// setting
// especially for debug
#include "settings.h"

namespace dbtrain_mysql {

PageID NextPageID(PageID nCur) {
  LinkedPage* pPage = new LinkedPage(nCur);
  PageID nNext = pPage->GetNextID();
  delete pPage;
  return nNext;
}

Table::Table(PageID nTableID) {
  pTable = new TablePage(nTableID);

  _nHeadID = pTable->GetHeadID();
  _nTailID = pTable->GetTailID();
  _nNotFull = _nHeadID;
  FindNextNotFull();
}

Table::~Table() { delete pTable; }

Record* Table::GetRecord(PageID nPageID, SlotID nSlotID) {
  Record* record = EmptyRecord();
  RecordPage page(nPageID);
  uint8_t* data = page.GetRecord(nSlotID);
  record->Load(data);

  delete[] data;
  return record;
}

PageSlotID Table::InsertRecord(Record* pRecord) {
  // 利用_nNotFull来获取有空间的页面

  FindNextNotFull();
  PageID nPageID = _nNotFull;
  // 利用Record::Store获得序列化数据

  RecordPage page(nPageID);

  uint8_t* data = new uint8_t[pTable->GetTotalSize()];
  pRecord->Store(data);

  // 利用RecordPage::InsertRecord插入数据
  SlotID nSlotID = page.InsertRecord(data);

  // 页满时更新_nNotFull
  // 没必要？等下次用的时候再更新

  delete[] data;
  return PageSlotID(nPageID, nSlotID);
}

void Table::DeleteRecord(PageID nPageID, SlotID nSlotID) {
  // 利用RecordPage::DeleteRecord删除数据
  RecordPage page(nPageID);
  page.DeleteRecord(nSlotID);

  // 更新_nNotFull来保证较高的页面空间利用效率
  _nNotFull = nPageID;
}

void Table::UpdateRecord(PageID nPageID, SlotID nSlotID,
                         const std::vector<Transform>& iTrans) {
  // 仿照InsertRecord从无格式数据导入原始记录
  // 构建Record对象，利用Record::SetField更新Record对象
  Record* record = GetRecord(nPageID, nSlotID);
  // Trasform::GetPos表示更新位置，GetField表示更新后的字段
  for (const auto& iter : iTrans) {
    record->SetField(iter.GetPos(), iter.GetField());
  }

  // 将新的记录序列化
  uint8_t* data = new uint8_t[pTable->GetTotalSize()];
  record->Store(data);
  // 利用RecordPage::UpdateRecord更新一条数据
  RecordPage page(nPageID);
  page.UpdateRecord(nSlotID, data);

  delete[] data;
  delete record;
}

std::vector<PageSlotID> Table::SearchRecord(Condition* pCond) {
  // 对记录的条件检索
  std::vector<PageSlotID> ans;

  bool unStop = true;
  PageID nPageID = pTable->GetHeadID();
  Record* record = EmptyRecord();
  while (unStop) {
    RecordPage page(nPageID);
    for (SlotID nSlotID = 0; nSlotID < page.GetCap(); ++nSlotID) {
      if (page.HasRecord(nSlotID)) {
        // 仿照InsertRecord从无格式数据导入原始记录
        uint8_t* data = page.GetRecord(nSlotID);
        record->Load(data);
        delete[] data;
        // 依次导入各条记录进行条件判断
        // Condition的抽象方法Match可以判断Record是否满足检索条件
        if (pCond == nullptr || pCond->Match(*record)) {
          ans.push_back(PageSlotID(nPageID, nSlotID));
        }
      }
    }
    if (nPageID == pTable->GetTailID()) unStop = false;
    nPageID = page.GetNextID();
  }
  delete record;

  // 返回所有符合条件的结果的pair<PageID,SlotID>
  return ans;
}

void Table::SearchRecord(std::vector<PageSlotID>& iPairs, Condition* pCond) {
  if (!pCond) return;
  auto it = iPairs.begin();
  while (it != iPairs.end()) {
    Record* pRecord = GetRecord(it->first, it->second);
    if (!pCond->Match(*pRecord)) {
      it = iPairs.erase(it);
    } else
      ++it;
    delete pRecord;
  }
}

void Table::Clear() {
  PageID nBegin = _nHeadID;
  while (nBegin != NULL_PAGE) {
    PageID nTemp = nBegin;
    nBegin = NextPageID(nBegin);
    OS::GetOS()->DeletePage(nTemp);
  }
}

void Table::FindNextNotFull() {
  // 快速查找非满记录页面算法
  // 不要同时建立两个指向相同磁盘位置的且可变对象，否则会出现一致性问题
  //   充分利用链表性质，注意全满时需要在结尾_pTable
  //       ->GetTailID对应结点后插入新的结点，并更新_pTable的TailID
  // 只需要保证均摊复杂度较低即可

  PageID searchFlag = _nNotFull;
  if (NextNotFullUntil(pTable->GetTailID())) return;
  _nNotFull = pTable->GetHeadID();
  // searchFlag会重复搜索一次
  if (NextNotFullUntil(searchFlag)) return;

  // 需要插入新的page
  RecordPage newPage(pTable->GetTotalSize(), true);
  LinkedPage tailPageBefore(pTable->GetTailID());
  _nNotFull = newPage.GetPageID();
  tailPageBefore.PushBack(&newPage);
  pTable->SetTailID(newPage.GetPageID());
}

bool Table::NextNotFullUntil(PageID target) {
  bool unStop = _nNotFull != NULL_PAGE;
  // 顺序往链表后面查找
  // 沿用了record_page的思想
  while (unStop) {
    RecordPage page(_nNotFull);
    if (!page.Full()) return true;
    unStop = _nNotFull != target;
    _nNotFull = page.GetNextID();
  }
  return false;
}

FieldID Table::GetPos(const String& sCol) const { return pTable->GetPos(sCol); }

FieldType Table::GetType(const String& sCol) const {
  return pTable->GetType(sCol);
}

Size Table::GetSize(const String& sCol) const { return pTable->GetSize(sCol); }

Record* Table::EmptyRecord() const {
  return new FixedRecord(pTable->GetFieldSize(), pTable->GetTypeVec(),
                         pTable->GetSizeVec());
}

bool CmpByFieldID(const std::pair<String, FieldID>& a,
                  const std::pair<String, FieldID>& b) {
  return a.second < b.second;
}

std::vector<String> Table::GetColumnNames() const {
  std::vector<String> iVec{};
  std::vector<std::pair<String, FieldID>> iPairVec(pTable->_iColMap.begin(),
                                                   pTable->_iColMap.end());
  std::sort(iPairVec.begin(), iPairVec.end(), CmpByFieldID);
  for (const auto& it : iPairVec) iVec.push_back(it.first);
  return iVec;
}

}  // namespace dbtrain_mysql
