#include "entity.h"

#include "macros.h"
#include "os/os.h"
#include "page/record_page.h"
#include "record/fixed_record.h"
#include "settings.h"

namespace dbtrain_mysql {

Entity::~Entity() { delete _pManagerPage; }

void Entity::Init() {
  _nHeadID = _pManagerPage->GetHeadID();
  _nTailID = _pManagerPage->GetTailID();
  _nNotFull = _nHeadID;
}

void Entity::Clear() {
#ifdef DELETE_DEBUG
  printf("\n-------------- Clear Begin --------------\n");
  printf("_nHeadID = %d\n", int(_nHeadID));
  printf("_nTailID = %d\n", int(_nTailID));
#endif
  LinkedPage pLinkedPage(_nHeadID);
  pLinkedPage.ReleaseListAll();
#ifdef DELETE_DEBUG
  printf("\n--------------- Clear End ---------------\n\n");
#endif
}

Record* Entity::EmptyRecord() const {
  return new FixedRecord(_pManagerPage->GetFieldSize(),
                         _pManagerPage->GetTypeVec(),
                         _pManagerPage->GetSizeVec());
}

void Entity::FindNextNotFull() {
  // 快速查找非满记录页面算法
  // 不要同时建立两个指向相同磁盘位置的且可变对象，否则会出现一致性问题
  //   充分利用链表性质，注意全满时需要在结尾_pManager
  //       ->GetTailID对应结点后插入新的结点，并更新_pManager的TailID
  // 只需要保证均摊复杂度较低即可

  PageID searchFlag = _nNotFull;
  if (NextNotFullUntil(_pManagerPage->GetTailID())) return;
  _nNotFull = _pManagerPage->GetHeadID();
  // searchFlag会重复搜索一次
  if (NextNotFullUntil(searchFlag)) return;

  // 需要插入新的page
  RecordPage newPage(_pManagerPage->GetTotalSize(), true);
  _nNotFull = newPage.GetPageID();
  LinkedPage tailPageBefore(_pManagerPage->GetTailID());
  tailPageBefore.PushBack(&newPage);

  _nTailID = _nNotFull;
  _pManagerPage->SetTailID(_nNotFull);
}

bool Entity::NextNotFullUntil(PageID target) {
  bool unStop = _nNotFull != NULL_PAGE;
  // 顺序往链表后面查找
  // 沿用了record_page的思想
  while (unStop) {
    RecordPage page(_nNotFull);
    if (!page.Full()) return true;
    unStop = _nNotFull != target;
    _nNotFull = page.GetNextID();
  }
  return false;
}

}  // namespace dbtrain_mysql