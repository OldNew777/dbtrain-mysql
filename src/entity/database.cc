#include "database.h"

#include "exception/exceptions.h"
#include "macros.h"
#include "os/os.h"
#include "page/record_page.h"
#include "page/table_page.h"

namespace dbtrain_mysql {

Database::Database(DatabasePage* pDatabasePage) : EntityManager(pDatabasePage) {
  _pIndexManagerPageID =
      new IndexManager(pDatabasePage->GetIndexManagerPageID());
  Init();
}

Database::Database(PageID nDatabasePageID) : EntityManager() {
  DatabasePage* pDatabasePage = new DatabasePage(nDatabasePageID);
  _pManagerPage = pDatabasePage;
  _pIndexManagerPageID =
      new IndexManager(pDatabasePage->GetIndexManagerPageID());
  Init();
}

Database::~Database() { delete _pIndexManagerPageID; }

IndexManager* Database::GetIndexManager() const { return _pIndexManagerPageID; }

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

EntityType Database::GetEntityType() const { return EntityType::DATABASE_TYPE; }

}  // namespace dbtrain_mysql