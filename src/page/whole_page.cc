#include "whole_page.h"

#include "exception/exceptions.h"
#include "macros.h"
#include "page/record_page.h"

namespace dbtrain_mysql {

WholePage::WholePage() : ManagerPage() {
  _iColMap["DatabaseName"] = 0;
  _iColMap["PageID"] = 1;
  _iTypeVec = {FieldType::CHAR_TYPE, FieldType::INT_TYPE};
  _iSizeVec = {DATABASE_NAME_SIZE, 4};

  RecordPage* pPage = new RecordPage(GetTotalSize(), true);
  _nHeadID = _nTailID = pPage->GetPageID();
  delete pPage;
  _bModified = true;
}

WholePage::WholePage(PageID nPageID) : ManagerPage(nPageID) {}

ManagerPageType WholePage::GetManagerPageType() const {
  return ManagerPageType::WHOLE_PAGE_TYPE;
}

}  // namespace dbtrain_mysql