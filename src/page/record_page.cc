#include "record_page.h"

#include <assert.h>

#include <cstring>

#include "exception/exceptions.h"
#include "macros.h"

namespace dbtrain_mysql {

const PageOffset FIXED_SIZE_OFFSET = 12;
const PageOffset EMPTY_SLOT_OFFSET = 14;
const PageOffset BITMAP_OFFSET = 0;
const PageOffset BITMAP_SIZE = 128;

SlotID RecordPage::CalculateCap(PageOffset nFixed) {
  return (DATA_SIZE - BITMAP_SIZE) / nFixed;
}

RecordPage::RecordPage(PageOffset nFixed, bool) : LinkedPage() {
  _nFixed = nFixed;
  _pUsed = new Bitmap((DATA_SIZE - BITMAP_SIZE) / nFixed);
  _nCap = CalculateCap(_nFixed);
  _nEmptySlotID = 0;
  _bModified = true;
}

RecordPage::RecordPage(PageID nPageID) : LinkedPage(nPageID) {
  GetHeader((uint8_t*)&_nFixed, 2, FIXED_SIZE_OFFSET);
  GetHeader((uint8_t*)&_nEmptySlotID, 2, EMPTY_SLOT_OFFSET);
  _pUsed = new Bitmap((DATA_SIZE - BITMAP_SIZE) / _nFixed);
  _nCap = CalculateCap(_nFixed);
  _bModified = false;
  LoadBitmap();
  FindNextEmptySlot();
}

RecordPage::~RecordPage() {
  if (_bModified) {
    StoreBitmap();
    SetHeader((uint8_t*)&_nFixed, 2, FIXED_SIZE_OFFSET);
    SetHeader((uint8_t*)&_nEmptySlotID, 2, EMPTY_SLOT_OFFSET);
  }
  delete _pUsed;
}

void RecordPage::LoadBitmap() {
  uint8_t pTemp[BITMAP_SIZE];
  memset(pTemp, 0, BITMAP_SIZE);
  GetData(pTemp, BITMAP_SIZE, BITMAP_OFFSET);
  _pUsed->Load(pTemp);
}

void RecordPage::FindNextEmptySlot() {
  _bModified = true;
  SlotID searchFlag = _nEmptySlotID;
  if (FindNextEmptySlotUntil(_nCap - 1)) return;
  // searchFlag代码上看会重复搜索一次
  // 但实际上不会轮到第二次，就会结束
  _nEmptySlotID = 0;
  FindNextEmptySlotUntil(searchFlag);
}

bool RecordPage::FindNextEmptySlotUntil(SlotID target) {
  // 如果顺序相反，则进入搜索，以免crash
  bool unStop = _nEmptySlotID <= target ? true : false;
  while (unStop) {
    if (!_pUsed->Get(_nEmptySlotID)) return true;
    if (_nEmptySlotID == target) unStop = false;
    ++_nEmptySlotID;
  }
  return false;
}

void RecordPage::StoreBitmap() {
  uint8_t pTemp[BITMAP_SIZE];
  memset(pTemp, 0, BITMAP_SIZE);
  _pUsed->Store(pTemp);
  SetData(pTemp, BITMAP_SIZE, BITMAP_OFFSET);
}

Size RecordPage::GetCap() const { return _nCap; }

Size RecordPage::GetUsed() const { return _pUsed->GetUsed(); }

bool RecordPage::Full() const { return _pUsed->Full(); }

void RecordPage::Clear() {
  for (SlotID i = 0; i < _nCap; ++i)
    if (HasRecord(i)) DeleteRecord(i);
}

void RecordPage::Print() const {
#ifdef PRINT_PAGE
  printf("******************** RecordPage ********************\n");
  printf("_Fixed = %d\n", (int)_nFixed);
  printf("_nCap = %d\n", (int)_nCap);
  printf("_nEmptySlotID = %d\n", (int)_nEmptySlotID);
  printf("_pUsed = %d\n", (int)_pUsed->GetUsed());
  for (Size i = 0; i < _nCap; ++i)
    if (_pUsed->Get(i)) printf("%d, ", (int)i);
  printf("\n");
  printf("****************************************************\n");
#endif
}

SlotID RecordPage::InsertRecord(const uint8_t* src) {
  if (src == nullptr) {
    auto e = NullptrException("RecordPage::InsertRecord");
    std::cout << e.what() << "\n";
    throw e;
  }

  _bModified = true;

  if (_pUsed->Full()) {
    auto e = RecordPageFullException(_nPageID);
    std::cout << e.what() << "\n";
    throw e;
  }

  // 寻找空的槽位，插入数据
  // 利用_pUsed位图判断槽位是否使用，插入后需要更新_pUsed
  // 需要优化查找空槽的算法
  // 确保了一定有空槽
  FindNextEmptySlot();
  SlotID nSlotID = _nEmptySlotID;

  _pUsed->Set(nSlotID);
  SetData(src, _nFixed, BITMAP_OFFSET + BITMAP_SIZE + nSlotID * _nFixed);

  return nSlotID;
}

uint8_t* RecordPage::GetRecord(SlotID nSlotID) {
  // 先检查是否有该Record
  if (!_pUsed->Get(nSlotID)) {
    auto e = RecordPageSlotUnusedException(nSlotID);
    std::cout << e.what() << "\n";
    throw e;
  }

  uint8_t* data = new uint8_t[_nFixed];
  // 使用GetData实现读数据
  GetData(data, _nFixed, BITMAP_OFFSET + BITMAP_SIZE + nSlotID * _nFixed);
  return data;
}

bool RecordPage::HasRecord(SlotID nSlotID) { return _pUsed->Get(nSlotID); }

void RecordPage::DeleteRecord(SlotID nSlotID) {
  // 先检查是否有该Record
  if (!_pUsed->Get(nSlotID)) {
    auto e = RecordPageSlotUnusedException(nSlotID);
    std::cout << e.what() << "\n";
    throw e;
  }

  _bModified = true;

  // 需要设置_pUsed
  // 现在是惰性删除，只标记unused
  _pUsed->Unset(nSlotID);

  // 删除之后肯定有空位
  // （认为delete操作是离散的）
  // 采取均匀使用的策略，即slotID大的优先使用，优先填满整个page
  if (_pUsed->Get(_nEmptySlotID) || _nEmptySlotID < nSlotID)
    _nEmptySlotID = nSlotID;
}

void RecordPage::UpdateRecord(SlotID nSlotID, const uint8_t* src) {
  if (src == nullptr) {
    auto e = NullptrException("RecordPage::UpdateRecord");
    std::cout << e.what() << "\n";
    throw e;
  }

  if (!_pUsed->Get(nSlotID)) {
    auto e = RecordPageSlotUnusedException(nSlotID);
    std::cout << e.what() << "\n";
    throw e;
  }

  SetData(src, _nFixed, BITMAP_OFFSET + BITMAP_SIZE + nSlotID * _nFixed);
}

}  // namespace dbtrain_mysql
