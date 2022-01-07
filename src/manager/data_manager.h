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
  Table* GetTable(const String& sTableName) const;
  /**
   * @brief 创建一张表
   *
   * @param sTableName 表名
   * @param iSchema 列参数
   * @return Table* 表的指针
   */
  void CreateTable(const String& sTableName, const Schema& iSchema) const;
  /**
   * @brief 删除一张表
   *
   * @param sTableName 表名
   */
  void DropTable(const String& sTableName) const;
  /**
   * @brief 重命名一张表
   *
   * @param sOldTableName 表的原名称
   * @param sNewTableName 表的新名称
   */
  void RenameTable(const String& sOldTableName,
                   const String& sNewTableName) const;
  /**
   * @brief 获取数据库内所有表的名称
   *
   * @return std::vector<String> 数据库内所有表的名称
   */
  std::vector<String> GetTableNames() const;
  /**
   * @brief 获取表的列信息
   *
   * @return std::vector<String> 表的列信息
   */
  std::vector<String> GetColumnNames(const String& sTableName) const;
  /**
   * @brief 获得列在表中的位置信息
   */
  FieldID GetColID(const String& sTableName, const String& sColName) const;
  /**
   * @brief 获得列的类型
   */
  FieldType GetColType(const String& sTableName, const String& sColName) const;
  /**
   * @brief 获得列的长度
   */
  Size GetColSize(const String& sTableName, const String& sColName) const;
  Record* GetRecord(const String& sTableName,
                    const PageSlotID& nPageSlotID) const;
  std::vector<Record*> GetTableInfos(const String& sTableName) const;

  // ------------------------ RECORD ------------------------
  std::pair<std::vector<String>, std::vector<Record*>> Join(
      std::map<String, std::vector<PageSlotID>>& iResultMap,
      std::vector<Condition*>& iJoinConds);
  std::vector<PageSlotID> Search(const String& sTableName, Condition* pCond,
                                 const std::vector<Condition*>& iIndexCond,
                                 int limit, int offset);
  uint32_t Delete(const String& sTableName, Condition* pCond,
                  const std::vector<Condition*>& iIndexCond);
  uint32_t Update(const String& sTableName, Condition* pCond,
                  const std::vector<Condition*>& iIndexCond,
                  const std::vector<Transform>& iTrans);
  PageSlotID Insert(const String& sTableName,
                    const std::vector<Field*>& iValueVec);
  PageSlotID Insert(const String& sTableName,
                    const std::vector<String>& iRawVec);

  // ------------------------ INDEX ------------------------
  void CreateIndex(const String& sTableName, const String& sColName);
  void DropIndex(const String& sTableName, const String& sColName);
  bool IsIndex(const String& sTableName, const String& sColName) const;
  Index* GetIndex(const String& sTableName, const String& sColName) const;
  std::vector<Record*> GetIndexInfos() const;
  void AddPrimaryKey(const String& sTableName, const std::vector<String> sColNameVec);

 protected:
  Whole* _pWhole;
  Database* _pDatabase;

 private:
  void CheckDatabaseUsed() const;
};

}  // namespace dbtrain_mysql

#endif
