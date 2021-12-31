#ifndef DBTRAIN_MYSQL_DATABASE_H
#define DBTRAIN_MYSQL_DATABASE_H

#include "defines.h"
#include "entity_manager.h"
#include "manager/index_manager.h"
#include "page/database_page.h"
#include "table.h"

namespace dbtrain_mysql {

class Database : public EntityManager {
 public:
  Database(DatabasePage* pDatabasePage);
  Database(PageID nDatabasePageID);
  virtual ~Database();

  /**
   * @brief 获取表的指针
   *
   * @param sTableName 表名
   * @return Table* 表的指针
   */
  Table* GetTable(const String& sTableName);
  /**
   * @brief 创建一张表
   *
   * @param sTableName 表名
   * @param iSchema 列参数
   */
  void CreateTable(const String& sTableName, const Schema& iSchema);
  /**
   * @brief 删除一张表
   *
   * @param sTableName 表名
   */
  void DropTable(const String& sTableName);
  /**
   * @brief 重命名一张表
   *
   * @param sOldTableName 表的原名称
   * @param sNewTableName 表的新名称
   */
  void RenameTable(const String& sOldTableName, const String& sNewTableName);
  /**
   * @brief 获取数据库内所有表的名称
   *
   * @return std::vector<String> 数据库内所有表的名称
   */
  std::vector<String> GetTableNames();
  /**
   * @brief 获取表的列信息
   *
   * @return std::vector<String> 表的列信息
   */
  std::vector<String> GetColumnNames(const String& sTableName);
  IndexManager* GetIndexManager() const;

  virtual EntityType GetEntityType() const;

 protected:
  IndexManager* _pIndexManagerPageID;
};

}  // namespace dbtrain_mysql

#endif
