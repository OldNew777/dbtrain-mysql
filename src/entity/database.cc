#include "database.h"

#include "condition/conditions.h"
#include "exception/exceptions.h"
#include "macros.h"
#include "os/os.h"
#include "page/record_page.h"
#include "page/table_page.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

Database::Database(DatabasePage* pDatabasePage) : EntityManager(pDatabasePage) {
  _pIndexManager = new IndexManager(pDatabasePage->GetIndexManagerPageID());
  Init();
}

Database::Database(PageID nDatabasePageID) : EntityManager() {
  DatabasePage* pDatabasePage = new DatabasePage(nDatabasePageID);
  _pManagerPage = pDatabasePage;
  _pIndexManager = new IndexManager(pDatabasePage->GetIndexManagerPageID());
  Init();
}

Database::~Database() { delete _pIndexManager; }

IndexManager* Database::GetIndexManager() const { return _pIndexManager; }

Table* Database::GetTable(const String& sTableName) {
  if (_iEntityMap.find(sTableName) == _iEntityMap.end()) {
    if (_iEntityPageIDMap.find(sTableName) == _iEntityPageIDMap.end()) {
      // no table named as it / not loaded
      return nullptr;
    } else {
      // not cached
      _iEntityMap[sTableName] = new Table(_iEntityPageIDMap[sTableName]);
      return dynamic_cast<Table*>(_iEntityMap[sTableName]);
    }
  }
  // cached
  return dynamic_cast<Table*>(_iEntityMap[sTableName]);
}

