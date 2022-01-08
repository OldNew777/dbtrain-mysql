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
  // check foreign key
  // insert foreign key
  for (int i = 0; i < iSchema.GetSize(); ++i) {
    const Column& column = iSchema.GetColumn(i);
    if (column.GetForeignKeyVec().size() != 0) {
      for (auto& tPair : column.GetForeignKeyVec()) {
        String fTableName = tPair.first;
        String fColName = tPair.second;
        // check reference table is null
        if (_CheckHaveNull(fTableName, fColName)) {
          printf("reference column should not be null\n");
          throw ForeignKeyException("reference column should not be null");
        }
      }
      // insert local shadow table
    }
    // printf("3\n");
  }

  // Create table and cache it
  TablePage* pPage = new TablePage(iSchema);
  Table* pTable = new Table(pPage);
  _iEntityMap[sTableName] = pTable;
  _iEntityPageIDMap[sTableName] = pPage->GetPageID();

  // create shadowpage
  // create a shadow table

  std::vector<Column> shadowTableColVec;
  shadowTableColVec.push_back(Column(SHADOW_STATUS_NAME, FieldType::CHAR_TYPE,
                                     false, false, SHADOW_STATUS_SIZE,
                                     {}));  // status
  shadowTableColVec.push_back(Column(SHADOW_LOCAL_COLUMN_NAME,
                                     FieldType::CHAR_TYPE, false, false,
                                     COLUMN_NAME_SIZE, {}));  //该表某一列的名字
  shadowTableColVec.push_back(Column(SHADOW_FOREIGN_TABLE_NAME,
                                     FieldType::CHAR_TYPE, false, false,
                                     TABLE_NAME_SIZE, {}));  //
  shadowTableColVec.push_back(Column(SHADOW_FOREIGN_COLUMN_NAME,
                                     FieldType::CHAR_TYPE, false, false,
                                     COLUMN_NAME_SIZE, {}));  //
  TablePage* shadowPage = new TablePage(Schema(shadowTableColVec));
  Table* shadowTable = new Table(shadowPage);
  _iEntityMap["@" + sTableName] = shadowTable;
  _iEntityPageIDMap["@" + sTableName] = shadowPage->GetPageID();

  // insert entity to page
  InsertEntity(sTableName);
  InsertEntity("@" + sTableName);

  // insert index
  for (int i = 0; i < iSchema.GetSize(); ++i) {
    const Column& column = iSchema.GetColumn(i);
    if (column.GetIsPrimary()) CreateIndex(sTableName, column.GetName());
  }

  // insert foreign key
  for (int i = 0; i < iSchema.GetSize(); ++i) {
    const Column& column = iSchema.GetColumn(i);
    if (column.GetForeignKeyVec().size() != 0) {
      for (auto& tPair : column.GetForeignKeyVec()) {
        String fTableName = tPair.first;
        String fColName = tPair.second;
        printf("%s %s\n", fTableName.data(), fColName.data());
        // insert local shadow table
        std::vector<Field*> LocalVec;
        LocalVec.push_back(new CharField(SHADOW_STATUS_FOREIGN_KEY));
        LocalVec.push_back(new CharField(column.GetName()));
        LocalVec.push_back(new CharField(fTableName));
        LocalVec.push_back(new CharField(fColName));
        Insert("@" + sTableName, LocalVec);
        // insert reference shadow table
        std::vector<Field*> ForeignVec;
        ForeignVec.push_back(new CharField(SHADOW_STATUS_REFERED_KEY));
        ForeignVec.push_back(new CharField(fColName));
        ForeignVec.push_back(new CharField(sTableName));
        ForeignVec.push_back(new CharField(column.GetName()));
        // printf("2\n");
        Insert("@" + fTableName, ForeignVec);
        _UpdateReferedKey(fTableName, fColName);
      }
      GetTable(sTableName)->AddForeignKey(column.GetName());
    }
    // printf("3\n");
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
    if (pTable->GetIsPrimary(sColName) || pTable->GetIsUnique(sColName)) {
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
    auto e = Exception("Unique Key Exists");
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
    if (pTable->GetIsPrimary(sColName) || pTable->GetIsUnique(sColName)) {
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
    auto e = Exception("Unique key existed");
    std::cout << e.what() << "\n";
    throw e;
  }

  // check foreignkey
  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    if (pTable->GetIsForeign(sColName)) {
      // check whether primary key conflicts with other records
      FieldType colType = pTable->GetType(sColName);
      Field* pField = BuildField(iRawVec[i], colType);
      std::vector<std::pair<String, String>> fPairVec =
          GetForeignKey(sTableName, sColName);
      // printf("FK of %s: %s %s\n", sColName.data(), fPair.first.data(),
      // fPair.second.data());
      for (auto& fPair : fPairVec) {
        if (!_CheckForeignKey(fPair.first, fPair.second, pField)) {
          printf("key out of range:%s\n", pField->ToString().data());
          delete pField;
          throw ForeignKeyException();
        }
      }

      delete pField;
    }
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
    if (pTable->GetIsPrimary(sColName) || pTable->GetIsUnique(sColName)) {
      primaryKeyConflict = true;
      if (_GetDuplicated(sTableName, sColName, iValueVec[i]).size() == 0) {
        primaryKeyConflict = false;
        break;
      }
    }
  }
  if (primaryKeyConflict) {
    // add exception here
    auto e = Exception("Unique key existed");
    std::cout << e.what() << "\n";
    throw e;
  }
  // check foreignkey
  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    if (pTable->GetIsForeign(sColName)) {
      // check whether primary key conflicts with other records

      std::vector<std::pair<String, String>> fPairVec =
          GetForeignKey(sTableName, sColName);
      // printf("FK of %s: %s %s\n", sColName.data(), fPair.first.data(),
      // fPair.second.data());
      for (auto& fPair : fPairVec) {
        if (!_CheckForeignKey(fPair.first, fPair.second, iValueVec[i])) {
          printf("key out of range:%d\n", iValueVec[i]->ToString().data());
          throw ForeignKeyException();
        }
      }
    }
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

void Database::AddPrimaryKey(const String& sTableName,
                             const std::vector<String> sColName) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  //因为现有pk的信息是正确的，所以只需要检查现有信息
  //获取所有需要检查的新增列的信息
  std::vector<String> sColNameVec;
  for (int i = 0; i < sColName.size(); i++) {
    if (!pTable->GetIsPrimary(sColName[i])) sColNameVec.push_back(sColName[i]);
  }
  if (sColNameVec.size() == 0) return;
  std::vector<PageSlotID> psidVec = pTable->SearchRecord(nullptr);
  Result* result = new MemResult(pTable->GetColumnNames());
  for (auto& psid : psidVec) {
    result->PushBack(pTable->GetRecord(psid.first, psid.second));
  }
  //如果已经有其他外键，那么一定不需要检查新外键的重复性
  bool needCheckDuplication = true;
  std::vector<std::string> iColNameVec = pTable->GetColumnNames();
  for (int i = 0; i < iColNameVec.size(); i++) {
    if (pTable->GetIsPrimary(iColNameVec[i])) {
      needCheckDuplication = false;
      break;
    }
  }
  //检查重复性和null性
  if (needCheckDuplication &&
      _CheckHaveDuplicate((MemResult*)result, sColNameVec)) {
    throw AlterException("the new Primary Key column cannot be duplicated");
  }
  for (auto& colName : sColName) {
    if (_CheckHaveNull(sTableName, colName)) {
      throw AlterException("the new Primary Key column cannot be Null");
    }
  }
  pTable->AddPrimaryKey(sColNameVec);
  // TODO: a space bug
  // if(result != nullptr) delete result;
  return;
}

