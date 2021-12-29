#ifndef DBTRAIN_MYSQL_DATABASE_H
#define DBTRAIN_MYSQL_DATABASE_H

#include <map>

#include "defines.h"
#include "entity/schema.h"
#include "entity_manager.h"
#include "page/database_page.h"
#include "table.h"

namespace dbtrain_mysql {

class Database : public EntityManager {
 public:
  Database(DatabasePage* pDatabasePage);
  Database(PageID nDatabaseID);
  virtual ~Database() = default;

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
   * @return Table* 表的指针
   */
  Table* CreateTable(const String& sTableName, const Schema& iSchema);
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
   * @brief 清空数据库内的所有表
   *
   */
  virtual void Clear();
  /**
   * @brief 获取数据库内所有表的名称
   *
   * @return std::vector<String> 数据库内所有表的名称
   */
  std::vector<String> GetTableNames();

  virtual EntityType GetEntityType() const;

 protected:
  virtual void Init() override;
};

}  // namespace dbtrain_mysql

#endif
