#include "page/table_page.h"

#include <assert.h>

#include <algorithm>

#include "exception/exceptions.h"
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

FieldID TablePage::GetFieldID(const String& sColName) const {
  if (_iColMap.find(sColName) == _iColMap.end()) throw TableException();
  return _iColMap.find(sColName)->second;
}

FieldID TablePage::GetPos(const String& sCol) { return _iColMap[sCol]; }

FieldType TablePage::GetType(const String& sCol) {
  return _iTypeVec[GetPos(sCol)];
}

Size TablePage::GetSize(const String& sCol) { return _iSizeVec[GetPos(sCol)]; }

ManagerPageType TablePage::GetManagerPageType() const {
  return ManagerPageType::TABLE_PAGE_TYPE;
}

}  // namespace dbtrain_mysql
