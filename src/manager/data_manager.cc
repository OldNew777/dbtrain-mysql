#include "data_manager.h"

#include <unordered_set>

#include "condition/conditions.h"
#include "datastruct/hashes.h"
#include "exception/exceptions.h"
#include "macros.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

DataManager::DataManager() {
  _pWhole = new Whole(MYSQL_MANAGER_PAGEID);
  _pDatabase = nullptr;
}

DataManager::~DataManager() { delete _pWhole; }

void DataManager::UseDatabase(const String& sDatabaseName) {
  // shouldn't delete _pDatabase here
  // it will be done by _pWhole
  _pDatabase = _pWhole->GetDatabase(sDatabaseName);
  if (_pDatabase == nullptr) {
    auto e = DatabaseNotExistException(sDatabaseName);
    std::cout << e.what() << "\n";
    throw e;
  }
}

void DataManager::CreateDatabase(const String& sDatabaseName) {
  _pWhole->CreateDatabase(sDatabaseName);
}

void DataManager::DropDatabase(const String& sDatabaseName) {
  if (_pDatabase == _pWhole->GetDatabase(sDatabaseName)) _pDatabase = nullptr;
  _pWhole->DropDatabase(sDatabaseName);
}

void DataManager::RenameDatabase(const String& sOldDatabaseName,
                                 const String& sNewDatabaseName) {
  _pWhole->RenameDatabase(sOldDatabaseName, sNewDatabaseName);
}

std::vector<String> DataManager::GetDatabaseNames() const {
  return _pWhole->GetDatabaseNames();
}

Table* DataManager::GetTable(const String& sTableName) const {
  CheckDatabaseUsed();
  Table* pTable = _pDatabase->GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  return pTable;
}

void DataManager::CreateTable(const String& sTableName,
                              const Schema& iSchema) const {
  CheckDatabaseUsed();
  _pDatabase->CreateTable(sTableName, iSchema);
}

void DataManager::DropTable(const String& sTableName) const {
  CheckDatabaseUsed();
  //TODO: 删除表间关联
  std::vector<std::vector<String> > refPairVec = 
      _pDatabase->GetTableReferedKeys(sTableName);
  std::vector<std::vector<String> > forPairVec = 
      _pDatabase->GetTableForeignKeys(sTableName);
  
  std::map<String, int> tmpMap;
  for(auto& tVec: refPairVec){
    _pDatabase->DropShadowTableKey(tVec[1], SHADOW_STATUS_REFERED_KEY, 
      tVec[2],sTableName, tVec[0]);
  }
  
  for(auto& tVec: forPairVec){
    _pDatabase->DropShadowTableKey(tVec[1], SHADOW_STATUS_FOREIGN_KEY, 
      tVec[2],sTableName, tVec[0]);
  }

  for (const auto& sColName :
       _pDatabase->GetIndexManager()->GetTableIndexes(sTableName))
    _pDatabase->GetIndexManager()->DropIndex(sTableName, sColName);
  _pDatabase->DropTable(sTableName);
  //delete shadow page
  for (const auto& sColName :
       _pDatabase->GetIndexManager()->GetTableIndexes("@" + sTableName))
    _pDatabase->GetIndexManager()->DropIndex("@" + sTableName, sColName);
  _pDatabase->DropTable("@" + sTableName);
}

void DataManager::RenameTable(const String& sOldTableName,
                              const String& sNewTableName) const {
  CheckDatabaseUsed();
  _pDatabase->RenameTable(sOldTableName, sNewTableName);
}

std::vector<String> DataManager::GetTableNames() const {
  CheckDatabaseUsed();
  return _pDatabase->GetTableNames();
}

std::vector<String> DataManager::GetColumnNames(
    const String& sTableName) const {
  CheckDatabaseUsed();
  return _pDatabase->GetColumnNames(sTableName);
}

FieldID DataManager::GetColID(const String& sTableName,
                              const String& sColName) const {
  return GetTable(sTableName)->GetColPos(sColName);
}

FieldType DataManager::GetColType(const String& sTableName,
                                  const String& sColName) const {
  return GetTable(sTableName)->GetType(sColName);
}

Size DataManager::GetColSize(const String& sTableName,
                             const String& sColName) const {
  return GetTable(sTableName)->GetSize(sColName);
}

Record* DataManager::GetRecord(const String& sTableName,
                               const PageSlotID& nPageSlotID) const {
  return GetTable(sTableName)->GetRecord(nPageSlotID.first, nPageSlotID.second);
}

std::vector<Record*> DataManager::GetTableInfos(
    const String& sTableName) const {
  return GetTable(sTableName)->GetTableInfos();
}

