#ifndef DBTRAIN_MYSQL_DATABASE_H
#define DBTRAIN_MYSQL_DATABASE_H

#include "defines.h"
#include "entity_manager.h"
#include "manager/index_manager.h"
#include "page/database_page.h"
#include "result/results.h"
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
  /**
   * @brief 增添主键
   */
  IndexManager* GetIndexManager() const;

  // ------------------------ RECORD ------------------------
  std::vector<PageSlotID> Search(const String& sTableName, Condition* pCond,
                                 const std::vector<Condition*>& iIndexCond);
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
  bool IsIndex(const String& sTableName, const String& sColName);
  Index* GetIndex(const String& sTableName, const String& sColName);
  void AddPrimaryKey(const String& sTableName, const std::vector<String> sColName);
  void DropPrimaryKey(const String& sTableName, const String& sColName);
  std::pair<String, String> GetForeignKey(const String& sTableName, const String& sColName);
  std::vector<Record*> GetIndexInfos();

  virtual void Clear() override;

  virtual EntityType GetEntityType() const;

 protected:
  IndexManager* _pIndexManager;

  std::vector<PageSlotID> _GetDuplicated(const String& sTableName,
                                        const String& sColName, Field* pField);
    bool _CheckHaveNullPK(MemResult* result, const std::vector<String>& sColNameVec);
    bool _CheckHaveDuplicatePK(MemResult* result,const std::vector<String>& sColNameVec);
};

}  // namespace dbtrain_mysql

#endif
