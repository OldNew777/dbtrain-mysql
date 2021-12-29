#ifndef DBTRAIN_MYSQL_ENTITY_H
#define DBTRAIN_MYSQL_ENTITY_H

#include "defines.h"
#include "page/manager_page.h"
#include "record/record.h"

namespace dbtrain_mysql {

enum class EntityType {
  DATABASE_TYPE = 0,
  TABLE_TYPE = 1,
  MYSQL_TYPE = 2,
};

class Entity {
 public:
  Entity() = default;
  virtual ~Entity();

  /**
   * @brief 生成一个未填充数据的空记录体
   *
   * @return Record* 生成的空记录体
   */
  Record* EmptyRecord() const;

  /**
   * @brief 清空页面所有存储记录
   *
   */
  virtual void Clear();

  virtual EntityType GetEntityType() const = 0;

 protected:
  ManagerPage* pManagerPage;
  PageID _nHeadID;
  PageID _nTailID;
  /**
   * @brief 表示一个非满页编号，可用于构建一个时空高效的记录插入算法。
   */
  PageID _nNotFull;

  /**
   * @brief 查找一个可用于插入新记录的页面，不存在时自动添加一个新的页面
   *
   */
  void FindNextNotFull();

  /**
   * @brief 往后查找一个可用于插入新记录的页面，直到target停止（包括）
   *
   * @return 是否查找到可插入的页面
   *
   */
  bool NextNotFullUntil(PageID target);

  virtual void Init();
};

}  // namespace dbtrain_mysql

#endif
