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
    uint8_t status = 0;
    if (iCol.GetCanBeNull()) status |= 0b1;
    if (iCol.GetIsPrimary()) {
      // printf("name: %s\n", iCol.GetName());
      status |= 0b10;
    }
    if(iCol.GetForeignKeyPair().first != ""){
      status |= 0b100;
    }
    _iStatusVec.push_back(status);
  }
  assert(_iColMap.size() == _iTypeVec.size());
  RecordPage* pPage = new RecordPage(GetTotalSize(), true);
  _nHeadID = _nTailID = pPage->GetPageID();
  delete pPage;
  _bModified = true;
}

TablePage::TablePage(PageID nPageID) : ManagerPage(nPageID) {
  for (int i = 0; i < _iTypeVec.size(); i++) {
    uint8_t iNull = 0;
    GetData(&iNull, COLUMN_NOT_NULL_BYTES,
            COLUMN_NOT_NULL_BYTES * i + COLUMN_STATUS_OFFSET);
    _iStatusVec.push_back(iNull);
  }
  // printf("TablePage()\n");
}
TablePage::~TablePage() {
  for (int i = 0; i < _iStatusVec.size(); i++) {
    uint8_t iNull = _iStatusVec[i];
    SetData(&iNull, COLUMN_NOT_NULL_BYTES,
            COLUMN_NOT_NULL_BYTES * i + COLUMN_STATUS_OFFSET);
  }
  // printf("~TablePage\n");
}

FieldID TablePage::GetColPos(const String& sCol) {
  if (_iColMap.find(sCol) == _iColMap.end()) {
    auto e = TableException("Column does not exist");
    std::cout << e.what() << ": " << sCol << "\n";
    throw e;
  }
  return _iColMap[sCol];
}

FieldType TablePage::GetType(const String& sCol) {
  return _iTypeVec[GetColPos(sCol)];
}

Size TablePage::GetSize(const String& sCol) {
  return _iSizeVec[GetColPos(sCol)];
}
bool TablePage::GetCanBeNull(const String& sCol) {
  return ((_iStatusVec[GetColPos(sCol)] & 0b1) == 0b1);
}
bool TablePage::GetIsPrimary(const String& sCol) {
  return ((_iStatusVec[GetColPos(sCol)] & 0b10) == 0b10);
}
bool TablePage::GetIsForeign(const String& sCol){
  return ((_iStatusVec[GetColPos(sCol)] & 0b100) == 0b100);
}

ManagerPageType TablePage::GetManagerPageType() const {
  return ManagerPageType::TABLE_PAGE_TYPE;
}

}  // namespace dbtrain_mysql