void Database::CreateTable(const String& sTableName, const Schema& iSchema) {
  // Table existed before
  if (GetTable(sTableName) != nullptr) {
    auto e = TableExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  // Create table and cache it
  TablePage* pPage = new TablePage(iSchema);
  Table* pTable = new Table(pPage);
  _iEntityMap[sTableName] = pTable;
  _iEntityPageIDMap[sTableName] = pPage->GetPageID();

  // insert entity to page
  InsertEntity(sTableName);

  // insert index
  for (int i = 0; i < iSchema.GetSize(); ++i) {
    const Column& column = iSchema.GetColumn(i);
    if (column.GetIsPrimary()) CreateIndex(sTableName, column.GetName());
  }
}

void Database::DropTable(const String& sTableName) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  _pIndexManager->DropIndex(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  pTable->Clear();
  delete pTable;
  OS::GetOS()->DeletePage(_iEntityPageIDMap[sTableName]);
  _iEntityMap.erase(sTableName);
  _iEntityPageIDMap.erase(sTableName);

  DeleteEntity(sTableName, _iEntityPageSlotIDMap[sTableName]);
}

void Database::RenameTable(const String& sOldTableName,
                           const String& sNewTableName) {
  Table* pTable = GetTable(sOldTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sOldTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  if (GetTable(sNewTableName) != nullptr) {
    auto e = TableExistException(sNewTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  DeleteEntity(sOldTableName, _iEntityPageSlotIDMap[sOldTableName]);
  InsertEntity(sNewTableName);

  _iEntityMap[sNewTableName] = pTable;
  _iEntityPageIDMap[sNewTableName] = _iEntityPageIDMap[sOldTableName];
  _iEntityMap.erase(sOldTableName);
  _iEntityPageIDMap.erase(sOldTableName);
}

std::vector<String> Database::GetTableNames() { return GetEntityNames(); }

std::vector<String> Database::GetColumnNames(const String& sTableName) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  return pTable->GetColumnNames();
}

std::vector<PageSlotID> Database::Search(
    const String& sTableName, Condition* pCond,
    const std::vector<Condition*>& iIndexCond) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  std::vector<PageSlotID> ans;
  if (iIndexCond.size() > 0) {
    int start = 0;
    if (pCond != nullptr) {
      ans = pTable->SearchRecord(pCond);
    } else {
      start = 1;
      IndexCondition* pIndexCond = dynamic_cast<IndexCondition*>(iIndexCond[0]);
      auto iName = pIndexCond->GetIndexName();
      auto iRange = pIndexCond->GetIndexRange();
      ans = _pIndexManager->GetIndex(iName.first, iName.second)
                ->Range(iRange.first, iRange.second);
    }
    for (Size i = start; i < iIndexCond.size(); ++i) {
      IndexCondition* pIndexCond = dynamic_cast<IndexCondition*>(iIndexCond[i]);
      auto iName = pIndexCond->GetIndexName();
      auto iRange = pIndexCond->GetIndexRange();
      ans =
          Intersection(ans, _pIndexManager->GetIndex(iName.first, iName.second)
                                ->Range(iRange.first, iRange.second));
    }
  } else {
    ans = pTable->SearchRecord(pCond);
  }

  return ans;
}

uint32_t Database::Delete(const String& sTableName, Condition* pCond,
                          const std::vector<Condition*>& iIndexCond) {
  auto iResVec = Search(sTableName, pCond, iIndexCond);
  Table* pTable = GetTable(sTableName);
  bool bHasIndex = _pIndexManager->HasIndex(sTableName);
  for (const auto& iPair : iResVec) {
    // Handle Delete on Index
    if (bHasIndex) {
      Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
      auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
      for (const auto& sCol : iColNames) {
        FieldID nPos = pTable->GetColPos(sCol);
        Field* pKey = pRecord->GetField(nPos);
        _pIndexManager->GetIndex(sTableName, sCol)->Delete(pKey, iPair);
      }
    }

    pTable->DeleteRecord(iPair.first, iPair.second);
  }
  return iResVec.size();
}

uint32_t Database::Update(const String& sTableName, Condition* pCond,
                          const std::vector<Condition*>& iIndexCond,
                          const std::vector<Transform>& iTrans) {
  auto iResVec = Search(sTableName, pCond, iIndexCond);
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  // check NOT-NULL / PRIMARY-KEY
  std::vector<String> iColNameVec = GetColumnNames(sTableName);
  for (int i = 0; i < iTrans.size(); ++i) {
    const String& sColName = iColNameVec[iTrans[i].GetColPos()];
    if (iTrans[i].GetField()->GetType() == FieldType::NULL_TYPE &&
        (!pTable->GetCanBeNull(sColName) || pTable->GetIsPrimary(sColName))) {
      auto e = FieldListException("Column should not be NULL");
      std::cout << e.what() << "\n";
      throw e;
    }
  }
  bool primaryKeyConflict = false;
  for (int i = 0; i < iTrans.size(); ++i) {
    const String& sColName = iColNameVec[iTrans[i].GetColPos()];
    if (pTable->GetIsPrimary(sColName)) {
      primaryKeyConflict = true;
      // check whether primary key conflicts with other records
      std::vector<PageSlotID> iDuplicated =
          _GetDuplicated(sTableName, sColName, iTrans[i].GetField());
#ifdef PRIMARY_KEY_DEBUG
      printf("iResVec.size() = %d\n", iResVec.size());
      printf("iDuplicated.size() = %d\n", iDuplicated.size());
      printf("Intersection(iResVec, iDuplicated).size() = %d\n",
             Intersection(iResVec, iDuplicated).size());
#endif
      if (iResVec.size() + iDuplicated.size() -
              Intersection(iResVec, iDuplicated).size() <=
          1) {
        primaryKeyConflict = false;
        break;
      }
    }
  }
  if (primaryKeyConflict) {
    // add exception here
    auto e = Exception("Primary key existed");
    std::cout << e.what() << "\n";
    throw e;
  }

  bool bHasIndex = _pIndexManager->HasIndex(sTableName);
  for (const auto& iPair : iResVec) {
    // Handle Delete on Index
    if (bHasIndex) {
      Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
      auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
      for (const auto& sCol : iColNames) {
        FieldID nPos = pTable->GetColPos(sCol);
        Field* pKey = pRecord->GetField(nPos);
        _pIndexManager->GetIndex(sTableName, sCol)->Delete(pKey, iPair);
      }
      delete pRecord;
    }

    pTable->UpdateRecord(iPair.first, iPair.second, iTrans);

    // Handle Insert on Index
    if (bHasIndex) {
      Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
      auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
      for (const auto& sCol : iColNames) {
        FieldID nPos = pTable->GetColPos(sCol);
        Field* pKey = pRecord->GetField(nPos);
        _pIndexManager->GetIndex(sTableName, sCol)->Insert(pKey, iPair);
      }
      delete pRecord;
    }
  }
  return iResVec.size();
}

PageSlotID Database::Insert(const String& sTableName,
                            const std::vector<String>& iRawVec) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  std::vector<std::string> iColNameVec = pTable->GetColumnNames();
  if (iColNameVec.size() != iRawVec.size()) {
    auto e = FieldListException("Column num does not correspond");
    std::cout << e.what() << "\n";
    throw e;
  }
  // check null
  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    if (iRawVec[i] == "NULL" &&
        (!pTable->GetCanBeNull(sColName) || pTable->GetIsPrimary(sColName))) {
      auto e = FieldListException("Column should not be NULL");
      std::cout << e.what() << "\n";
      throw e;
    }
  }
  // check primary key
  bool primaryKeyConflict = false;
  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    if (pTable->GetIsPrimary(sColName)) {
      // check whether primary key conflicts with other records
      primaryKeyConflict = true;
      FieldType colType = pTable->GetType(sColName);
      Field* pField = BuildField(iRawVec[i], colType);
      if (_GetDuplicated(sTableName, sColName, pField).size() == 0) {
        primaryKeyConflict = false;
        delete pField;
        break;
      }
      delete pField;
    }
  }
  if (primaryKeyConflict) {
    // add exception here
    auto e = Exception("Primary key existed");
    std::cout << e.what() << "\n";
    throw e;
  }

  Record* pRecord = pTable->EmptyRecord();
  try {
    pRecord->Build(iRawVec);
  } catch (const Exception& e) {
    delete pRecord;
    throw e;
  }

  PageSlotID iPair = pTable->InsertRecord(pRecord);

  // Handle Insert on Index
  if (_pIndexManager->HasIndex(sTableName)) {
    auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
    for (const auto& sCol : iColNames) {
      FieldID nPos = pTable->GetColPos(sCol);
      Field* pKey = pRecord->GetField(nPos);
      _pIndexManager->GetIndex(sTableName, sCol)->Insert(pKey, iPair);
    }
  }

  delete pRecord;
  return iPair;
}

