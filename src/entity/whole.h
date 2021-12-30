#ifndef DBTRAIN_MYSQL_WHOLE_H
#define DBTRAIN_MYSQL_WHOLE_H

#include "database.h"
#include "defines.h"
#include "entity_manager.h"
#include "page/whole_page.h"

namespace dbtrain_mysql {

class Whole : public EntityManager {
 public:
  Whole(WholePage* pWholePage);
  Whole(PageID pWholePageID);
  virtual ~Whole() = default;

  /**
   * @brief 获取表的指针
   *
   * @param sTableName 表名
   * @return Table* 表的指针
   */
  Database* GetDatabase(const String& sDatabaseName);
  /**
   * @brief 创建一张表
   *
   * @param sTableName 表名
   * @param iSchema 列参数
   * @return Table* 表的指针
   */
  Database* CreateDatabase(const String& sDatabaseName);
  /**
   * @brief 删除一张表
   *
   * @param sTableName 表名
   */
  void DropDatabase(const String& sDatabaseName);
  /**
   * @brief 重命名一张表
   *
   * @param sOldTableName 表的原名称
   * @param sNewTableName 表的新名称
   */
  void RenameDatabase(const String& sOldDatabaseName,
                      const String& sNewDatabaseName);
  /**
   * @brief 获取数据库内所有表的名称
   *
   * @return std::vector<String> 数据库内所有表的名称
   */
  std::vector<String> GetDatabaseNames() const;

  virtual EntityType GetEntityType() const;
};

}  // namespace dbtrain_mysql

#endif