std::pair<std::vector<String>, std::vector<Record*>> DataManager::Join(
    std::map<String, std::vector<PageSlotID>>& iResultMap,
    std::vector<Condition*>& iJoinConds) {  // 表之间JOIN过程

  // 由于实现临时表存储具有一定难度，所以JOIN过程中将中间结果保留在内存中，不存入临时表
  // 存在JOIN字段值相同的情况，需要特别重视
  // 针对于不同的JOIN情况（此处只需要考虑数据量和是否为索引列），可以选择使用不同的JOIN算法
  // JOIN前已经经过了Filter过程

  // JoinCondition中保存了JOIN两方的表名和列名
  // 利用GetTable(TableName)的方式可以获得Table*指针，之后利用Table::GetRecord获得初始Record*数据
  // 利用Table::GetColumnNames可以获得Table初始的列名，与初始Record*顺序一致
  // Record对象添加了Copy,Sub,Add,Remove函数，方便同学们对于Record进行处理
  // 利用GetColID/Type/Size三个函数可以基于表名和列名获得列的信息
  // 利用IsIndex可以判断列是否存在索引
  // 利用GetIndex可以获得索引Index*指针

  // 预先获取各record
  std::map<String, std::vector<Record*>> iRecordMap;

  std::pair<std::vector<String>, std::vector<Record*>> ans;
  if (iResultMap.size() == 0) return ans;

  bool processed = false;

  //   //   Index Join
  //   if (!processed && iJoinConds.size() == 1) {
  //     JoinCondition* condition = dynamic_cast<JoinCondition*>(iJoinConds[0]);
  //     // B若有Index，将其调整到A的位置
  //     if (!IsIndex(condition->sTableA, condition->sColA) &&
  //         IsIndex(condition->sTableB, condition->sColB)) {
  //       String temp = condition->sTableA;
  //       condition->sTableA = condition->sTableB;
  //       condition->sTableB = temp;
  //       temp = condition->sColA;
  //       condition->sColA = condition->sColB;
  //       condition->sColB = temp;
  //     }

  //     // 只有一个where_clause条件，且至少有一个有Index
  //     if (IsIndex(condition->sTableA, condition->sColA)) {
  //       // 预获取数据
  //       Table* tableA = GetTable(condition->sTableA);
  //       Table* tableB = GetTable(condition->sTableB);
  //       Size fieldID_A = tableA->GetColPos(condition->sColA),
  //            fieldID_B = tableB->GetColPos(condition->sColB);
  //       FieldType fieldType = tableA->GetType(condition->sColA);
  //       assert(fieldType == tableB->GetType(condition->sColB));

  //       std::vector<PageSlotID>& psVec = iResultMap[condition->sTableB];
  //       iRecordMap[condition->sTableB];
  //       auto mapIter = iRecordMap.find(condition->sTableB);
  //       for (Size i = 0; i < psVec.size(); ++i) {
  //         PageSlotID nPageSlotID = psVec[i];
  //         mapIter->second.push_back(
  //             tableB->GetRecord(psVec[i].first, psVec[i].second));
  //       }

  //       // 若有Index，用Index.Range查询
  //       // TODO:
  //       // 有bug：iResultMap的数据已经经过常量过滤，但Index里的没有！！！
  //       // 如果要再检验一遍是否在iResultMap中，复杂度就大于hash join了
  //       std::vector<PageSlotID>& dataB = iResultMap[condition->sTableB];
  //       if (IsIndex(condition->sTableA, condition->sColA)) {
  //         processed = true;

  //         Index* indexA = GetIndex(condition->sTableA, condition->sColA);
  //         for (Size j = 0; j < dataB.size(); ++j) {
  //           Record* recordB = iRecordMap[condition->sTableB][j];
  //           Field *fieldB = recordB->GetField(fieldID_B),
  //                 *fieldB_right = fieldB->Copy();
  //           fieldB_right->Add();
  //           auto rangeAns = indexA->Range(fieldB, fieldB_right);
  //           for (Size i = 0; i < rangeAns.size(); ++i) {
  //             Record* recordA =
  //                 tableA->GetRecord(rangeAns[i].first, rangeAns[i].second);
  //             recordA->Add(recordB);
  //             ans.second.push_back(recordA);
  //           }
  //           delete fieldB_right;
  //         }
  //       }
  //     }
  //   }

  // Hash Join
  if (!processed) {
    // TODO:
    // 有bug，当where_clause里的table不包含在iResultMap中，会出现查询bug
    // 在目前框架下无法由我解决，故搁置
    for (auto iter = iResultMap.begin(); iter != iResultMap.end(); ++iter) {
      Table* table = GetTable(iter->first);
      for (Size i = 0; i < iter->second.size(); ++i) {
        iRecordMap[iter->first].push_back(
            table->GetRecord(iter->second[i].first, iter->second[i].second));
      }
    }

#ifdef JOIN_DEBUG
    std::cout << "\n$$$$$$$$$$$$$$$$$$$ ALL DATA $$$$$$$$$$$$$$$$$$$$$\n\n";
    static int markCharNum = 30;
    for (auto iter = iRecordMap.begin(); iter != iRecordMap.end(); ++iter) {
      int leftMarkCharNum = (markCharNum - iter->first.length() - 2) / 2;
      for (int i = 0; i < leftMarkCharNum; ++i) std::cout << '-';
      std::cout << ' ' << iter->first << ' ';
      for (int i = 0;
           i < markCharNum - leftMarkCharNum - iter->first.length() - 2; ++i)
        std::cout << '-';
      std::cout << "\n";

      for (Size j = 0; j < iter->second.size(); ++j) {
        Record* record = iter->second[j];
        std::cout << record->ToString() << "\n";
      }

      std::cout << "------------------------------\n\n";
    }
    std::cout << "$$$$$$$$$$$$$$$$$$$ ALL DATA $$$$$$$$$$$$$$$$$$$$$\n\n";
#endif

    // 拼接Record
    Size filedID_base;
    std::vector<Record*> recordVec;
    // 并查集
    std::unordered_set<String> tableJoint;

    std::map<String, Size> fieldID_base_map;

    // 初始化一个
    for (Size i = 0; i < iJoinConds.size(); ++i) {
      JoinCondition* condition = dynamic_cast<JoinCondition*>(iJoinConds[i]);
      if (iResultMap.find(condition->sTableA) == iResultMap.end()) continue;

      fieldID_base_map[condition->sTableA] = 0;
      std::vector<Record*> dataA = iRecordMap[condition->sTableA];
      tableJoint.insert(condition->sTableA);
      Table* table = GetTable(condition->sTableA);

      auto columeNames = table->GetColumnNames();
      filedID_base = columeNames.size();
      ans.first = columeNames;
      for (auto iter = dataA.begin(); iter != dataA.end(); ++iter) {
        recordVec.push_back((*iter)->Clone());
      }

#ifdef JOIN_DEBUG
      std::cout << "----------------------------\n";
      for (Size i = 0; i < ans.first.size(); ++i) {
        std::cout << ans.first[i] << " ";
      }
      std::cout << std::endl;
      for (Size i = 0; i < recordVec.size(); ++i) {
        std::cout << recordVec[i]->ToString() << std::endl;
      }
      std::cout << "----------------------------\n\n";
#endif

      break;
    }

    std::vector<Size> unprocessedConditionIndex;
    for (Size i = 0; i < iJoinConds.size(); ++i)
      unprocessedConditionIndex.push_back(i);

    while (unprocessedConditionIndex.size() > 0) {
      auto conditionIter = unprocessedConditionIndex.begin();
      while (conditionIter != unprocessedConditionIndex.end()) {
        JoinCondition* condition =
            dynamic_cast<JoinCondition*>(iJoinConds[*conditionIter]);
        bool joinFlag = true;
        // 若仅作为where_clause的搜索条件而不join index，则做一个标记
        if (iResultMap.find(condition->sTableB) == iResultMap.end())
          joinFlag = false;

        // B已经joint，将其调整到A的位置
        if (tableJoint.find(condition->sTableA) == tableJoint.end() &&
            tableJoint.find(condition->sTableB) != tableJoint.end()) {
          String temp = condition->sTableA;
          condition->sTableA = condition->sTableB;
          condition->sTableB = temp;
          temp = condition->sColA;
          condition->sColA = condition->sColB;
          condition->sColB = temp;
        }
        // 都没有join，留到下一轮处理
        if (tableJoint.find(condition->sTableA) == tableJoint.end() &&
            tableJoint.find(condition->sTableB) == tableJoint.end()) {
          ++conditionIter;
          continue;
        }

        Table* tableA = GetTable(condition->sTableA);
        Table* tableB = GetTable(condition->sTableB);
        FieldType fieldType = tableA->GetType(condition->sColA);
        if (fieldType != tableB->GetType(condition->sColB)) {
          auto e = RecordTypeException();
          std::cout << e.what() << "\n";
          throw e;
        }
        Size fieldID_A, fieldID_B;

        // 都join过了，需要遍历并检验
        if (tableJoint.find(condition->sTableA) != tableJoint.end() &&
            tableJoint.find(condition->sTableB) != tableJoint.end()) {
          conditionIter = unprocessedConditionIndex.erase(conditionIter);
          fieldID_A = fieldID_base_map[condition->sTableA] +
                      tableA->GetColPos(condition->sColA);
          fieldID_B = fieldID_base_map[condition->sTableB] +
                      tableB->GetColPos(condition->sColB);
          auto recordVecIter = recordVec.begin();
          while (recordVecIter != recordVec.end()) {
            Field *fieldA = (*recordVecIter)->GetField(fieldID_A),
                  *fieldB = (*recordVecIter)->GetField(fieldID_B);

#ifdef JOIN_DEBUG
            std::cout << "Field :  " << fieldA->ToString()
                      << (Equal(fieldA, fieldB) ? " = " : " != ")
                      << fieldB->ToString() << "\n";
#endif

            if (Equal(fieldA, fieldB))
              ++recordVecIter;
            else {
              delete *recordVecIter;
              recordVecIter = recordVec.erase(recordVecIter);
            }
          }

#ifdef JOIN_DEBUG
          std::cout << "CHECK\n";
          std::cout << "----------------------------\n";
          for (Size i = 0; i < ans.first.size(); ++i) {
            std::cout << ans.first[i] << " ";
          }
          std::cout << std::endl;
          for (Size i = 0; i < recordVec.size(); ++i) {
            std::cout << recordVec[i]->ToString() << std::endl;
          }
          std::cout << "----------------------------\n\n";
#endif
          continue;
        }

        // 一个join过，一个没有join过
        conditionIter = unprocessedConditionIndex.erase(conditionIter);
        tableJoint.insert(condition->sTableB);
        fieldID_base_map[condition->sTableB] = filedID_base;

        std::vector<Record*>& dataA = iRecordMap[condition->sTableA];
        std::vector<Record*>& dataB = iRecordMap[condition->sTableB];
        fieldID_A = fieldID_base_map[condition->sTableA] +
                    tableA->GetColPos(condition->sColA);
        fieldID_B = tableB->GetColPos(condition->sColB);
        auto columeNames = tableB->GetColumnNames();

#ifdef JOIN_DEBUG
        std::cout << ans.first.size() << " + " << columeNames.size() << " = ";
#endif

        ans.first.insert(ans.first.end(), columeNames.begin(),
                         columeNames.end());

#ifdef JOIN_DEBUG
        std::cout << ans.first.size() << "\n";
#endif

        HashMapping<Record*>* hashMapping;
        if (recordVec.size() >= BIG_PRIME * 0.3)
          hashMapping = new HashTable<Record*>();
        else
          hashMapping = new HashMap<Record*>();
        for (auto iter = recordVec.begin(); iter != recordVec.end(); ++iter)
          hashMapping->Insert((*iter)->Hash(fieldID_A), *iter);

        std::vector<Record*> toBeDeleted = recordVec;
        recordVec.clear();
        for (auto iter = dataB.begin(); iter != dataB.end(); ++iter) {
          Record* recordB = *iter;
          Field* fieldB = recordB->GetField(fieldID_B);
          uint32_t hash = fieldB->Hash();
          std::vector<Record*> hashEntryVec = hashMapping->Get(hash);

          for (Size i = 0; i < hashEntryVec.size(); ++i) {
            Record* recordA = hashEntryVec[i];
            Field* fieldA = recordA->GetField(fieldID_A);
            // 对每个recordB，遍历相等的recordA，并join起来
            // 对应duplicate实现的功能
            if (Equal(fieldA, fieldB)) {
              Record* recordNew = recordA->Clone();
              if (joinFlag) recordNew->Add(recordB);
              recordVec.push_back(recordNew);
            }
          }
        }
        delete hashMapping;
        for (auto iter = toBeDeleted.begin(); iter != toBeDeleted.end(); ++iter)
          delete *iter;

        if (joinFlag) filedID_base += columeNames.size();

#ifdef JOIN_DEBUG
        std::cout << "----------------------------\n";
        for (Size i = 0; i < ans.first.size(); ++i) {
          std::cout << ans.first[i] << " ";
        }
        std::cout << std::endl;
        for (Size i = 0; i < recordVec.size(); ++i) {
          std::cout << recordVec[i]->ToString() << std::endl;
        }
        std::cout << "----------------------------\n\n";
#endif
      }
    }
    ans.second = recordVec;
  }

#ifdef JOIN_DEBUG
  std::cout << "----------------------------\n";
  for (Size i = 0; i < ans.first.size(); ++i) {
    std::cout << ans.first[i] << " ";
  }
  std::cout << std::endl;
  for (Size i = 0; i < ans.second.size(); ++i) {
    std::cout << ans.second[i]->ToString() << std::endl;
  }
  std::cout << "----------------------------\n\n";
#endif

  // 析构record
  for (auto iter = iRecordMap.begin(); iter != iRecordMap.end(); ++iter)
    for (Size i = 0; i < iter->second.size(); ++i) delete iter->second[i];

  // // delete duplicated fields
  // std::vector<Size> iDuplicatedVec, iRemainVec;
  // std::unordered_set<String> iFieldNameSet;
  // for (int i = ans.first.size() - 1; i >= 0; --i) {
  //   if (iFieldNameSet.find(ans.first[i]) == iFieldNameSet.end()) {
  //     iFieldNameSet.insert(ans.first[i]);
  //     iRemainVec.push_back(i);
  //   } else {
  //     iDuplicatedVec.push_back(i);
  //   }
  // }

  // if (iDuplicatedVec.size() == 0) return ans;

  // for (Record* pRecord : ans.second) {
  //   pRecord->Sub(iRemainVec);
  // }
  // std::vector<String> iColName = std::move(ans.first);
  // for (int i : iDuplicatedVec) {
  //   iColName.erase(iColName.begin() + i);
  // }
  // ans.first = std::move(iColName);

  return ans;
}

