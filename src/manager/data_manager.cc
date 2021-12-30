#include "data_manager.h"

#include "exception/exceptions.h"
#include "macros.h"

namespace dbtrain_mysql {

DataManager::DataManager() {
  whole = new Whole(MYSQL_MANAGER_PAGEID);
  database = nullptr;
}

DataManager::~DataManager() { delete whole; }

void DataManager::UseDatabase(const String& sDatabaseName) {
  // shouldn't delete database here
  // it will be done by whole
  try {
    database = whole->GetDatabase(sDatabaseName);
  } catch (DatabaseNotExistException& e) {
    printf("Database '%s' not existed\n", sDatabaseName.c_str());
    throw e;
  }
}

void DataManager::CreateDatabase(const String& sDatabaseName) {
  whole->CreateDatabase(sDatabaseName);
}

void DataManager::DropDatabase(const String& sDatabaseName) {
  whole->DropDatabase(sDatabaseName);
}

void DataManager::RenameDatabase(const String& sOldDatabaseName,
                                 const String& sNewDatabaseName) {
  whole->RenameDatabase(sOldDatabaseName, sNewDatabaseName);
}

std::vector<String> DataManager::GetDatabaseNames() const {
  return whole->GetDatabaseNames();
}

Table* DataManager::GetTable(const String& sTableName) {
  CheckDatabaseUsed();
  return database->GetTable(sTableName);
}

void DataManager::CreateTable(const String& sTableName, const Schema& iSchema) {
  CheckDatabaseUsed();
  database->CreateTable(sTableName, iSchema);
}

void DataManager::DropTable(const String& sTableName) {
  CheckDatabaseUsed();
  database->DropTable(sTableName);
}

void DataManager::RenameTable(const String& sOldTableName,
                              const String& sNewTableName) {
  CheckDatabaseUsed();
  database->RenameTable(sOldTableName, sNewTableName);
}

std::vector<String> DataManager::GetTableNames() {
  CheckDatabaseUsed();
  return database->GetTableNames();
}

std::vector<String> DataManager::GetColumnNames(const String& sTableName) {
  CheckDatabaseUsed();
  return database->GetColumnNames(sTableName);
}

void DataManager::CheckDatabaseUsed() const {
  if (database == nullptr) {
    printf("Please USE (DATABASE) first\n");
    throw DatabaseUnusedException();
  }
}

}  // namespace dbtrain_mysql