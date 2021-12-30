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
   * @brief 获取数据库的指针
   *
   * @param sDatabaseName 数据库名
   * @return Database* 数据库的指针
   */
  Database* GetDatabase(const String& sDatabaseName);
  /**
   * @brief 创建一个数据库
   *
   * @param sDatabaseName 数据库名
   */
  void CreateDatabase(const String& sDatabaseName);
  /**
   * @brief 删除一个数据库
   *
   * @param sDatabaseName 数据库名
   */
  void DropDatabase(const String& sDatabaseName);
  /**
   * @brief 重命名一个数据库
   *
   * @param sOldTableName 数据库的原名称
   * @param sNewTableName 数据库的新名称
   */
  void RenameDatabase(const String& sOldDatabaseName,
                      const String& sNewDatabaseName);
  /**
   * @brief 获取所有数据库的名称
   *
   * @return std::vector<String> 所有数据库的名称
   */
  std::vector<String> GetDatabaseNames() const;

 protected:
  virtual EntityType GetEntityType() const;
};

}  // namespace dbtrain_mysql

#endif
