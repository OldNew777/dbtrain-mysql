#include "database_page.h"

#include "exception/exceptions.h"
#include "macros.h"
#include "page/record_page.h"

namespace dbtrain_mysql {

const PageOffset INDEX_MANAGER_PAGE_ID_OFFSET = 32;

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


  _bModified = true;
}

DatabasePage::DatabasePage(PageID nPageID) : ManagerPage(nPageID) {}

ManagerPageType DatabasePage::GetManagerPageType() const {
  return ManagerPageType::DATABASE_PAGE_TYPE;
}

}  // namespace dbtrain_mysql