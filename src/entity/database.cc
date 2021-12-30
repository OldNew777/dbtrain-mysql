#include "database.h"

#include "exception/exceptions.h"
#include "macros.h"
#include "os/os.h"
#include "page/record_page.h"
#include "page/table_page.h"

namespace dbtrain_mysql {

Database::Database(DatabasePage* pDatabasePage) : EntityManager(pDatabasePage) {
  Init();
}

Database::Database(PageID nDatabasePageID) : EntityManager() {
  pManagerPage = new DatabasePage(nDatabasePageID);
  Init();
}

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

Table* Database::CreateTable(const String& sTableName, const Schema& iSchema) {
  // Table existed before
  if (GetTable(sTableName) != nullptr) throw TableExistException(sTableName);

  // Create table and cache it
  TablePage* pPage = new TablePage(iSchema);
  Table* pTable = new Table(pPage);
  _iEntityMap[sTableName] = pTable;
  _iEntityPageIDMap[sTableName] = pPage->GetPageID();

  // insert entity to page
  InsertEntity(sTableName);

  return pTable;
}

void Database::DropTable(const String& sTableName) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) throw TableNotExistException(sTableName);
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
  if (pTable == nullptr) throw TableNotExistException(sOldTableName);
  if (GetTable(sNewTableName) != nullptr)
    throw TableExistException(sNewTableName);

  DeleteEntity(sOldTableName, _iEntityPageSlotIDMap[sOldTableName]);
  InsertEntity(sNewTableName);

  _iEntityMap[sNewTableName] = pTable;
  _iEntityPageIDMap[sNewTableName] = _iEntityPageIDMap[sOldTableName];
  _iEntityMap.erase(sOldTableName);
  _iEntityPageIDMap.erase(sOldTableName);
}

std::vector<String> Database::GetTableNames() {
  std::vector<String> names;
  for (auto iter = _iEntityPageSlotIDMap.begin();
       iter != _iEntityPageSlotIDMap.end(); ++iter)
    names.push_back(iter->first);
  return names;
}

std::vector<String> Database::GetColumnNames(const String& sTableName) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) throw TableNotExistException(sTableName);
  return pTable->GetColumnNames();
}

EntityType Database::GetEntityType() const { return EntityType::DATABASE_TYPE; }

void Database::Init() {
  EntityManager::Init();
  std::vector<std::pair<PageSlotID, Record*>> records =
      pManagerPage->GetAllRecords();
  for (auto pRecord : records) {
    String sTableName = pRecord.second->GetField(0)->ToString();
    _iEntityPageSlotIDMap[sTableName] = pRecord.first;
    _iEntityPageIDMap[sTableName] =
        dynamic_cast<IntField*>(pRecord.second->GetField(1))->GetIntData();
    delete pRecord.second;
  }
}

}  // namespace dbtrain_mysql