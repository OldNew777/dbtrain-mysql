#ifndef DBTRAIN_MYSQL_LINKED_PAGE_H
#define DBTRAIN_MYSQL_LINKED_PAGE_H

#include "defines.h"
#include "page/page.h"

namespace dbtrain_mysql {

class RecoveryManager;

/**
 * @brief 链表结点页面。
 *
 */
class LinkedPage : public Page {
  friend class RecoveryManager;

 public:
  LinkedPage();
  LinkedPage(PageID nPageID);
  virtual ~LinkedPage();

  /**
   * @brief 向当前页面后添加一个新的页面
   *
   * @param _pPage 需要添加的页面
   * @return true 添加成功
   * @return false 添加失败
   */
  bool PushBack(LinkedPage* _pPage);
  /**
   * @brief 删除当前页面后的第一个页面
   *
   * @return PageID 被删除页面的页面编号
   */
  PageID PopBack();
  /**
   * @brief 从链表中删除当前页面
   */
  void RemoveCurrent();
  /**
   * @brief 释放链表中右侧所有页面
   */
  void ReleaseListRight();
  /**
   * @brief 释放链表中所有页面
   */
  void ReleaseListAll();

  PageID GetNextID() const;
  PageID GetPrevID() const;

  void SetNextID(PageID nNextID);
  void SetPrevID(PageID nPrevID);

 protected:
  PageID _nNextID;
  PageID _nPrevID;
};

}  // namespace dbtrain_mysql

#endif  // DBTRAIN_MYSQL_LINKED_PAGE_H