// #include "table/table.h"

// #include <assert.h>

// #include <algorithm>

// #include "macros.h"
// #include "minios/os.h"
// #include "page/record_page.h"
// #include "record/fixed_record.h"

// // setting
// // especially for debug
// #include "settings.h"

// namespace dbtrain_mysql {

// PageID NextPageID(PageID nCur) {
//   LinkedPage* pPage = new LinkedPage(nCur);
//   PageID nNext = pPage->GetNextID();
//   delete pPage;
//   return nNext;
// }

// Table::Table(PageID nTableID) {
//   pTable = new TablePage(nTableID);

//   _nHeadID = pTable->GetHeadID();
//   _nTailID = pTable->GetTailID();
//   _nNotFull = _nHeadID;
//   NextNotFull();
// }

// Table::~Table() { delete pTable; }

// Record* Table::GetRecord(PageID nPageID, SlotID nSlotID) {
//   // LAB1 BEGIN
//   // TODO: 获得一条记录
//   // TIPS: 利用RecordPage::GetRecord获取无格式记录数据
//   // TIPS: 利用TablePage::GetFieldSize, GetTyepVec, GetSizeVec
//   Record* record = EmptyRecord();
//   // 三个函数可以构建空的FixedRecord对象
//   RecordPage page(nPageID);
//   uint8_t* data = page.GetRecord(nSlotID);
//   // TIPS: 利用Record::Load导入数据 ALERT: 需要注意析构所有不会返回的内容
//   record->Load(data);

//   delete[] data;
//   return record;

//   // LAB1 END
// }

// PageSlotID Table::InsertRecord(Record* pRecord) {
//   // LAB1 BEGIN
//   // TODO: 插入一条记录
//   // TIPS: 利用_nNotFull来获取有空间的页面

//   NextNotFull();
//   PageID nPageID = _nNotFull;
//   // TIPS: 利用Record::Store获得序列化数据

//   RecordPage page(nPageID);

//   uint8_t* data = new uint8_t[pTable->GetTotalSize()];
//   pRecord->Store(data);

//   // TIPS: 利用RecordPage::InsertRecord插入数据
//   SlotID nSlotID = page.InsertRecord(data);

//   // TIPS: 注意页满时更新_nNotFull
//   // 没必要？等下次用的时候再更新

//   delete[] data;
//   return PageSlotID(nPageID, nSlotID);

//   // LAB1 END
// }

// void Table::DeleteRecord(PageID nPageID, SlotID nSlotID) {
//   // LAB1 BEGIN
//   // TIPS: 利用RecordPage::DeleteRecord插入数据
//   RecordPage page(nPageID);
//   page.DeleteRecord(nSlotID);

//   // TIPS: 注意更新_nNotFull来保证较高的页面空间利用效率
//   _nNotFull = nPageID;

//   // LAB1 END
// }

// void Table::UpdateRecord(PageID nPageID, SlotID nSlotID,
//                          const std::vector<Transform>& iTrans) {
//   // LAB1 BEGIN
//   // TIPS: 仿照InsertRecord从无格式数据导入原始记录
//   // TIPS: 构建Record对象，利用Record::SetField更新Record对象
//   Record* record = GetRecord(nPageID, nSlotID);
//   // TIPS: Trasform::GetPos表示更新位置，GetField表示更新后的字段
//   for (const auto& iter : iTrans) {
//     record->SetField(iter.GetPos(), iter.GetField());
//   }

//   // TIPS: 将新的记录序列化
//   uint8_t* data = new uint8_t[pTable->GetTotalSize()];
//   record->Store(data);
//   // TIPS: 利用RecordPage::UpdateRecord更新一条数据
//   RecordPage page(nPageID);
//   page.UpdateRecord(nSlotID, data);

//   delete[] data;
//   delete record;

//   // LAB1 END
// }

// std::vector<PageSlotID> Table::SearchRecord(Condition* pCond) {
//   // LAB1 BEGIN
//   // TODO: 对记录的条件检索

//   std::vector<PageSlotID> ans;