PageSlotID Database::Insert(const String& sTableName,
                            const std::vector<Field*>& iValueVec) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  std::vector<std::string> iColNameVec = pTable->GetColumnNames();
  if (iColNameVec.size() != iValueVec.size()) {
    auto e = FieldListException("Column num does not correspond");
    std::cout << e.what() << "\n";
    throw e;
  }

  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    if (iValueVec[i]->GetType() == FieldType::NULL_TYPE &&
        (!pTable->GetCanBeNull(sColName) || pTable->GetIsPrimary(sColName))) {
      auto e = FieldListException("Column should not be NULL");
      std::cout << e.what() << "\n";
      throw e;
    }
  }

  bool primaryKeyConflict = false;
  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    if (pTable->GetIsPrimary(sColName)) {
      primaryKeyConflict = true;
      if (_GetDuplicated(sTableName, sColName, iValueVec[i]).size() == 0) {
        primaryKeyConflict = false;
        break;
      }
    }
  }
  if (primaryKeyConflict) {
    // add exception here
    auto e = Exception("Primary key existed");
    std::cout << e.what() << "\n";
    throw e;
  }

  Record* pRecord = pTable->EmptyRecord();
  try {
    pRecord->Build(iValueVec);
  } catch (const Exception& e) {
    delete pRecord;
    throw e;
  }

  PageSlotID iPair = pTable->InsertRecord(pRecord);

  // Handle Insert on Index
  if (_pIndexManager->HasIndex(sTableName)) {
    auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
    for (const auto& sCol : iColNames) {
      FieldID nPos = pTable->GetColPos(sCol);
      Field* pKey = pRecord->GetField(nPos);
      _pIndexManager->GetIndex(sTableName, sCol)->Insert(pKey, iPair);
    }
  }

  delete pRecord;
  return iPair;
}

