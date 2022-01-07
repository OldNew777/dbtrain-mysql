#ifndef DBTRAIN_MYSQL_INSTANCE_H
#define DBTRAIN_MYSQL_INSTANCE_H

#include "defines.h"
#include "entity/schema.h"
#include "field/fields.h"
#include "index/index.h"
#include "manager/data_manager.h"
#include "record/transform.h"
#include "result/results.h"

namespace dbtrain_mysql {

class Instance {
 public:
  Instance();
  ~Instance();

  void UseDatabase(const String &sDatabaseName);
  void CreateDatabase(const String &sDatabaseName);
  void DropDatabase(const String &sDatabaseName);
  void RenameDatabase(const String &sOldDatabaseName,
                      const String &sNewDatabaseName);
  std::vector<String> GetDatabaseNames() const;

  void CreateTable(const String &sTableName, const Schema &iSchema);
  void DropTable(const String &sTableName);
  void RenameTable(const String &sOldTableName, const String &sNewTableName);
  /**
   * @brief 获得列在表中的位置信息
   */
  FieldID GetColID(const String &sTableName, const String &sColName) const;
  /**
   * @brief 获得列的类型
   */
  FieldType GetColType(const String &sTableName, const String &sColName) const;
  /**
   * @brief 获得列的长度
   */
  Size GetColSize(const String &sTableName, const String &sColName) const;

  std::vector<PageSlotID> Search(const String &sTableName, Condition *pCond,
                                 const std::vector<Condition *> &iIndexCond,
                                 int limit = INT32_MAX, int offset = 0);
  uint32_t Delete(const String &sTableName, Condition *pCond,
                  const std::vector<Condition *> &iIndexCond);
  uint32_t Update(const String &sTableName, Condition *pCond,
                  const std::vector<Condition *> &iIndexCond,
                  const std::vector<Transform> &iTrans);
  PageSlotID Insert(const String &sTableName,
                    const std::vector<Field *> &iValueVec);
  PageSlotID Insert(const String &sTableName,
                    const std::vector<String> &iRawVec);

  Record *GetRecord(const String &sTableName,
                    const PageSlotID &nPageSlotID) const;
  std::vector<Record *> GetTableInfos(const String &sTableName) const;
  std::vector<String> GetTableNames() const;
  std::vector<String> GetColumnNames(const String &sTableName) const;
  /**
   * @brief 获取一个Table *指针，要求存在表，否则报错
   */
  Table *GetTable(const String &sTableName) const;

  /**
   * @brief 判断列是否为索引列
   */
  bool IsIndex(const String &sTableName, const String &sColName) const;
  /**
   * @brief 获取一个Index*指针，要求存在索引，否则报错
   */
  Index *GetIndex(const String &sTableName, const String &sColName) const;
  std::vector<Record *> GetIndexInfos() const;
  void CreateIndex(const String &sTableName, const String &sColName);
  void DropIndex(const String &sTableName, const String &sColName);
  void DropPrimaryKey(const String &sTableName, const String &sColName);

  /**
   * @brief 实现多个表的JOIN操作
   *
   * @param iResultMap 表名和对应的常量Filter过程后PageSlotID结果的Map
   * @param iJoinConds 所有表示Join条件的Condition的Vector
   * @return std::pair<std::vector<String>, std::vector<Record *>>
   * Pair第一项为JOIN结果对应的Table列的列名，列的顺序自行定义；
   * Pair第二项为JOIN结果，结果数据Record*中的字段顺序需要和列名一致。
   */
  std::pair<std::vector<String>, std::vector<Record *>> Join(
      std::map<String, std::vector<PageSlotID>> &iResultMap,
      std::vector<Condition *> &iJoinConds);

  void AddPrimaryKey(const String& sTableName, const std::vector<String> sColNameVec);
 protected:
  DataManager *_pDataManager;
};

}  // namespace dbtrain_mysql

#endif
