#include "database_page.h"

#include "exception/exceptions.h"
#include "macros.h"
#include "page/record_page.h"

namespace dbtrain_mysql {

const PageOffset COLUMN_LEN_OFFSET = 16;
const PageOffset COLUMN_NAME_LEN_OFFSET = 20;
const PageOffset HEAD_PAGE_OFFSET = 24;
const PageOffset TAIL_PAGE_OFFSET = 28;

const PageOffset COLUMN_TYPE_OFFSET = 0;
const PageOffset COLUMN_SIZE_OFFSET = 64;
const PageOffset COLUMN_NAME_OFFSET = 192;

DatabasePage::DatabasePage() : ManagerPage() {
  _iColMap["Name"] = 0;
  _iColMap["PageID"] = 1;
  _iTypeVec = {FieldType::CHAR_TYPE, FieldType::INT_TYPE};
  _iSizeVec = {DATABASE_NAME_SIZE, 4};

  RecordPage* pPage = new RecordPage(DATABASE_NAME_SIZE, true);
  _nHeadID = _nTailID = pPage->GetPageID();
  delete pPage;
  _bModified = true;
}

DatabasePage::DatabasePage(PageID nPageID) : ManagerPage(nPageID) {}

ManagerPageType DatabasePage::GetManagerPageType() const {
  return ManagerPageType::DATABASE_PAGE_TYPE;
}

}  // namespace dbtrain_mysql