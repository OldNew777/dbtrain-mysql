#include "database_page.h"

#include "exception/exceptions.h"
#include "macros.h"
#include "manager/index_manager.h"
#include "manager/key_manager.h"
#include "page/record_page.h"

namespace dbtrain_mysql {

const PageOffset INDEX_MANAGER_PAGE_ID_OFFSET = 32;
const PageOffset KEY_MANAGER_PAGE_ID_OFFSET = 36;

DatabasePage::DatabasePage() : ManagerPage() {
  _iColMap["TableName"] = 0;
  _iColMap["PageID"] = 1;
  _iTypeVec = {FieldType::CHAR_TYPE, FieldType::INT_TYPE};
  _iSizeVec = {TABLE_NAME_SIZE, 4};

  // Init page containing tables
  RecordPage* pPage = new RecordPage(GetTotalSize(), true);
  _nHeadID = _nTailID = pPage->GetPageID();
  delete pPage;

  // Init page containing IndexManager
  IndexManager indexManager;
  KeyManager keyManager;
  _nIndexManagerPageID = indexManager.GetPageID();
  _nKeyManagerPageID = keyManager.GetPageID();
  SetHeader((uint8_t*)&_nIndexManagerPageID, 4, INDEX_MANAGER_PAGE_ID_OFFSET);
  SetHeader((uint8_t*)&_nKeyManagerPageID, 4, KEY_MANAGER_PAGE_ID_OFFSET);

  _bModified = true;
}

DatabasePage::DatabasePage(PageID nPageID) : ManagerPage(nPageID) {
  GetHeader((uint8_t*)&_nIndexManagerPageID, 4, INDEX_MANAGER_PAGE_ID_OFFSET);
  GetHeader((uint8_t*)&_nKeyManagerPageID, 4, KEY_MANAGER_PAGE_ID_OFFSET);
}

PageID DatabasePage::GetIndexManagerPageID() const {
  return _nIndexManagerPageID;
}

PageID DatabasePage::GetKeyManagerPageID() const { return _nKeyManagerPageID; }

ManagerPageType DatabasePage::GetManagerPageType() const {
  return ManagerPageType::DATABASE_PAGE_TYPE;
}

}  // namespace dbtrain_mysql