void Database::DropPrimaryKey(const String& sTableName,
                              const String& sColName) {
  Table* pTable = GetTable(sTableName);
  pTable->DropPrimaryKey(sColName);
  // std::pair<String, String> sPair = GetForeignKey(sTableName, sColName);
  // _UpdateReferedKey(sPair.first, sPair.second);
}
bool Database::_CheckHaveNull(const String& fTableName,
                              const String& fColName) {
  Table* fTable = GetTable(fTableName);
  if (fTable == nullptr) {
    auto e = TableNotExistException(fTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  if (!fTable->GetCanBeNull(fColName) || fTable->GetIsPrimary(fColName)) {
    return false;
  }
  // printf("into\n");
  std::vector<PageSlotID> fpsidVec = fTable->SearchRecord(nullptr);
  MemResult* result = new MemResult(fTable->GetColumnNames());
  for (auto& psid : fpsidVec)
    result->PushBack(fTable->GetRecord(psid.first, psid.second));
  FieldID colPos = fTable->GetColPos(fColName);
  for (int j = 0; j < result->GetDataSize(); j++) {
    if (result->GetFieldString(j, colPos) == "NULL") {
      if (result) delete result;
      return true;
    }
  }
  if (result) delete result;
  return false;
}

bool Database::_CheckHaveDuplicate(MemResult* result,
                                   const std::vector<String>& sColNameVec) {
  std::map<String, int> iColPosMap;
  for (int i = 0; i < sColNameVec.size(); i++) {
    bool flag = false;
    for (int j = 0; j < result->GetHeaderSize(); j++) {
      if (result->GetHeader(j) == sColNameVec[i]) {
        flag = true;
        iColPosMap[sColNameVec[i]] = j;
        break;
      }
    }
    if (!flag) {
      printf(
          "the column name used to alter table PK should be a exist column "
          "name\n");
      throw Exception();
    }
  }

  for (uint32_t i = 0; i < result->GetDataSize() - 1; i++) {
    for (uint32_t j = i + 1; j < result->GetDataSize(); j++) {
      bool duplicate = true;
      for (const String& colName : sColNameVec) {
        if (result->GetFieldString(i, iColPosMap[colName]) !=
            result->GetFieldString(j, iColPosMap[colName])) {
          duplicate = false;
          break;
        }
      }
      if (duplicate) return true;
    }
  }
  return false;
}
std::vector<std::pair<String, String>> Database::GetReferedKey(
    const String& sTableName, const String& sColName) {
  Table* pTable = GetTable("@" + sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  std::vector<std::pair<String, String>> retVec;
  FieldID colPos = pTable->GetColPos(SHADOW_LOCAL_COLUMN_NAME);
  std::vector<PageSlotID> iPageSlotIDVec = pTable->SearchRecord(nullptr);
  MemResult* res =
      new MemResult({SHADOW_STATUS_NAME, SHADOW_LOCAL_COLUMN_NAME,
                     SHADOW_FOREIGN_TABLE_NAME, SHADOW_FOREIGN_COLUMN_NAME});
  for (auto& psid : iPageSlotIDVec) {
    res->PushBack(pTable->GetRecord(psid.first, psid.second));
  }
  for (int i = 0; i < res->GetDataSize(); i++) {
    // printf("%s %s\n", res->GetFieldString(i, 0).data(),
    // res->GetFieldString(i, 1).data());
    if (res->GetFieldString(i, 0) != SHADOW_STATUS_REFERED_KEY ||
        res->GetFieldString(i, 1) != sColName)
      continue;
    retVec.push_back(
        std::make_pair(res->GetFieldString(i, 2), res->GetFieldString(i, 3)));
  }
  // if (retVec.size() == 0) {
  //   printf("there should be a refered key in shadow table\n");
  //   throw ForeignKeyException();
  // }
}
std::vector<std::pair<String, String>> Database::GetForeignKey(
    const String& sTableName, const String& sColName) {
  Table* pTable = GetTable("@" + sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  std::vector<std::pair<String, String>> retVec;
  FieldID colPos = pTable->GetColPos(SHADOW_LOCAL_COLUMN_NAME);
  std::vector<PageSlotID> iPageSlotIDVec = pTable->SearchRecord(nullptr);
  MemResult* res =
      new MemResult({SHADOW_STATUS_NAME, SHADOW_LOCAL_COLUMN_NAME,
                     SHADOW_FOREIGN_TABLE_NAME, SHADOW_FOREIGN_COLUMN_NAME});
  for (auto& psid : iPageSlotIDVec) {
    res->PushBack(pTable->GetRecord(psid.first, psid.second));
  }
  for (int i = 0; i < res->GetDataSize(); i++) {
    // printf("%s %s\n", res->GetFieldString(i, 0).data(),
    // res->GetFieldString(i, 1).data());
    if (res->GetFieldString(i, 0) != SHADOW_STATUS_FOREIGN_KEY ||
        res->GetFieldString(i, 1) != sColName)
      continue;
    retVec.push_back(
        std::make_pair(res->GetFieldString(i, 2), res->GetFieldString(i, 3)));
  }
  // if (retVec.size() == 0) {
  //   printf("there should be a foreign key in shadow table\n");
  //   throw ForeignKeyException();
  // }
  return retVec;
}

std::vector<std::vector<String>> Database::GetTableReferedKeys(
    const String& sTableName) {  //
  Table* pTable = GetTable("@" + sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  std::vector<std::vector<String>> referedKeyVec;
  FieldID colPos = pTable->GetColPos(SHADOW_LOCAL_COLUMN_NAME);
  std::vector<PageSlotID> iPageSlotIDVec = pTable->SearchRecord(nullptr);
  MemResult* res =
      new MemResult({SHADOW_STATUS_NAME, SHADOW_LOCAL_COLUMN_NAME,
                     SHADOW_FOREIGN_TABLE_NAME, SHADOW_FOREIGN_COLUMN_NAME});
  for (auto& psid : iPageSlotIDVec) {
    res->PushBack(pTable->GetRecord(psid.first, psid.second));
  }
  for (int i = 0; i < res->GetDataSize(); i++) {
    // printf("%s %s\n", res->GetFieldString(i, 0).data(),
    // res->GetFieldString(i, 1).data());
    if (res->GetFieldString(i, 0) != SHADOW_STATUS_REFERED_KEY) continue;
    referedKeyVec.push_back(std::vector<String>());
    referedKeyVec.back().push_back(res->GetFieldString(i, 1));
    referedKeyVec.back().push_back(res->GetFieldString(i, 2));
    referedKeyVec.back().push_back(res->GetFieldString(i, 3));
  }
  return referedKeyVec;
}
std::vector<std::vector<String>> Database::GetTableForeignKeys(
    const String& sTableName) {  //
  Table* pTable = GetTable("@" + sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  std::vector<std::vector<String>> foreignKeyVec;
  FieldID colPos = pTable->GetColPos(SHADOW_LOCAL_COLUMN_NAME);
  std::vector<PageSlotID> iPageSlotIDVec = pTable->SearchRecord(nullptr);
  MemResult* res =
      new MemResult({SHADOW_STATUS_NAME, SHADOW_LOCAL_COLUMN_NAME,
                     SHADOW_FOREIGN_TABLE_NAME, SHADOW_FOREIGN_COLUMN_NAME});
  for (auto& psid : iPageSlotIDVec) {
    res->PushBack(pTable->GetRecord(psid.first, psid.second));
  }
  for (int i = 0; i < res->GetDataSize(); i++) {
    // printf("%s %s\n", res->GetFieldString(i, 0).data(),
    // res->GetFieldString(i, 1).data());
    if (res->GetFieldString(i, 0) != SHADOW_STATUS_FOREIGN_KEY) continue;
    foreignKeyVec.push_back(std::vector<String>());
    foreignKeyVec.back().push_back(res->GetFieldString(i, 1));
    foreignKeyVec.back().push_back(res->GetFieldString(i, 2));
    foreignKeyVec.back().push_back(res->GetFieldString(i, 3));
  }
  return foreignKeyVec;
}

bool Database::_CheckForeignKey(const String& fTableName,
                                const String& fColName,
                                Field* pField) {  // false-wrong true-corrct
  // printf("%s %s on %s\n", fTableName.data(), fColName.data(),
  // pField->ToString().data());
  if (pField->ToString() == "NULL") {  //外键可为null
    return true;
  }
  Table* pTable = GetTable(fTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(fTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  std::vector<PageSlotID> psidVec = pTable->SearchRecord(nullptr);
  MemResult* res = new MemResult(pTable->GetColumnNames());
  for (auto& psid : psidVec) {
    res->PushBack(pTable->GetRecord(psid.first, psid.second));
  }
  FieldID colPos = pTable->GetColPos(fColName);
  bool flag = false;
  for (int i = 0; i < res->GetDataSize(); i++) {
    if (res->GetFieldString(i, colPos) == pField->ToString()) {
      flag = true;
      break;
    }
  }
  return flag;
}

/**
  @brief 删除sTable的一行记录
  @param lTableName 要删除的表名
  @return 删除的个数
*/
uint32_t Database::_DropShadowTableKey(const String& lTableName,
                                       const String& statusMode,
                                       const String& lColName,
                                       const String& fTableName,
                                       const String& fColName) {
  if (statusMode != SHADOW_STATUS_FOREIGN_KEY &&
      statusMode != SHADOW_STATUS_REFERED_KEY) {
    printf("status Mode Wrong\n");
    throw ForeignKeyException("status Mode Wrong");
  }

  Table* pTable = GetTable("@" + lTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException("@" + lTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  std::vector<Condition*> iCond{};

  // type condition
  FieldID tColPos = pTable->GetColPos(SHADOW_STATUS_NAME);
  Field* tLow = new CharField(statusMode);
  Field* tHigh = tLow->Clone();
  tHigh->Add();
  Condition* tCond = new RangeCondition(tColPos, tLow, tHigh);
  if (tCond != nullptr) iCond.push_back(tCond);

  if (lColName != "") {
    // local Colname condition
    FieldID cColPos = pTable->GetColPos(SHADOW_LOCAL_COLUMN_NAME);
    Field* cLow = new CharField(lColName);
    Field* cHigh = cLow->Clone();
    cHigh->Add();
    Condition* cCond = new RangeCondition(cColPos, cLow, cHigh);
    if (cCond != nullptr) iCond.push_back(cCond);
  }

  if (fTableName != "") {
    // foreign tablename condition
    FieldID ftColPos = pTable->GetColPos(SHADOW_FOREIGN_TABLE_NAME);
    Field* ftLow = new CharField(fTableName);
    Field* ftHigh = ftLow->Clone();
    ftHigh->Add();
    Condition* ftCond = new RangeCondition(ftColPos, ftLow, ftHigh);
    if (ftCond != nullptr) iCond.push_back(ftCond);
  }

  if (fColName != "") {
    // foreign colname condition
    FieldID fcColPos = pTable->GetColPos(SHADOW_FOREIGN_COLUMN_NAME);
    Field* fcLow = new CharField(fColName);
    Field* fcHigh = fcLow->Clone();
    fcHigh->Add();
    Condition* fcCond = new RangeCondition(fcColPos, fcLow, fcHigh);
    if (fcCond != nullptr) iCond.push_back(fcCond);
  }

  Condition* cond = new AndCondition(iCond);
  uint32_t ret = Delete("@" + lTableName, cond, {});

  for (auto tmpCond : iCond) delete tmpCond;

  if (statusMode == SHADOW_STATUS_FOREIGN_KEY) {
    GetTable(lTableName)->DropForeignKey(lColName);
  } else if (statusMode == SHADOW_STATUS_REFERED_KEY) {
    _UpdateReferedKey(fTableName, fColName);
  }
  return ret;
}
void Database::AddForeignKey(const String& lTableName, const String& lColName,
                             const String& fTableName,
                             const std::vector<String>& fColNameVec) {
  // TODO: ADD FOREIGNKEY
  Table* lTable = GetTable(lTableName);
  Table* fTable = GetTable(fTableName);
  if (lTable == nullptr) {
    auto e = TableNotExistException(lTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  if (fTable == nullptr) {
    auto e = TableNotExistException(fTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  // check fk validation
  for (auto& fColName : fColNameVec) {
    std::vector<PageSlotID> psidVec = lTable->SearchRecord(nullptr);
    MemResult* lRes = new MemResult(lTable->GetColumnNames());
    for (auto& psid : psidVec)
      lRes->PushBack(lTable->GetRecord(psid.first, psid.second));
    FieldID colPos = lTable->GetColPos(lColName);
    for (int i = 0; i < lRes->GetDataSize(); i++) {
      if (!_CheckForeignKey(fTableName, fColName, lRes->GetField(i, colPos))) {
        if (lRes) delete lRes;
        printf("Foreign key should be in range of refernce key\n");
        throw ForeignKeyException(
            "Foreign key should be in range of refernce key");
      }
    }
    if (lRes) delete lRes;
    // check type
    if (lTable->GetType(lColName) != fTable->GetType(fColName)) {
      printf("foreign key should have same type\n");
      throw ForeignKeyException("foreign key should have same type");
    }
    // check reference not null
    if (_CheckHaveNull(fTableName, fColName)) {
      printf("reference key cannot be null\n");
      throw ForeignKeyException("reference key cannot be null");
    }

    // add this table foreign key
    std::vector<Field*> LocalVec;
    LocalVec.push_back(new CharField(SHADOW_STATUS_FOREIGN_KEY));
    LocalVec.push_back(new CharField(lColName));
    LocalVec.push_back(new CharField(fTableName));
    LocalVec.push_back(new CharField(fColName));
    Insert("@" + lTableName, LocalVec);
    // insert reference shadow table
    std::vector<Field*> ForeignVec;
    ForeignVec.push_back(new CharField(SHADOW_STATUS_REFERED_KEY));
    ForeignVec.push_back(new CharField(fColName));
    ForeignVec.push_back(new CharField(lTableName));
    ForeignVec.push_back(new CharField(lColName));
    // printf("2\n");
    Insert("@" + fTableName, ForeignVec);
    lTable->AddForeignKey(lColName);
    _UpdateReferedKey(fTableName, fColName);
  }
}
void Database::DropFroeignKey(const String& sTableName,
                              const String& sColName) {
  std::vector<std::pair<String, String>> fPairVec =
      GetForeignKey(sTableName, sColName);
  // drop ref key of foreign table
  for (auto fPair : fPairVec) {
    _DropShadowTableKey(fPair.first, SHADOW_STATUS_REFERED_KEY, fPair.second,
                        sTableName, sColName);
    // frop for key of local table
    uint32_t res = _DropShadowTableKey(sTableName, SHADOW_STATUS_FOREIGN_KEY,
                                       sColName, fPair.first, fPair.second);
    // printf("%s %s %s %s %s\n", sTableName.data(),
    // SHADOW_STATUS_FOREIGN_KEY.data(),
    //   sColName.data(),fPair.first.data(),fPair.second.data());
    _UpdateReferedKey(fPair.first, fPair.second);
  }
}
void Database::DropTableForeignKey(const String& sTableName) {
  std::vector<std::vector<String>> refPairVec = GetTableReferedKeys(sTableName);
  std::vector<std::vector<String>> forPairVec = GetTableForeignKeys(sTableName);

  std::map<String, int> tmpMap;
  for (auto& tVec : refPairVec) {
    _DropShadowTableKey(tVec[1], SHADOW_STATUS_REFERED_KEY, tVec[2], sTableName,
                        tVec[0]);
    _UpdateReferedKey(tVec[1], tVec[2]);
  }

  for (auto& tVec : forPairVec) {
    _DropShadowTableKey(tVec[1], SHADOW_STATUS_FOREIGN_KEY, tVec[2], sTableName,
                        tVec[0]);
    _UpdateReferedKey(tVec[1], tVec[2]);
  }
}
void Database::_UpdateReferedKey(const String& fTableName,
                                 const String& fColname) {
  Table* fTable = GetTable("@" + fTableName);
  Table* sTable = GetTable(fTableName);
  if (fTable == nullptr) {
    auto e = TableNotExistException("@" + fTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  if (sTable == nullptr) {
    auto e = TableNotExistException(fTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  // printf("into\n");
  std::vector<String> colNames = sTable->GetColumnNames();
  std::map<String, bool> sMap;
  for (auto& col : colNames) {
    sMap[col] = false;
  }
  std::vector<PageSlotID> fpsidVec = fTable->SearchRecord(nullptr);
  MemResult* result = new MemResult(fTable->GetColumnNames());
  for (auto& psid : fpsidVec)
    result->PushBack(fTable->GetRecord(psid.first, psid.second));
  for (int j = 0; j < result->GetDataSize(); j++) {
    if (result->GetFieldString(j, 0) != SHADOW_STATUS_REFERED_KEY) continue;
    sMap[result->GetFieldString(j, 1)] = true;
  }
  for (auto& iPair : sMap) {
    if (iPair.second) {
      sTable->AddReferedKey(iPair.first);
    } else {
      sTable->DropReferedKey(iPair.first);
    }
  }

  if (result) delete result;
}
void Database::AddUniqueKey(const String& sTableName, const String& sColName) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  std::vector<String> sColNameVec;
  sColNameVec.push_back(sColName);
  std::vector<PageSlotID> psidVec = pTable->SearchRecord(nullptr);
  Result* result = new MemResult(pTable->GetColumnNames());
  for (auto& psid : psidVec) {
    result->PushBack(pTable->GetRecord(psid.first, psid.second));
  }
  if (_CheckHaveDuplicate((MemResult*)result, sColNameVec)) {
    if (result) delete result;
    throw AlterException("the new Unique Key column cannot be duplicated");
  }
  pTable->AddUniqueKey(sColName);
  if (result) delete result;
}
}  // namespace dbtrain_mysql