std::vector<PageSlotID> Database::_GetDuplicated(const String& sTableName,
                                                const String& sColName,
                                                Field* pField) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  FieldID colPos = pTable->GetColPos(sColName);
  Field *pLow = pField->Clone(), *pHigh = pField->Clone();
  pHigh->Add();
  Condition* pCond = nullptr;
  std::vector<Condition*> iIndexCond{};
  if (IsIndex(sTableName, sColName)) {
    iIndexCond.push_back(new IndexCondition(sTableName, sColName, pLow, pHigh));
  } else {
    pCond = new RangeCondition(colPos, pLow, pHigh);
  }
  std::vector<PageSlotID> iPageSlotIDVec =
      Search(sTableName, pCond, iIndexCond);

#ifdef PRIMARY_KEY_DEBUG
  printf("\n%s.%s\n", sTableName.c_str(), sColName.c_str());
  printf("[%s, %s)\n", pLow->ToString().c_str(), pHigh->ToString().c_str());
  printf("Size = %d\n\n", int(iPageSlotIDVec.size()));
#endif

  if (pCond) delete pCond;
  for (auto pCond : iIndexCond) delete pCond;

  return iPageSlotIDVec;
}

void Database::CreateIndex(const String& sTableName, const String& sColName) {
  auto iAll = Search(sTableName, nullptr, {});
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  FieldType iType = pTable->GetType(sColName);
  _pIndexManager->AddIndex(sTableName, sColName, iType);
  // Handle Exists Data
  for (const auto& iPair : iAll) {
    FieldID nPos = pTable->GetColPos(sColName);
    Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
    Field* pKey = pRecord->GetField(nPos);
    _pIndexManager->GetIndex(sTableName, sColName)->Insert(pKey, iPair);
    delete pRecord;
  }
}

void Database::DropIndex(const String& sTableName, const String& sColName) {
  auto iAll = Search(sTableName, nullptr, {});
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  for (const auto& iPair : iAll) {
    FieldID nPos = pTable->GetColPos(sColName);
    Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
    Field* pKey = pRecord->GetField(nPos);
    _pIndexManager->GetIndex(sTableName, sColName)->Delete(pKey, iPair);
    delete pRecord;
  }
  _pIndexManager->DropIndex(sTableName, sColName);
}

bool Database::IsIndex(const String& sTableName, const String& sColName) {
  return _pIndexManager->IsIndex(sTableName, sColName);
}

Index* Database::GetIndex(const String& sTableName, const String& sColName) {
  return _pIndexManager->GetIndex(sTableName, sColName);
}

std::vector<Record*> Database::GetIndexInfos() {
  std::vector<Record*> iVec{};
  for (const auto& iPair : _pIndexManager->GetIndexInfos()) {
    FixedRecord* pInfo =
        new FixedRecord(4,
                        {FieldType::CHAR_TYPE, FieldType::CHAR_TYPE,
                         FieldType::CHAR_TYPE, FieldType::INT_TYPE},
                        {TABLE_NAME_SIZE, COLUMN_NAME_SIZE, 10, 4});
    pInfo->SetField(0, new CharField(iPair.first));
    pInfo->SetField(1, new CharField(iPair.second));
    pInfo->SetField(
        2,
        new CharField(toString(GetTable(iPair.first)->GetType(iPair.second))));
    pInfo->SetField(3,
                    new IntField(GetTable(iPair.first)->GetSize(iPair.second)));

    iVec.push_back(pInfo);
  }
  return iVec;
}

