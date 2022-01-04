#include "page/linked_page.h"

#include "exception/page_exception.h"
#include "macros.h"
#include "os/os.h"

namespace dbtrain_mysql {

const PageOffset NEXT_PAGE_OFFSET = 4;
const PageOffset PREV_PAGE_OFFSET = 8;

LinkedPage::LinkedPage() : Page() {
  this->_bModified = true;
  this->_nNextID = NULL_PAGE;
  this->_nPrevID = NULL_PAGE;
}

LinkedPage::LinkedPage(PageID nPageID) : Page(nPageID) {
  this->_bModified = false;
  GetHeader((uint8_t*)&_nNextID, 4, NEXT_PAGE_OFFSET);
  GetHeader((uint8_t*)&_nPrevID, 4, PREV_PAGE_OFFSET);
}

LinkedPage::~LinkedPage() {
  if (_bModified) {
    // Dirty Page Condition
    SetHeader((uint8_t*)&_nNextID, 4, NEXT_PAGE_OFFSET);
    SetHeader((uint8_t*)&_nPrevID, 4, PREV_PAGE_OFFSET);
  }
}

uint32_t LinkedPage::GetNextID() const { return _nNextID; }

uint32_t LinkedPage::GetPrevID() const { return _nPrevID; }

void LinkedPage::SetNextID(PageID nNextID) {
  this->_nNextID = nNextID;
  this->_bModified = true;
}

void LinkedPage::SetPrevID(PageID nPrevID) {
  this->_nPrevID = nPrevID;
  this->_bModified = true;
}

bool LinkedPage::PushBack(LinkedPage* pPage) {
  if (!pPage) return false;
  // 链表结点后增加一个新的链表页面结点
  // ALERT: ！！！一定要注意！！！
  // 不要同时建立两个指向相同磁盘位置的且可变对象，否则会出现一致性问题
  // ALERT:
  // 页面对象完成修改后一定要及时析构，析构会自动调用写回。以方便其他函数重新基于这一页面建立页面对象
  // 需要判断当前页面是否存在后续页面
  // 正确设置当前页面和pPage的PrevID以及NextID

  pPage->SetPrevID(GetPageID());
  pPage->SetNextID(GetNextID());

  PageID newPageID = pPage->GetPageID();
  if (GetNextID() != NULL_PAGE) {
    LinkedPage page_next(GetNextID());
    page_next.SetPrevID(newPageID);
  }
  SetNextID(newPageID);
  return true;
}

PageID LinkedPage::PopBack() {
  // 删除下一个链表结点，返回删除结点的PageID
  // 需要判断当前页面是否存在后续页面
  PageID pageID_next = GetNextID();
  if (pageID_next == NULL_PAGE) throw PageException();

  // 正确设置当前页面的NextID，如果后一个结点不是空页，需要讨论是否存在后两页的PrevID问题
  LinkedPage* page_next = new LinkedPage(pageID_next);
  if (page_next->GetNextID() != NULL_PAGE) {
    LinkedPage page_next2(page_next->GetNextID());
    page_next2.SetPrevID(GetPageID());
  }
  SetNextID(page_next->GetNextID());

  // OS::DeletePage在最后释放被删除的页面
  // 必须先析构page再释放OS页面，否则会引起写入错误
  delete page_next;
  OS::GetOS()->DeletePage(pageID_next);
}

void LinkedPage::RemoveCurrent() {
  if (GetNextID() != NULL_PAGE) {
    LinkedPage page_next(GetNextID());
    page_next.SetPrevID(GetPrevID());
  }
  if (GetPrevID() != NULL_PAGE) {
    LinkedPage page_last(GetPrevID());
    page_last.SetNextID(GetNextID());
  }
  SetPrevID(NULL_PAGE);
  SetNextID(NULL_PAGE);
}

void LinkedPage::ReleaseListRight() {
  _bModified = true;

  OS* os = OS::GetOS();

  PageID pageID = GetNextID();
  while (pageID != NULL_PAGE) {
    LinkedPage page(pageID);
    os->DeletePage(pageID);
    pageID = page.GetNextID();
  }

  SetNextID(NULL_PAGE);
}

void LinkedPage::ReleaseListAll() {
  _bModified = false;
  OS* os = OS::GetOS();

#ifdef DELETE_DEBUG
  int count = 0;
#endif

  PageID pageID = GetNextID();
#ifdef DELETE_DEBUG
  ++count;
#endif
  while (pageID != NULL_PAGE) {
    LinkedPage page(pageID);
    os->DeletePage(pageID);
    pageID = page.GetNextID();
  }
  pageID = GetPrevID();
  while (pageID != NULL_PAGE) {
#ifdef DELETE_DEBUG
    ++count;
#endif
    LinkedPage page(pageID);
    os->DeletePage(pageID);
    pageID = page.GetPrevID();
  }
  os->DeletePage(GetPageID());

#ifdef DELETE_DEBUG
  printf("LinkedPage::ReleaseListAll() : release %d pages\n", count);
#endif
}

}  // namespace dbtrain_mysql
