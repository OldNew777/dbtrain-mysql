#include "whole.h"

#include "exception/exceptions.h"
#include "macros.h"
#include "os/os.h"
#include "page/database_page.h"
#include "page/record_page.h"

namespace dbtrain_mysql {

Whole::Whole(WholePage* pWholePage) : EntityManager(pWholePage) { Init(); }

Whole::Whole(PageID pWholePageID) : EntityManager() {
  _pManagerPage = new DatabasePage(pWholePageID);
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

void Whole::CreateDatabase(const String& sDatabaseName) {
  // Database existed before
  if (GetDatabase(sDatabaseName) != nullptr) {
    auto e = DatabaseExistException(sDatabaseName);
    std::cout << e.what() << "\n";
    throw e;
  }

  // Create database and cache it
  DatabasePage* pPage = new DatabasePage();
  Database* pDatabase = new Database(pPage);
  _iEntityMap[sDatabaseName] = pDatabase;
  _iEntityPageIDMap[sDatabaseName] = pPage->GetPageID();

  // insert entity to page
  InsertEntity(sDatabaseName);
}

void Whole::DropDatabase(const String& sDatabaseName) {
  Database* pDatabase = GetDatabase(sDatabaseName);
  if (pDatabase == nullptr) {
    auto e = DatabaseNotExistException(sDatabaseName);
    std::cout << e.what() << "\n";
    throw e;
  }
#ifdef DELETE_DEBUG
  printf("Checkpoint 1\n");
#endif
  pDatabase->Clear();
#ifdef DELETE_DEBUG
  printf("Checkpoint 2\n");
#endif
  delete pDatabase;
#ifdef DELETE_DEBUG
  printf("Database root page delete begin\n");
  printf("root page id %d\n", int(_iEntityPageIDMap[sDatabaseName]));
#endif
  OS::GetOS()->DeletePage(_iEntityPageIDMap[sDatabaseName]);
#ifdef DELETE_DEBUG
  printf("Database root page delete succeed\n");
#endif
  _iEntityMap.erase(sDatabaseName);
  _iEntityPageIDMap.erase(sDatabaseName);

  DeleteEntity(sDatabaseName, _iEntityPageSlotIDMap[sDatabaseName]);
}

void Whole::RenameDatabase(const String& sOldDatabaseName,
                           const String& sNewDatabaseName) {
  Database* pDatabase = GetDatabase(sOldDatabaseName);
  if (pDatabase == nullptr) {
    auto e = DatabaseNotExistException(sOldDatabaseName);
    std::cout << e.what() << "\n";
    throw e;
  }
  if (GetDatabase(sNewDatabaseName) != nullptr) {
    auto e = DatabaseExistException(sNewDatabaseName);
    std::cout << e.what() << "\n";
    throw e;
  }

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