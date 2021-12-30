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
  database = whole->GetDatabase(sDatabaseName);
  if (database == nullptr) {
    printf("Database '%s' not existed\n", sDatabaseName.c_str());
    throw DatabaseNotExistException(sDatabaseName);
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
  if (database == nullptr) {
    printf("Please USE (DATABASE) first\n");
    throw DatabaseUnusedException();
  }
  return database->GetTable(sTableName);
}

Table* DataManager::CreateTable(const String& sTableName,
                                const Schema& iSchema) {
  if (database == nullptr) {
    printf("Please USE (DATABASE) first\n");
    throw DatabaseUnusedException();
  }
  database->CreateTable(sTableName, iSchema);
}

void DataManager::DropTable(const String& sTableName) {
  if (database == nullptr) {
    printf("Please USE (DATABASE) first\n");
    throw DatabaseUnusedException();
  }
  database->DropTable(sTableName);
}

void DataManager::RenameTable(const String& sOldTableName,
                              const String& sNewTableName) {
  if (database == nullptr) {
    printf("Please USE (DATABASE) first\n");
    throw DatabaseUnusedException();
  }
  database->RenameTable(sOldTableName, sNewTableName);
}

std::vector<String> DataManager::GetTableNames() {
  if (database == nullptr) {
    printf("Please USE (DATABASE) first\n");
    throw DatabaseUnusedException();
  }
  return database->GetTableNames();
}

std::vector<String> DataManager::GetColumnNames(const String& sTableName) {
  if (database == nullptr) {
    printf("Please USE (DATABASE) first\n");
    throw DatabaseUnusedException();
  }
  return database->GetColumnNames(sTableName);
}

}  // namespace dbtrain_mysql