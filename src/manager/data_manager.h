#ifndef DBTRAIN_MYSQL_DATA_MANAGER_H
#define DBTRAIN_MYSQL_DATA_MANAGER_H

#include "defines.h"
#include "entity/database.h"
#include "entity/table.h"
#include "entity/whole.h"

namespace dbtrain_mysql {

class DataManager {
 public:
  DataManager();
  ~DataManager();

  // ------------------------ DATABASE ------------------------
  /**
   * @brief 使用数据库
   *
   * @param sTableName 数据库名
   */
  void UseDatabase(const String& sDatabaseName);
  /**
   * @brief 创建一个数据库
   *
   * @param sTableName 数据库名
   */
  void CreateDatabase(const String& sDatabaseName);
  /**
   * @brief 删除一个数据库
   *
   * @param sTableName 数据库名
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

  // ------------------------ TABLE ------------------------
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

 protected:
  Whole* whole;
  Database* database;

  void CheckDatabaseUsed() const;
};

}  // namespace dbtrain_mysql

#endif