std::vector<PageSlotID> DataManager::Search(
    const String& sTableName, Condition* pCond,
    const std::vector<Condition*>& iIndexCond, int limit, int offset) {
  CheckDatabaseUsed();
  std::vector<PageSlotID> ans =
      _pDatabase->Search(sTableName, pCond, iIndexCond);
  ans.erase(ans.begin(), ans.begin() + offset);
  if (limit < ans.size()) ans.erase(ans.begin() + limit, ans.end());
  return ans;
}

uint32_t DataManager::Delete(const String& sTableName, Condition* pCond,
                             const std::vector<Condition*>& iIndexCond) {
  CheckDatabaseUsed();
  return _pDatabase->Delete(sTableName, pCond, iIndexCond);
}

uint32_t DataManager::Update(const String& sTableName, Condition* pCond,
                             const std::vector<Condition*>& iIndexCond,
                             const std::vector<Transform>& iTrans) {
  CheckDatabaseUsed();
  return _pDatabase->Update(sTableName, pCond, iIndexCond, iTrans);
}

PageSlotID DataManager::Insert(const String& sTableName,
                               const std::vector<Field*>& iValueVec) {
  CheckDatabaseUsed();
  return _pDatabase->Insert(sTableName, iValueVec);
}

PageSlotID DataManager::Insert(const String& sTableName,
                               const std::vector<String>& iRawVec) {
  return _pDatabase->Insert(sTableName, iRawVec);
}