//   bool unStop = true;
//   PageID nPageID = pTable->GetHeadID();
//   Record* record = EmptyRecord();
//   while (unStop) {
//     RecordPage page(nPageID);
//     for (SlotID nSlotID = 0; nSlotID < page.GetCap(); ++nSlotID) {
//       if (page.HasRecord(nSlotID)) {
//         // TIPS: 仿照InsertRecord从无格式数据导入原始记录
//         uint8_t* data = page.GetRecord(nSlotID);
//         record->Load(data);
//         delete[] data;
//         // TIPS: 依次导入各条记录进行条件判断
//         // TIPS: Condition的抽象方法Match可以判断Record是否满足检索条件
//         if (pCond == nullptr || pCond->Match(*record)) {
//           ans.push_back(PageSlotID(nPageID, nSlotID));
//         }
//       }
//     }
//     if (nPageID == pTable->GetTailID()) unStop = false;
//     nPageID = page.GetNextID();
//   }
//   delete record;

//   // TIPS: 返回所有符合条件的结果的pair<PageID,SlotID>
//   return ans;

//   // LAB1 END
// }

// void Table::SearchRecord(std::vector<PageSlotID>& iPairs, Condition* pCond) {
//   if (!pCond) return;
//   auto it = iPairs.begin();
//   while (it != iPairs.end()) {
//     Record* pRecord = GetRecord(it->first, it->second);
//     if (!pCond->Match(*pRecord)) {
//       it = iPairs.erase(it);
//     } else
//       ++it;
//     delete pRecord;
//   }
// }

// void Table::Clear() {
//   PageID nBegin = _nHeadID;
//   while (nBegin != NULL_PAGE) {
//     PageID nTemp = nBegin;
//     nBegin = NextPageID(nBegin);
//     MiniOS::GetOS()->DeletePage(nTemp);
//   }
// }

// void Table::NextNotFull() {
//   // LAB1 BEGIN
//   // TODO: 实现一个快速查找非满记录页面的算法
//   // ALERT: ！！！一定要注意！！！
//   // 不要同时建立两个指向相同磁盘位置的且可变对象，否则会出现一致性问题
//   // ALERT: 可以适当增加传入参数，本接口不会被外部函数调用，例如额外传入Page
//   // *指针
//   // TIPS:
//   //
//   充分利用链表性质，注意全满时需要在结尾_pTable->GetTailID对应结点后插入新的结点，并更新_pTable的TailID
//   // TIPS: 只需要保证均摊复杂度较低即可

//   PageID searchFlag = _nNotFull;
//   if (NextNotFullUntil(pTable->GetTailID())) return;
//   _nNotFull = pTable->GetHeadID();
//   // searchFlag会重复搜索一次
//   if (NextNotFullUntil(searchFlag)) return;

//   // 需要插入新的page
//   RecordPage newPage(pTable->GetTotalSize(), true);
//   LinkedPage tailPageBefore(pTable->GetTailID());
//   _nNotFull = newPage.GetPageID();
//   tailPageBefore.PushBack(&newPage);
//   pTable->SetTailID(newPage.GetPageID());

//   // LAB1 END
// }

// bool Table::NextNotFullUntil(PageID target) {
//   bool unStop = _nNotFull == NULL_PAGE ? false : true;
//   // 顺序往链表后面查找
//   // 沿用了record_page的思想
//   while (unStop) {
//     RecordPage page(_nNotFull);
//     if (!page.Full()) return true;
//     if (_nNotFull == target) unStop = false;
//     _nNotFull = page.GetNextID();
//   }
//   return false;
// }

// FieldID Table::GetPos(const String& sCol) const { return
// pTable->GetPos(sCol); }

// FieldType Table::GetType(const String& sCol) const {
//   return pTable->GetType(sCol);
// }

// Size Table::GetSize(const String& sCol) const { return pTable->GetSize(sCol);
// }

// Record* Table::EmptyRecord() const {
//   FixedRecord* pRecord = new FixedRecord(
//       pTable->GetFieldSize(), pTable->GetTypeVec(), pTable->GetSizeVec());
//   return pRecord;
// }

// bool CmpByFieldID(const std::pair<String, FieldID>& a,
//                   const std::pair<String, FieldID>& b) {
//   return a.second < b.second;
// }

// std::vector<String> Table::GetColumnNames() const {
//   std::vector<String> iVec{};
//   std::vector<std::pair<String, FieldID>> iPairVec(pTable->_iColMap.begin(),
//                                                    pTable->_iColMap.end());
//   std::sort(iPairVec.begin(), iPairVec.end(), CmpByFieldID);
//   for (const auto& it : iPairVec) iVec.push_back(it.first);
//   return iVec;
// }

// }  // namespace dbtrain_mysql
