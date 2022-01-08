#ifndef DBTRAIN_MYSQL_TABLE_H
#define DBTRAIN_MYSQL_TABLE_H

#include <map>

#include "condition/condition.h"
#include "defines.h"
#include "entity.h"
#include "page/table_page.h"
#include "record/record.h"
#include "record/transform.h"

namespace dbtrain_mysql {

class Table : public Entity {
 public:
  Table(TablePage* pTablePage);
  Table(PageID nTablePageID);
  virtual ~Table() = default;

  /**
   * @brief 获取一个指定位置的记录
   *
   * @param nPageID 页编号
   * @param nSlotID 槽编号
   * @return Record* 对应记录
   */
  Record* GetRecord(PageID nPageID, SlotID nSlotID);
  /**
   * @brief 插入一条数据
   *
   * @param pRecord 待插入数据
   * @return PageSlotID 插入的位置
   */
  PageSlotID InsertRecord(Record* pRecord);
  /**
   * @brief 删除一条数据
   *
   * @param nPageID 页编号
   * @param nSlotID 槽编号
   */
  void DeleteRecord(PageID nPageID, SlotID nSlotID);
  /**
   * @brief 更新一条数据
   *
   * @param nPageID 页编号
   * @param nSlotID 槽编号
   * @param iTrans 更新变化方式
   */
  void UpdateRecord(PageID nPageID, SlotID nSlotID,
                    const std::vector<Transform>& iTrans);
  /**
   * @brief 条件检索
   *
   * @param pCond 检索条件
   * @return std::vector<PageSlotID> 符合条件记录的位置
   */
  std::vector<PageSlotID> SearchRecord(Condition* pCond);
  /**
   * @brief 增加主键
   *
   * @param std::vector<String> 增加主键的名字
   * @return std::vector<PageSlotID> 符合条件记录的位置
   */
  void AddPrimaryKey(const std::vector<String>& sColVec);
  void AddForeignKey(const String& sColVec);
  void AddReferedKey(const String& sColVec);
  void AddUniqueKey(const String& sColVec);
  void DropReferedKey(const String& sColVec);
  void DropPrimaryKey(const String& sColName);
  void DropForeignKey(const String& sColName);

  void SearchRecord(std::vector<PageSlotID>& iPairs, Condition* pCond);

  FieldID GetColPos(const String& sCol) const;
  FieldType GetType(const String& sCol) const;
  Size GetSize(const String& sCol) const;
  bool GetIsUnique(const String& sCol) const;
  bool GetCanBeNull(const String& sCol) const;
  bool GetIsPrimary(const String& sCol) const;
  bool GetIsForeign(const String& sCol) const;
  bool GetIsRefered(const String& sCol) const;
  std::vector<Record*> GetTableInfos() const;
  std::vector<String> GetColumnNames() const;

  virtual EntityType GetEntityType() const;

 protected:
  TablePage* _pTablePage;

  void Init();
};

}  // namespace dbtrain_mysql

#endif