void DataManager::CreateIndex(const String& sTableName,
                              const String& sColName) {
  CheckDatabaseUsed();
  _pDatabase->CreateIndex(sTableName, sColName);
}

void DataManager::DropIndex(const String& sTableName, const String& sColName) {
  CheckDatabaseUsed();
  _pDatabase->DropIndex(sTableName, sColName);
}

bool DataManager::IsIndex(const String& sTableName,
                          const String& sColName) const {
  CheckDatabaseUsed();
  return _pDatabase->IsIndex(sTableName, sColName);
}

Index* DataManager::GetIndex(const String& sTableName,
                             const String& sColName) const {
  CheckDatabaseUsed();
  return _pDatabase->GetIndex(sTableName, sColName);
}

std::vector<Record*> DataManager::GetIndexInfos() const {
  CheckDatabaseUsed();
  return _pDatabase->GetIndexInfos();
}

void DataManager::CheckDatabaseUsed() const {
  if (_pDatabase == nullptr) {
    auto e = DatabaseUnusedException("Please USE (DATABASE) first");
    std::cout << e.what() << "\n";
    throw e;
  }
}

void DataManager::AddPrimaryKey(const String& sTableName, const std::vector<String> sColNameVec){
  CheckDatabaseUsed();
  _pDatabase->AddPrimaryKey(sTableName, sColNameVec);
}
void DataManager::DropPrimaryKey(const String& sTableName, const String& sColName) {
  CheckDatabaseUsed();
  _pDatabase->DropPrimaryKey(sTableName, sColName);
}
void DataManager::DropForeignKey(const String& sTableName, const String& sColName) {
  CheckDatabaseUsed();
  _pDatabase->DropShadowTableKey(sTableName,SHADOW_STATUS_FOREIGN_KEY, 
      sColName, "", "");
}
}  // namespace dbtrain_mysql