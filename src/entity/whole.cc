#include "whole.h"

#include "exception/exceptions.h"
#include "macros.h"
#include "os/os.h"
#include "page/database_page.h"
#include "page/record_page.h"

namespace dbtrain_mysql {

Whole::Whole(WholePage* pWholePage) : EntityManager(pWholePage) { Init(); }

Whole::Whole(PageID pWholePageID) : EntityManager() {
  pManagerPage = new DatabasePage(pWholePageID);
  Init();
}

Database* Whole::GetDatabase(const String& sDatabaseName) {
  if (_iEntityMap.find(sDatabaseName) == _iEntityMap.end()) {
    if (_iEntityPageIDMap.find(sDatabaseName) == _iEntityPageIDMap.end()) {
      // no database named as it / not loaded
      return nullptr;
    } else {
      // not cached
      _iEntityMap[sDatabaseName] =
          new Database(_iEntityPageIDMap[sDatabaseName]);
      return dynamic_cast<Database*>(_iEntityMap[sDatabaseName]);
    }
  }
  // cached
  return dynamic_cast<Database*>(_iEntityMap[sDatabaseName]);
}

Database* Whole::CreateDatabase(const String& sDatabaseName) {
  // Database existed before
  if (GetDatabase(sDatabaseName) != nullptr)
    throw DatabaseExistException(sDatabaseName);

  // Create database and cache it
  DatabasePage* pPage = new DatabasePage();
  Database* pDatabase = new Database(pPage);
  _iEntityMap[sDatabaseName] = pDatabase;
  _iEntityPageIDMap[sDatabaseName] = pPage->GetPageID();

  // insert entity to page
  InsertEntity(sDatabaseName);

  return pDatabase;
}

void Whole::DropDatabase(const String& sDatabaseName) {
  Database* pDatabase = GetDatabase(sDatabaseName);
  if (pDatabase == nullptr) throw DatabaseNotExistException(sDatabaseName);
  pDatabase->Clear();
  delete pDatabase;
  OS::GetOS()->DeletePage(_iEntityPageIDMap[sDatabaseName]);
  _iEntityMap.erase(sDatabaseName);
  _iEntityPageIDMap.erase(sDatabaseName);

  DeleteEntity(sDatabaseName, _iEntityPageSlotIDMap[sDatabaseName]);
}

void Whole::RenameDatabase(const String& sOldDatabaseName,
                           const String& sNewDatabaseName) {
  Database* pDatabase = GetDatabase(sOldDatabaseName);
  if (pDatabase == nullptr) throw DatabaseNotExistException(sOldDatabaseName);
  if (GetDatabase(sNewDatabaseName) != nullptr)
    throw DatabaseExistException(sNewDatabaseName);

  DeleteEntity(sOldDatabaseName, _iEntityPageSlotIDMap[sOldDatabaseName]);
  InsertEntity(sNewDatabaseName);

  _iEntityMap[sNewDatabaseName] = pDatabase;
  _iEntityPageIDMap[sNewDatabaseName] = _iEntityPageIDMap[sOldDatabaseName];
  _iEntityMap.erase(sOldDatabaseName);
  _iEntityPageIDMap.erase(sOldDatabaseName);
}

std::vector<String> Whole::GetDatabaseNames() const { return GetEntityNames(); }

EntityType Whole::GetEntityType() const { return EntityType::MYSQL_TYPE; }

}  // namespace dbtrain_mysql