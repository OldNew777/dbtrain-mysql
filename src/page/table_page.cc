#include "page/table_page.h"

#include <assert.h>

#include <algorithm>

#include "exception/exceptions.h"
#include "macros.h"
#include "page/record_page.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

TablePage::TablePage(const Schema& iSchema) : ManagerPage() {
  for (Size i = 0; i < iSchema.GetSize(); ++i) {
    Column iCol = iSchema.GetColumn(i);
    _iColMap[iCol.GetName()] = i;
    _iTypeVec.push_back(iCol.GetType());
    _iSizeVec.push_back(iCol.GetSize());
  }
  assert(_iColMap.size() == _iTypeVec.size());
  RecordPage* pPage = new RecordPage(GetTotalSize(), true);
  _nHeadID = _nTailID = pPage->GetPageID();
  delete pPage;
  _bModified = true;
}

TablePage::TablePage(PageID nPageID) : ManagerPage(nPageID) {}

FieldID TablePage::GetColPos(const String& sCol) {
  if (_iColMap.find(sCol) == _iColMap.end()) throw TableException();
  return _iColMap[sCol];
}

FieldType TablePage::GetType(const String& sCol) {
  return _iTypeVec[GetColPos(sCol)];
}

Size TablePage::GetSize(const String& sCol) {
  return _iSizeVec[GetColPos(sCol)];
}

ManagerPageType TablePage::GetManagerPageType() const {
  return ManagerPageType::TABLE_PAGE_TYPE;
}

}  // namespace dbtrain_mysql