void Database::Clear() {
  _pIndexManager->Clear();
  // load tables to delete pages later
  for (auto iter : _iEntityPageIDMap)
    if (_iEntityMap.find(iter.first) == _iEntityMap.end() ||
        _iEntityMap[iter.first] == nullptr) {
      _iEntityMap[iter.first] = new Table(iter.second);
    }
  EntityManager::Clear();
}

EntityType Database::GetEntityType() const { return EntityType::DATABASE_TYPE; }

void Database::AddPrimaryKey(const String& sTableName, const std::vector<String> sColName){
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  //因为现有pk的信息是正确的，所以只需要检查现有信息
  //获取所有需要检查的新增列的信息
  std::vector<String> sColNameVec;
  for (int i = 0; i < sColName.size(); i ++){
    if(!pTable->GetIsPrimary(sColName[i])) sColNameVec.push_back(sColName[i]);
  }
  if(sColNameVec.size() == 0) return;

  std::vector<PageSlotID> psidVec =  pTable->SearchRecord(nullptr);
  MemResult* result = new MemResult(pTable->GetColumnNames());
  for(auto& psid: psidVec){
    result->PushBack(pTable->GetRecord(psid.first, psid.second));
  }
  
  //如果已经有其他外键，那么一定不需要检查新外键的重复性
  bool needCheckDuplication = true;
  std::vector<std::string> iColNameVec = pTable->GetColumnNames();
  for(int i = 0; i < iColNameVec.size(); i ++){
    if(pTable->GetIsPrimary(iColNameVec[i])){
      needCheckDuplication = false;
      break;
    }
  }
  //检查重复性和null性
  if(needCheckDuplication && _CheckHaveDuplicatePK(result, sColNameVec)){
    throw AlterException("the new Primary Key column cannot be duplicated");
  }
  if(_CheckHaveNullPK(result, sColNameVec)){
    throw AlterException("the new Primary Key column cannot be Null");
  }
  pTable->AddPrimaryKey(sColNameVec);
  if(result) delete result;
  return;
}


bool Database::_CheckHaveNullPK(MemResult* result, const std::vector<String>& sColNameVec){

  std::map<String, int> iColPosMap;
  for(int i = 0; i < sColNameVec.size(); i ++){
    bool flag = false;
    for(int j = 0; j < result->GetHeaderSize(); i ++){
      if(sColNameVec[i] == result->GetHeader(j)){
        flag = true;
        iColPosMap[sColNameVec[i]] = j;
        break;
      }
    }
    if(!flag){
      printf("the column name used to alter table PK should be a exist column name\n");
      throw Exception();
    }
  }
  
  for (int j = 0; j < result->GetDataSize(); j ++) {
    for (uint32_t i = 0; i < sColNameVec.size(); i++) {
      if(result->GetFieldString(j, i) == "NULL"){
        if(result) delete result;
        return true;
      }
    }
  }
  if(result) delete result;
  return false;
}


bool Database::_CheckHaveDuplicatePK(MemResult* result, const std::vector<String>& sColNameVec){
  
  std::map<String, int> iColPosMap;
  for(int i = 0; i < sColNameVec.size(); i ++){
    bool flag = false;
    for(int j = 0; j < result->GetHeaderSize(); j ++){
      if(result->GetHeader(j) == sColNameVec[i]){
        flag = true;
        iColPosMap[sColNameVec[i]] = j;
        break;
      }
    }
    if(!flag){
      printf("the column name used to alter table PK should be a exist column name\n");
      throw Exception();
    }
  }
  
  for (uint32_t i = 0; i < result->GetDataSize() - 1; i ++) {
    printf("%s\n",sColNameVec[0].data());
    for(uint32_t j = i + 1; j < result->GetDataSize(); j ++){
      bool duplicate = true;
      for(const String& colName: sColNameVec){
        if(result->GetFieldString(i, iColPosMap[colName]) != result->GetFieldString(j, iColPosMap[colName])){
              duplicate = false;
              break;
        }
      }
      if(duplicate) return true;
    }
  }
  return false;
}
}  // namespace dbtrain_mysql