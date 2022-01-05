#include "manager_page.h"

#include <algorithm>

#include "exception/exceptions.h"
#include "macros.h"
#include "page/record_page.h"
#include "settings.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

ManagerPage::ManagerPage() : Page() {}

ManagerPage::ManagerPage(PageID nPageID) : Page(nPageID) {
  Load();
  _bModified = false;
  // printf("ManagePage\n");
}

ManagerPage::~ManagerPage() {
  if (_bModified) {
    _bModified = false;
    Store();
  };
  // printf("~ManagePage\n");
}

PageID ManagerPage::GetHeadID() const { return _nHeadID; }

PageID ManagerPage::GetTailID() const { return _nTailID; }

void ManagerPage::SetHeadID(PageID nHeadID) {
  _nHeadID = nHeadID;
  _bModified = true;
}

void ManagerPage::SetTailID(PageID nTailID) {
  _nTailID = nTailID;
  _bModified = true;
}

Size ManagerPage::GetTotalSize() const {
  Size nTotal = 0;
  for (const auto& nSize : _iSizeVec) nTotal += nSize;
  return nTotal + ((_iSizeVec.size() + 7) >> 3);
}

Size ManagerPage::GetFieldSize() const { return _iTypeVec.size(); }

std::vector<FieldType> ManagerPage::GetTypeVec() const { return _iTypeVec; }

std::vector<Size> ManagerPage::GetSizeVec() const { return _iSizeVec; }

void ManagerPage::Store() {
  SetHeader((uint8_t*)&_nHeadID, 4, HEAD_PAGE_OFFSET);
  SetHeader((uint8_t*)&_nTailID, 4, TAIL_PAGE_OFFSET);
  FieldID iFieldSize = _iSizeVec.size();
  SetHeader((uint8_t*)&iFieldSize, 4, COLUMN_LEN_OFFSET);
  for (Size i = 0; i < iFieldSize; ++i) {
    int nType = (int)_iTypeVec[i];
    SetData((uint8_t*)&nType, FIELD_TYPE_BYTES, COLUMN_TYPE_OFFSET + i);
  }
  for (Size i = 0; i < iFieldSize; ++i) {
    Size nSize = _iSizeVec[i];
    SetData((uint8_t*)&nSize, FIELD_SIZE_MAX_BYTES,
            COLUMN_SIZE_OFFSET + FIELD_SIZE_MAX_BYTES * i);
  }
  String sColumnsName = BuildColumnsString(_iColMap);
  Size sColNameLen = sColumnsName.size();
  SetHeader((uint8_t*)&sColNameLen, 4, COLUMN_NAME_LEN_OFFSET);
  SetData((uint8_t*)sColumnsName.c_str(), sColNameLen, COLUMN_NAME_OFFSET);

#ifdef DATABASE_DEBUG
  printf("\n----ManagerPage::Store----\n");
  printf("_nPageID = %d\n", int(_nPageID));
  printf("_nHeadID = %d\n", int(_nHeadID));
  printf("_nTailID = %d\n", int(_nTailID));
  printf("size = %d\n", int(iFieldSize));
  printf("sColNameLen = %d\n", int(sColNameLen));
  std::cout << "BuildColumnsString = " << sColumnsName << "\n\n";
#endif
}

void ManagerPage::Load() {
  GetHeader((uint8_t*)&_nHeadID, 4, HEAD_PAGE_OFFSET);
  GetHeader((uint8_t*)&_nTailID, 4, TAIL_PAGE_OFFSET);
  FieldID iFieldSize = 0;
  GetHeader((uint8_t*)&iFieldSize, 4, COLUMN_LEN_OFFSET);
  for (Size i = 0; i < iFieldSize; ++i) {
    int nType = 0;
    GetData((uint8_t*)&nType, FIELD_TYPE_BYTES, COLUMN_TYPE_OFFSET + i);
    _iTypeVec.push_back(FieldType(nType));
  }

  for (Size i = 0; i < iFieldSize; ++i) {
    Size nSize = 0;
    GetData((uint8_t*)&nSize, FIELD_SIZE_MAX_BYTES,
            COLUMN_SIZE_OFFSET + FIELD_SIZE_MAX_BYTES * i);
    _iSizeVec.push_back(nSize);
  }

  Size sColNameLen = 0;
  GetHeader((uint8_t*)&sColNameLen, 4, COLUMN_NAME_LEN_OFFSET);
  char* pTemp = new char[sColNameLen + 1];
  pTemp[sColNameLen] = '\0';
  GetData((uint8_t*)pTemp, sColNameLen, COLUMN_NAME_OFFSET);
  String sName(pTemp);
  _iColMap = LoadColumnsString(sName);

#ifdef DATABASE_DEBUG
  printf("\n----ManagerPage::Load----\n");
  printf("_nPageID = %d\n", int(_nPageID));
  printf("_nHeadID = %d\n", int(_nHeadID));
  printf("_nTailID = %d\n", int(_nTailID));
  printf("size = %d\n", int(iFieldSize));
  printf("sColNameLen = %d\n", int(sColNameLen));
  std::cout << "LoadColumnsString " << sName << "\n\n";
#endif

  delete[] pTemp;

}

std::vector<std::pair<PageSlotID, Record*>> ManagerPage::GetAllRecords() const {
  std::vector<std::pair<PageSlotID, Record*>> records;
  PageID curPageID = GetHeadID();
  while (curPageID != NULL_PAGE) {
    RecordPage* pPage = new RecordPage(curPageID);
    for (Size i = 0, num = 0; i < pPage->GetCap() && num < pPage->GetUsed();
         ++i) {
      if (!pPage->HasRecord(i)) continue;
      ++num;
      FixedRecord* pRecord =
          new FixedRecord(GetSizeVec().size(), GetTypeVec(), GetSizeVec());
      uint8_t* pData = pPage->GetRecord(i);
      pRecord->Load(pData);
      records.push_back({{curPageID, i}, std::move(pRecord)});
      delete[] pData;
    }
    curPageID = pPage->GetNextID();
    delete pPage;
  }
  return records;
}

}  // namespace dbtrain_mysql