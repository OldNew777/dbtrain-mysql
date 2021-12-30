#include "data_manager.h"

#include "exception/exceptions.h"
#include "macros.h"

namespace dbtrain_mysql {

DataManager::DataManager() {
  _pWhole = new Whole(MYSQL_MANAGER_PAGEID);
  _pDatabase = nullptr;
}

DataManager::~DataManager() { delete _pWhole; }

void DataManager::UseDatabase(const String& sDatabaseName) {
  // shouldn't delete _pDatabase here
  // it will be done by _pWhole
  try {
    _pDatabase = _pWhole->GetDatabase(sDatabaseName);
  } catch (DatabaseNotExistException& e) {
    printf("Database '%s' not existed\n", sDatabaseName.c_str());
    throw e;
  }
}

void DataManager::CreateDatabase(const String& sDatabaseName) {
  _pWhole->CreateDatabase(sDatabaseName);
}

void DataManager::DropDatabase(const String& sDatabaseName) {
  _pWhole->DropDatabase(sDatabaseName);
}

void DataManager::RenameDatabase(const String& sOldDatabaseName,
                                 const String& sNewDatabaseName) {
  _pWhole->RenameDatabase(sOldDatabaseName, sNewDatabaseName);
}

std::vector<String> DataManager::GetDatabaseNames() const {
  return _pWhole->GetDatabaseNames();
}

Table* DataManager::GetTable(const String& sTableName) const {
  CheckDatabaseUsed();
  Table* pTable = _pDatabase->GetTable(sTableName);
  if (pTable == nullptr) throw TableNotExistException(sTableName);
  return pTable;
}

void DataManager::CreateTable(const String& sTableName,
                              const Schema& iSchema) const {
  CheckDatabaseUsed();
  _pDatabase->CreateTable(sTableName, iSchema);
}

void DataManager::DropTable(const String& sTableName) const {
  CheckDatabaseUsed();
  _pDatabase->DropTable(sTableName);
}

void DataManager::RenameTable(const String& sOldTableName,
                              const String& sNewTableName) const {
  CheckDatabaseUsed();
  _pDatabase->RenameTable(sOldTableName, sNewTableName);
}

std::vector<String> DataManager::GetTableNames() const {
  CheckDatabaseUsed();
  return _pDatabase->GetTableNames();
}

std::vector<String> DataManager::GetColumnNames(
    const String& sTableName) const {
  CheckDatabaseUsed();
  return _pDatabase->GetColumnNames(sTableName);
}

FieldID DataManager::GetColID(const String& sTableName,
                              const String& sColName) const {
  return GetTable(sTableName)->GetColPos(sColName);
}

FieldType DataManager::GetColType(const String& sTableName,
                                  const String& sColName) const {
  return GetTable(sTableName)->GetType(sColName);
}

Size DataManager::GetColSize(const String& sTableName,
                             const String& sColName) const {
  return GetTable(sTableName)->GetSize(sColName);
}

Record* DataManager::GetRecord(const String& sTableName,
                               const PageSlotID& nPageSlotID) const {
  Record* pRecord =
      GetTable(sTableName)->GetRecord(nPageSlotID.first, nPageSlotID.second);
  return pRecord;
}

std::vector<Record*> DataManager::GetTableInfos(
    const String& sTableName) const {}

void DataManager::CheckDatabaseUsed() const {
  if (_pDatabase == nullptr) {
    printf("Please USE (DATABASE) first\n");
    throw DatabaseUnusedException();
  }
}

}  // namespace dbtrain_mysql