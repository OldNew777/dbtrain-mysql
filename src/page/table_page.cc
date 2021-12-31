#include "page/table_page.h"

#include <assert.h>

#include <algorithm>

#include "exception/exceptions.h"
#include "macros.h"
#include "page/record_page.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

const PageOffset COLUMN_TYPE_OFFSET = 0;
const PageOffset COLUMN_SIZE_OFFSET =
    COLUMN_TYPE_OFFSET + COLUMN_NUM_MAX * FIELD_TYPE_BYTES;
const PageOffset COLUMN_NAME_OFFSET =
    COLUMN_SIZE_OFFSET + COLUMN_NUM_MAX * FIELD_SIZE_MAX_BYTES;
const PageOffset COLUMN_INDEX_PAGEID_OFFSET =
    COLUMN_NAME_OFFSET + COLUMN_NUM_MAX * COLUMN_NAME_SIZE;

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

  // Init Index PageID
  for (Size i = 0; i < _iSizeVec.size(); ++i) {
    SetData((uint8_t*)&NULL_PAGE, 4, COLUMN_INDEX_PAGEID_OFFSET + 4 * i);
    _iIndexPageIDVec.push_back(NULL_PAGE);
  }
}

TablePage::TablePage(PageID nPageID) : ManagerPage(nPageID) {
  // Load Index PageID
  for (Size i = 0; i < _iSizeVec.size(); ++i) {
    PageID nPageID = 0;
    GetData((uint8_t*)&nPageID, 4, COLUMN_INDEX_PAGEID_OFFSET + 4 * i);
    _iIndexPageIDVec.push_back(nPageID);
  }
}

void TablePage::DeleteIndex(const String& sCol) { AddIndex(sCol, NULL_PAGE); }

void TablePage::AddIndex(const String& sCol, PageID nPageID) {
  FieldID pos = GetColPos(sCol);
  _iIndexPageIDVec[pos] = nPageID;
  SetData((uint8_t*)&nPageID, 4, COLUMN_INDEX_PAGEID_OFFSET + 4 * pos);
}

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

PageID TablePage::GetIndexPageID(const String& sCol) {
  return _iIndexPageIDVec[GetColPos(sCol)];
}

ManagerPageType TablePage::GetManagerPageType() const {
  return ManagerPageType::TABLE_PAGE_TYPE;
}

}  // namespace dbtrain_mysql
