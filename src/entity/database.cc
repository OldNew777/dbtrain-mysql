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
    printf("Table '%s' existed\n", sTableName.c_str());
    throw TableExistException(sTableName);
  }

  // Create table and cache it
  TablePage* pPage = new TablePage(iSchema);
  Table* pTable = new Table(pPage);
  _iEntityMap[sTableName] = pTable;
  _iEntityPageIDMap[sTableName] = pPage->GetPageID();

  // insert entity to page
  InsertEntity(sTableName);
}

void Database::DropTable(const String& sTableName) {
  Table* pTable = GetTable(sTableName);
  _pIndexManager->DropIndex(sTableName);
  if (pTable == nullptr) {
    printf("Table '%s' not existed\n", sTableName.c_str());
    throw TableNotExistException(sTableName);
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
    printf("Table '%s' not existed\n", sOldTableName.c_str());
    throw TableNotExistException(sOldTableName);
  }
  if (GetTable(sNewTableName) != nullptr) {
    printf("Table '%s' existed\n", sNewTableName.c_str());
    throw TableExistException(sNewTableName);
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
  return pTable->GetColumnNames();
}

std::vector<PageSlotID> Database::Search(
    const String& sTableName, Condition* pCond,
    const std::vector<Condition*>& iIndexCond) {
  if (pCond != nullptr && iIndexCond.size() > 0) {
    printf("Search function accept exclusive arguments\n");
    throw Exception("Search function accept exclusive arguments");
  }

  Table* pTable = GetTable(sTableName);
  std::vector<PageSlotID> ans;
  if (iIndexCond.size() > 0) {
    IndexCondition* pIndexCond = dynamic_cast<IndexCondition*>(iIndexCond[0]);
    if (pIndexCond == nullptr)
      throw NullptrException("Search", "IndexCondition should not be nullptr");
    auto iName = pIndexCond->GetIndexName();
    auto iRange = pIndexCond->GetIndexRange();
    std::vector<PageSlotID> iRes =
        _pIndexManager->GetIndex(iName.first, iName.second)
            ->Range(iRange.first, iRange.second);
    for (Size i = 1; i < iIndexCond.size(); ++i) {
      IndexCondition* pIndexCond = dynamic_cast<IndexCondition*>(iIndexCond[i]);
      auto iName = pIndexCond->GetIndexName();
      auto iRange = pIndexCond->GetIndexRange();
      iRes =
          Intersection(iRes, _pIndexManager->GetIndex(iName.first, iName.second)
                                 ->Range(iRange.first, iRange.second));
    }
    ans = iRes;
  } else
    ans = pTable->SearchRecord(pCond);

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
  if (pTable == nullptr) throw TableNotExistException(sTableName);

  std::vector<std::string> colNames = pTable->GetColumnNames();
  if (colNames.size() != iRawVec.size()) {
    printf("Column num does not correspond\n");
    throw FieldListException();
  }
  // check null
  for (int i = 0; i < colNames.size(); i++) {
    if (iRawVec[i] == "NULL" && (!pTable->GetCanBeNull(colNames[i]) ||
                                 pTable->GetIsPrimary(colNames[i]))) {
      printf("Column should not be NULL\n");
      throw FieldListException();
    }
  }
  // check primary key
  bool primaryKeyConflict = false;
  for (int i = 0; i < colNames.size(); i++) {
    if (pTable->GetIsPrimary(colNames[i])) {
      // check whether primary key conflicts with other records
      primaryKeyConflict = true;
      FieldID colPos = pTable->GetColPos(colNames[i]);
      FieldType colType = pTable->GetType(colNames[i]);
      Field* low = BuildField(iRawVec[i], colType);
      Field* high = low->Clone();
      high->Add();
      Condition* pCond = new RangeCondition(colPos, low, high);
      std::vector<PageSlotID> pageSlotIDVec = pTable->SearchRecord(pCond);
      if (pageSlotIDVec.size() == 0) {
        primaryKeyConflict = false;
        break;
      }
    }
  }
  if (primaryKeyConflict) {
    // add exception here
    printf("Primary key existed\n");
    throw Exception("Primary key existed");
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
  if (pTable == nullptr) throw TableNotExistException(sTableName);

  std::vector<std::string> colNames = pTable->GetColumnNames();
  if (colNames.size() != iValueVec.size()) {
    printf("Column num does not correspond\n");
    throw FieldListException();
  }

  for (int i = 0; i < colNames.size(); i++) {
    if (iValueVec[i]->GetType() == FieldType::NULL_TYPE &&
        (!pTable->GetCanBeNull(colNames[i]) ||
         pTable->GetIsPrimary(colNames[i]))) {
      printf("Column should not be NULL\n");
      throw FieldListException();
    }
  }

  bool primaryKeyConflict = false;
  for (int i = 0; i < colNames.size(); i++) {
    if (pTable->GetIsPrimary(colNames[i])) {
      primaryKeyConflict = true;
      FieldID colPos = pTable->GetColPos(colNames[i]);
      FieldType colType = pTable->GetType(colNames[i]);
      Field* low = iValueVec[i]->Clone();
      Field* high = low->Clone();
      high->Add();
      Condition* pCond = new RangeCondition(colPos, low, high);
      std::vector<PageSlotID> pageSlotIDVec = pTable->SearchRecord(pCond);
      if (pageSlotIDVec.size() == 0) {
        primaryKeyConflict = false;
        break;
      }
      delete pCond;
    }
  }
  if (primaryKeyConflict) {
    // add exception here
    printf("Primary key existed\n");
    throw Exception("Primary key existed");
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

void Database::CreateIndex(const String& sTableName, const String& sColName) {
  auto iAll = Search(sTableName, nullptr, {});
  Table* pTable = GetTable(sTableName);
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

}  // namespace dbtrain_mysql