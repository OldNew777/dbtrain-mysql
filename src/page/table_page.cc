#include "page/table_page.h"

#include <assert.h>

#include <algorithm>

#include "exception/exceptions.h"
#include "macros.h"
#include "page/record_page.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

// const PageOffset COLUMN_TYPE_OFFSET = 0;
// const PageOffset COLUMN_SIZE_OFFSET =
//     COLUMN_TYPE_OFFSET + COLUMN_NUM_MAX * FIELD_TYPE_BYTES;
// const PageOffset COLUMN_NAME_OFFSET =
//     COLUMN_SIZE_OFFSET + COLUMN_NUM_MAX * FIELD_SIZE_MAX_BYTES;
// const PageOffset COLUMN_INDEX_PAGEID_OFFSET =
//     COLUMN_NAME_OFFSET + COLUMN_NUM_MAX * COLUMN_NAME_SIZE;
// const PageOffset COLUMN_INDEX_NOTNULL_OFFSET = 
//   COLUMN_INDEX_PAGEID_OFFSET + COLUMN_NUM_MAX * 
const PageOffset COLUMN_TYPE_OFFSET = 0;
const PageOffset COLUMN_SIZE_OFFSET =
    COLUMN_TYPE_OFFSET + COLUMN_NUM_MAX * FIELD_TYPE_BYTES;
const PageOffset COLUMN_NAME_OFFSET =
    COLUMN_SIZE_OFFSET + COLUMN_NUM_MAX * FIELD_SIZE_MAX_BYTES;
const PageOffset COLUMN_NOT_NULL_OFFSET = 
    COLUMN_NAME_OFFSET + COLUMN_NUM_MAX * COLUMN_NOT_NULL_BYTES;

TablePage::TablePage(const Schema& iSchema) : ManagerPage() {
  for (Size i = 0; i < iSchema.GetSize(); ++i) {
    Column iCol = iSchema.GetColumn(i);
    _iColMap[iCol.GetName()] = i;
    _iTypeVec.push_back(iCol.GetType());
    _iSizeVec.push_back(iCol.GetSize());
  }
  assert(_iColMap.size() == _iTypeVec.size());
  for(int i = 0; i < _iTypeVec.size(); i ++){
    uint8_t iNull = 0;
    GetData(&iNull, COLUMN_NOT_NULL_BYTES, 
      COLUMN_NOT_NULL_BYTES * i + COLUMN_NOT_NULL_OFFSET);
    if(iNull == 0){
      _iNullVec.push_back(false);
    }
    else{
      _iNullVec.push_back(true);
    }
  }
  RecordPage* pPage = new RecordPage(GetTotalSize(), true);
  _nHeadID = _nTailID = pPage->GetPageID();
  delete pPage;
  _bModified = true;

  // // Init Index PageID
  // for (Size i = 0; i < _iSizeVec.size(); ++i) {
  //   SetData((uint8_t*)&NULL_PAGE, 4, COLUMN_INDEX_PAGEID_OFFSET + 4 * i);
  //   _iIndexPageIDVec.push_back(NULL_PAGE);
  // }
}
TablePage::~TablePage(){
  for(int i = 0; i < _iNullVec.size(); i ++){
    uint8_t iNull = 0;
    if(_iNullVec[i]){
      iNull = 1;
    }
    SetData(&iNull, COLUMN_NOT_NULL_BYTES, 
      COLUMN_NOT_NULL_BYTES * i + COLUMN_NOT_NULL_OFFSET);
  }
}

TablePage::TablePage(PageID nPageID) : ManagerPage(nPageID) {
  throw UnimplementedException();
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
bool TablePage::GetIsNull(const String& sCol){
  return _iNullVec[GetColPos(sCol)];
}

// void TablePage::DeleteIndex(const String& sCol) { AddIndex(sCol, NULL_PAGE);
// }

// void TablePage::AddIndex(const String& sCol, PageID nPageID) {
//   FieldID pos = GetColPos(sCol);
//   _iIndexPageIDVec[pos] = nPageID;
//   SetData((uint8_t*)&nPageID, 4, COLUMN_INDEX_PAGEID_OFFSET + 4 * pos);
// }

// PageID TablePage::GetIndexPageID(const String& sCol) {
//   return _iIndexPageIDVec[GetColPos(sCol)];
// }

ManagerPageType TablePage::GetManagerPageType() const {
  return ManagerPageType::TABLE_PAGE_TYPE;
}

}  // namespace dbtrain_mysql
