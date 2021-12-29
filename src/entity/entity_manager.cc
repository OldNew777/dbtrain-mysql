#include "entity_manager.h"

#include "defines.h"
#include "exception/exceptions.h"
#include "macros.h"
#include "page/record_page.h"
#include "string.h"

namespace dbtrain_mysql {

void EntityManager::Clear() {
  _iEntityMap.clear();
  _iEntityPageIDMap.clear();
  Entity::Clear();
}

EntityManager::EntityManager(ManagerPage* pManagerPage) {
  this->pManagerPage = pManagerPage;
  Init();
}

EntityManager::~EntityManager() {
  for (auto iter = _iEntityMap.begin(); iter != _iEntityMap.end(); ++iter)
    if (iter->second) {
      delete iter->second;
      iter->second = nullptr;
    }
}

void EntityManager::InsertEntity(const String& sEntityName) {
  // insert entity to page
  FindNextNotFull();
  PageID nPageID = _nNotFull;
  RecordPage page(nPageID);
  uint8_t* data = new uint8_t[pManagerPage->GetTotalSize()];
  int pageID = nPageID;
  memset(data, 0, pManagerPage->GetTotalSize());
  memcpy(data, sEntityName.c_str(), sEntityName.size());
  memcpy(data + TABLE_NAME_SIZE, &pageID, 4);
  _iEntityPageSlotIDMap[sEntityName] = {nPageID, page.InsertRecord(data)};

  delete[] data;
}

void EntityManager::DeleteEntity(const String& sEntityName,
                                 PageSlotID nPageSlotID) {
  // delete entity from page
  RecordPage page(nPageSlotID.first);
  page.DeleteRecord(nPageSlotID.second);
  _iEntityPageSlotIDMap.erase(sEntityName);
}

}  // namespace dbtrain_mysql