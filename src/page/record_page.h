#ifndef DBTRAIN_MYSQL_RECORD_PAGE_H
#define DBTRAIN_MYSQL_RECORD_PAGE_H

#include "page/linked_page.h"
#include "utils/bitmap.h"

namespace dbtrain_mysql {

class TableManager;

/**
 * @brief 定长记录页面。
 *
 */
class RecordPage : public LinkedPage {
  friend class TableManager;

 public:
  /**
   * @brief 构建一个新的定长记录页面
   * @param nFixed 定长记录长度
   */
  RecordPage(PageOffset nFixed, bool);
  /**
   * @brief 从OS中重新导入一个定长记录页面
   * @param nPageID 页面编号
   */
  RecordPage(PageID nPageID);
  ~RecordPage();

  /**
   * @brief 插入一条定长记录
   *
   * @param src 记录定长格式化后的内容
   * @return SlotID 插入位置的槽编号
   */
  SlotID InsertRecord(const uint8_t* src);
  /**
   * @brief 获取指定位置的记录的内容
   *
   * @param nSlotID 槽编号
   * @return uint8_t* 记录定长格式化的内容
   */
  uint8_t* GetRecord(SlotID nSlotID);
  /**
   * @brief 判断某一个槽是否存在记录
   *
   * @param nSlotID 槽编号
   * @return true 存在记录
   * @return false 不存在记录
   */
  bool HasRecord(SlotID nSlotID);
  /**
   * @brief 删除指定位置的记录
   *
   * @param nSlotID 槽编号
   */
  void DeleteRecord(SlotID nSlotID);
  /**
   * @brief 原地更新一条记录的内容
   *
   * @param nSlotID 槽编号
   * @param src 新的定长格式化内容
   */
  void UpdateRecord(SlotID nSlotID, const uint8_t* src);

  Size GetCap() const;
  Size GetUsed() const;
  bool Full() const;
  void Clear();

  static SlotID CalculateCap(PageOffset nFixed);
  void Print() const;

 private:
  void StoreBitmap();
  void LoadBitmap();

  /**
   * @brief 表示支持的定长记录长度
   */
  PageOffset _nFixed;
  /**
   * @brief 表示页面能容纳的记录数量
   */
  Size _nCap;
  /**
   * @brief 表示槽占用状况的位图
   */
  Bitmap* _pUsed;
  /**
   * @brief 表示一个空槽编号，可用于构建一个时空高效的Record插入算法。
   */
  SlotID _nEmptySlotID;

  /**
   * @brief 查找一个可用于插入新记录的slot
   *
   */
  void FindNextEmptySlot();

  /**
   * @brief 往后查找一个可用于插入新记录的slot，直到target停止（包括）
   *
   * @return 是否查找到可插入的slot
   *
   */
  bool FindNextEmptySlotUntil(SlotID target);
};

}  // namespace dbtrain_mysql

#endif