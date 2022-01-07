#include "entity/table.h"

#include <assert.h>

#include <algorithm>

#include "macros.h"
#include "page/record_page.h"
#include "utils/basic_function.h"

// setting
// especially for debug
#include "settings.h"

namespace dbtrain_mysql {

Table::Table(TablePage* nTablePage) : Entity() {
  _pManagerPage = nTablePage;
  Init();
}

Table::Table(PageID nTableID) : Entity() {
  _pManagerPage = new TablePage(nTableID);
  Init();
}

void Table::Init() {
  Entity::Init();
  _pTablePage = dynamic_cast<TablePage*>(_pManagerPage);
}

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

#ifdef DELETE_DEBUG
  printf("Table::InsertRecord to page %d\n", int(nPageID));
#endif

  // 利用Record::Store获得序列化数据
  uint8_t* data = new uint8_t[_pManagerPage->GetTotalSize()];
  pRecord->Store(data);

  // 利用RecordPage::InsertRecord插入数据
  RecordPage page(nPageID);
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
  // Trasform::GetColPos表示更新位置，GetField表示更新后的字段
  for (const auto& iter : iTrans) {
#ifdef UPDATE_DEBUG
    printf("Update\n");
    Field* pField = iter.GetField();
    printf("GetField\n");
    printf("%p\n", pField);
    std::cout << "Update to " << pField->ToString() << std::endl;
    delete pField;
#endif
    record->SetField(iter.GetColPos(), iter.GetField());
  }

  // 将新的记录序列化
  uint8_t* data = new uint8_t[_pManagerPage->GetTotalSize()];
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
  PageID nPageID = _pManagerPage->GetHeadID();
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
    if (nPageID == _pManagerPage->GetTailID()) unStop = false;
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

FieldID Table::GetColPos(const String& sCol) const {
  return _pTablePage->GetColPos(sCol);
}

FieldType Table::GetType(const String& sCol) const {
  return _pTablePage->GetType(sCol);
}

Size Table::GetSize(const String& sCol) const {
  return _pTablePage->GetSize(sCol);
}

bool Table::GetCanBeNull(const String& sCol) const {
  return _pTablePage->GetCanBeNull(sCol);
}

bool Table::GetIsPrimary(const String& sCol) const {
  return _pTablePage->GetIsPrimary(sCol);
}
bool Table::GetIsForeign(const String& sCol) const {
  return _pTablePage->GetIsForeign(sCol);
}

std::vector<String> Table::GetColumnNames() const {
  std::vector<String> iVec{};
  std::vector<std::pair<String, FieldID>> iPairVec(
      _pTablePage->_iColMap.begin(), _pTablePage->_iColMap.end());
  std::sort(iPairVec.begin(), iPairVec.end(), lessCmpBySecond<String, FieldID>);
  for (const auto& it : iPairVec) iVec.push_back(it.first);
  return iVec;
}

std::vector<Record*> Table::GetTableInfos() const {
  std::vector<Record*> iVec{};
  for (const auto& sColName : GetColumnNames()) {
    FixedRecord* pDesc = new FixedRecord(
        5,
        {FieldType::CHAR_TYPE, FieldType::CHAR_TYPE, FieldType::INT_TYPE,
         FieldType::CHAR_TYPE, FieldType::CHAR_TYPE},
        {COLUMN_NAME_SIZE, 10, 4, 3, 3});
    pDesc->SetField(0, new CharField(sColName));
    pDesc->SetField(1, new CharField(toString(GetType(sColName))));
    pDesc->SetField(2, new IntField(GetSize(sColName)));
    pDesc->SetField(3, new CharField((_pTablePage->GetCanBeNull(sColName) &&
                                      !_pTablePage->GetIsPrimary(sColName))
                                         ? "YES"
                                         : "NO"));
    pDesc->SetField(
        4, new CharField((_pTablePage->GetIsPrimary(sColName)) ? "YES" : "NO"));
    iVec.push_back(pDesc);
  }
  return iVec;
}

EntityType Table::GetEntityType() const { return EntityType::TABLE_TYPE; }

void Table::AddPrimaryKey(const std::vector<String>& iColVec){
  for(int i = 0; i < iColVec.size(); i ++){
    _pTablePage->_iStatusVec[_pTablePage->GetColPos(iColVec[i])] |= 0b10 ;//add primary key
  }
}

void Table::DropPrimaryKey(const String& sColName){
  _pTablePage->_iStatusVec[_pTablePage->GetColPos(sColName)] &= 0b11111101;
}
void Table::DropForeignKey(const String& sColName){
  _pTablePage->_iStatusVec[_pTablePage->GetColPos(sColName)] &= 0b11111011;
}

}  // namespace dbtrain_mysql
