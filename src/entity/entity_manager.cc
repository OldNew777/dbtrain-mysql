#include "entity_manager.h"

#include "defines.h"
#include "exception/exceptions.h"
#include "macros.h"
#include "page/record_page.h"
#include "settings.h"
#include "string.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

void EntityManager::Clear() {
  for (auto iter : _iEntityMap)
    if (iter.second) {
      delete iter.second;
    }
  _iEntityMap.clear();
  _iEntityPageIDMap.clear();
  _iEntityPageSlotIDMap.clear();
  Entity::Clear();
}

EntityManager::EntityManager(ManagerPage* pManagerPage) {
  this->pManagerPage = pManagerPage;
  Init();
}

EntityManager::~EntityManager() {
  for (auto iter : _iEntityMap)
    if (iter.second) {
      delete iter.second;
    }
}

void EntityManager::InsertEntity(const String& sEntityName) {
  // insert entity to page
  FindNextNotFull();
  PageID nPageID = _nNotFull;

  RecordPage page(nPageID);
  uint8_t* data = new uint8_t[pManagerPage->GetTotalSize()];
  int entityPageID = _iEntityPageIDMap[sEntityName];
  memset(data, 0, pManagerPage->GetTotalSize());
  memcpy(data, sEntityName.c_str(), sEntityName.size());
  memcpy(data + TABLE_NAME_SIZE, &entityPageID, 4);
  SlotID nSlotID = page.InsertRecord(data);
  _iEntityPageSlotIDMap[sEntityName] = {nPageID, nSlotID};

#ifdef DATABASE_DEBUG
  printf("\n----EntityManager::InsertEntity----\n");
  printf("_nHeadID = %d\n", int(_nHeadID));
  printf("_nTailID = %d\n", int(_nTailID));
  printf("entity PageID = %d\n", int(nPageID));
  printf("entity save postion = ");
  PrintPageSlotID(_iEntityPageSlotIDMap[sEntityName]);
  printf("\n\n");
#endif

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