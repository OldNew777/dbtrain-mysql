#ifndef DBTRAIN_MYSQL_DATABASE_H
#define DBTRAIN_MYSQL_DATABASE_H

#include <map>

#include "defines.h"
#include "page/database_page.h"
#include "record/record.h"

namespace dbtrain_mysql {

class Database {
 public:
  Database(PageID nDatabaseID);
  ~Database();

  /**
   * @brief 获取表的PageID
   *
   * @param sTableName 表名
   * @return PageID 表的PageID
   */
  PageID GetTable(const String& sTableName);
  /**
   * @brief 创建一张表
   *
   * @param sTableName 表名
   * @return PageID 表的PageID
   */
  PageID InsertTable(const String& sTableName);
  /**
   * @brief 删除一张表
   *
   * @param sTableName 表名
   */
  void DeleteTable(const String& sTableName);
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
  void Clear();
  /**
   * @brief 获取数据库内所有表的名称
   *
   * @return std::vector<String> 数据库内所有表的名称
   */
  std::vector<String> GetColumnNames();
  /**
   * @brief 生成一个未填充数据的空记录体
   *
   * @return Record* 生成的空记录体
   */
  Record* EmptyRecord() const;

 private:
  DatabasePage* pDatabase;
  PageID _nHeadID;
  PageID _nTailID;
  std::map<String, PageID> _iTableMap;
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
};

}  // namespace dbtrain_mysql

#endif
