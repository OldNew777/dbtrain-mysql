// #include "system/instance.h"

// #include <assert.h>
// #include <stdio.h>
// #include <stdlib.h>

// #include <algorithm>
// #include <iostream>
// #include <set>

// #include "condition/conditions.h"
// #include "datastruct/hashes.h"
// #include "exception/exceptions.h"
// #include "manager/table_manager.h"
// #include "record/fixed_record.h"
// #include "settings.h"

// namespace dbtrain_mysql {

// Instance::Instance() {
//   _pTableManager = new TableManager();
//   _pIndexManager = new IndexManager();
//   _pTransactionManager = new TransactionManager();
//   _pRecoveryManager = new RecoveryManager();

//   _pTransactionManager->_pRecoveryManager = _pRecoveryManager;
//   _pTransactionManager->_pInstance = this;
//   _pRecoveryManager->_pInstance = this;
// }

// Instance::~Instance() {
//   delete _pTableManager;
//   delete _pIndexManager;
//   delete _pTransactionManager;
//   delete _pRecoveryManager;
// }

// Table* Instance::GetTable(const String& sTableName) const {
//   return _pTableManager->GetTable(sTableName);
// }

// bool Instance::CreateTable(const String& sTableName, const Schema& iSchema,
//                            bool useTxn) {
//   if (useTxn) {
//     std::vector<Column> columns;
//     for (Size i = 0; i < iSchema.GetSize(); ++i)
//       columns.push_back(iSchema.GetColumn(i));
//     Column txnColumn("TransactionID", FieldType::INT_TYPE);
//     columns.push_back(txnColumn);
//     Schema iSchemaTxn(columns);
//     _pTableManager->AddTable(sTableName, iSchemaTxn);
//   } else {
//     _pTableManager->AddTable(sTableName, iSchema);
//   }
//   return true;
// }

// bool Instance::DropTable(const String& sTableName) {
//   for (const auto& sColName : _pIndexManager->GetTableIndexes(sTableName))
//     _pIndexManager->DropIndex(sTableName, sColName);
//   _pTableManager->DropTable(sTableName);
//   return true;
// }

// FieldID Instance::GetColID(const String& sTableName,
//                            const String& sColName) const {
//   Table* pTable = GetTable(sTableName);
//   if (pTable == nullptr) throw TableNotExistException(sTableName);
//   return pTable->GetPos(sColName);
// }

// FieldType Instance::GetColType(const String& sTableName,
//                                const String& sColName) const {
//   Table* pTable = GetTable(sTableName);
//   if (pTable == nullptr) throw TableNotExistException(sTableName);
//   return pTable->GetType(sColName);
// }

// Size Instance::GetColSize(const String& sTableName,
//                           const String& sColName) const {
//   Table* pTable = GetTable(sTableName);
//   if (pTable == nullptr) throw TableNotExistException(sTableName);
//   return pTable->GetSize(sColName);
// }

// bool CmpPageSlotID(const PageSlotID& iA, const PageSlotID& iB) {
//   if (iA.first == iB.first) return iA.second < iB.second;
//   return iA.first < iB.first;
// }

// std::vector<PageSlotID> Intersection(std::vector<PageSlotID> iA,
//                                      std::vector<PageSlotID> iB) {
//   std::sort(iA.begin(), iA.end(), CmpPageSlotID);
//   std::sort(iB.begin(), iB.end(), CmpPageSlotID);
//   std::vector<PageSlotID> iRes{};
//   std::set_intersection(iA.begin(), iA.end(), iB.begin(), iB.end(),
//                         std::back_inserter(iRes));
//   return iRes;
// }

// std::vector<PageSlotID> Instance::Search(
//     const String& sTableName, Condition* pCond,
//     const std::vector<Condition*>& iIndexCond, Transaction* txn) {
//   Table* pTable = GetTable(sTableName);
//   if (pTable == nullptr) throw TableNotExistException(sTableName);
//   std::vector<PageSlotID> ans;
//   if (iIndexCond.size() > 0) {
//     IndexCondition* pIndexCond =
//     dynamic_cast<IndexCondition*>(iIndexCond[0]); assert(pIndexCond !=
//     nullptr); auto iName = pIndexCond->GetIndexName(); auto iRange =
//     pIndexCond->GetIndexRange(); std::vector<PageSlotID> iRes =
//         GetIndex(iName.first, iName.second)->Range(iRange.first,
//         iRange.second);
//     for (Size i = 1; i < iIndexCond.size(); ++i) {
//       IndexCondition* pIndexCond =
//       dynamic_cast<IndexCondition*>(iIndexCond[i]); auto iName =
//       pIndexCond->GetIndexName(); auto iRange = pIndexCond->GetIndexRange();
//       iRes = Intersection(iRes, GetIndex(iName.first, iName.second)
//                                     ->Range(iRange.first, iRange.second));
//     }
//     ans = iRes;
//   } else
//     ans = pTable->SearchRecord(pCond);

//   if (txn != nullptr) {
// #ifdef MVCC_DEBUG
//     printf("\n********************* Search ***********************\n");
//     printf("***************** Ans before MVCC ******************\n");
//     for (auto iPair : ans) {
//       PrintPageSlotID(iPair);
//       printf(", ");
//     }
//     printf("\n");
//     printf("********************* TxnIDs ***********************\n");
// #endif

//     auto iter = ans.begin();
//     while (iter != ans.end()) {
//       PageSlotID psID = *iter;
//       Record* pRecord = pTable->GetRecord(psID.first, psID.second);
//       IntField* txnID_field =
//           dynamic_cast<IntField*>(pRecord->GetField(pRecord->GetSize() - 1));
//       TxnID txnID = txnID_field->GetIntData();

// #ifdef MVCC_DEBUG
//       printf("%d, ", int(txnID));
// #endif

//       if (!txn->Valid(txnID)) {
//         iter = ans.erase(iter);
//       } else {
//         ++iter;
//       }
//       delete pRecord;
//     }

// #ifdef MVCC_DEBUG
//     printf("\n");
//     printf("**************** Ans before filter *****************\n");
//     for (auto iPair : ans) {
//       PrintPageSlotID(iPair);
//       printf(", ");
//     }
//     printf("\n");
//     printf("******************** Deleted ***********************\n");
//     txn->PrintDeleted();
// #endif

//     iter = ans.begin();
//     while (iter != ans.end()) {
//       if (txn->Deleted(*iter))
//         iter = ans.erase(iter);
//       else
//         ++iter;
//     }

// #ifdef MVCC_DEBUG
//     printf("***************** Ans after filter *****************\n");
//     for (auto iPair : ans) {
//       PrintPageSlotID(iPair);
//       printf(", ");
//     }
//     printf("\n");
//     printf("********************** End *************************\n\n");
// #endif
//   }
//   return ans;
// }

// PageSlotID Instance::Insert(const String& sTableName,
//                             const std::vector<String>& iRawVec,
//                             Transaction* txn) {
//   Table* pTable = GetTable(sTableName);
//   if (pTable == nullptr) throw TableNotExistException(sTableName);
//   Record* pRecord = pTable->EmptyRecord();
//   if (txn != nullptr) {
//     // add transaction_id to record
//     std::vector<String> iRawVec_Txn = iRawVec;
//     iRawVec_Txn.push_back(to_string(txn->GetTxnID()));
//     pRecord->Build(iRawVec_Txn);
//   } else {
//     pRecord->Build(iRawVec);
//   }

//   PageSlotID iPair = pTable->InsertRecord(pRecord);
//   if (txn != nullptr) {
//     txn->AddWriteRecord(WriteRecord(OrderType::INSERT_TYPE, sTableName,
//     iPair)); _pRecoveryManager->AddLog(txn->GetTxnID(), Log(sTableName,
//     iPair));
//   }

//   // Handle Insert on Index
//   if (_pIndexManager->HasIndex(sTableName)) {
//     auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
//     for (const auto& sCol : iColNames) {
//       FieldID nPos = pTable->GetPos(sCol);
//       Field* pKey = pRecord->GetField(nPos);
//       _pIndexManager->GetIndex(sTableName, sCol)->Insert(pKey, iPair);
//     }
//   }

//   delete pRecord;
//   return iPair;
// }

// uint32_t Instance::Delete(const String& sTableName, Condition* pCond,
//                           const std::vector<Condition*>& iIndexCond,
//                           Transaction* txn) {
//   auto iResVec = Search(sTableName, pCond, iIndexCond);
//   Table* pTable = GetTable(sTableName);
//   bool bHasIndex = _pIndexManager->HasIndex(sTableName);
//   for (const auto& iPair : iResVec) {
//     // Handle Delete on Index
//     if (bHasIndex) {
//       Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
//       auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
//       for (const auto& sCol : iColNames) {
//         FieldID nPos = pTable->GetPos(sCol);
//         Field* pKey = pRecord->GetField(nPos);
//         _pIndexManager->GetIndex(sTableName, sCol)->Delete(pKey, iPair);
//       }
//     }

//     if (txn == nullptr)
//       pTable->DeleteRecord(iPair.first, iPair.second);
//     else
//       txn->AddWriteRecord(
//           WriteRecord(OrderType::DELETE_TYPE, sTableName, iPair));
//   }
//   return iResVec.size();
// }

// uint32_t Instance::Update(const String& sTableName, Condition* pCond,
//                           const std::vector<Condition*>& iIndexCond,
//                           const std::vector<Transform>& iTrans,
//                           Transaction* txn) {
//   auto iResVec = Search(sTableName, pCond, iIndexCond);
//   Table* pTable = GetTable(sTableName);
//   bool bHasIndex = _pIndexManager->HasIndex(sTableName);
//   for (const auto& iPair : iResVec) {
//     // Handle Delete on Index
//     if (bHasIndex) {
//       Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
//       auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
//       for (const auto& sCol : iColNames) {
//         FieldID nPos = pTable->GetPos(sCol);
//         Field* pKey = pRecord->GetField(nPos);
//         _pIndexManager->GetIndex(sTableName, sCol)->Delete(pKey, iPair);
//       }
//       delete pRecord;
//     }

//     if (txn == nullptr) {
//       // 原实现是update
//       pTable->UpdateRecord(iPair.first, iPair.second, iTrans);
//     } else {
//       // delete旧record
//       txn->AddWriteRecord(
//           WriteRecord(OrderType::DELETE_TYPE, sTableName, iPair));

//       // insert新record
//       Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
//       for (const auto& iter : iTrans) {
//         pRecord->SetField(iter.GetPos(), iter.GetField());
//       }
//       Field* txnTDField = new IntField(txn->GetTxnID());
//       pRecord->SetField(pRecord->GetSize() - 1, txnTDField);
//       auto iPairNew = pTable->InsertRecord(pRecord);
//       txn->AddWriteRecord(
//           WriteRecord(OrderType::INSERT_TYPE, sTableName, iPairNew));
//       _pRecoveryManager->AddLog(txn->GetTxnID(), Log(sTableName, iPairNew));
//       delete pRecord;
//     }

//     // Handle Insert on Index
//     if (bHasIndex) {
//       Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
//       auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
//       for (const auto& sCol : iColNames) {
//         FieldID nPos = pTable->GetPos(sCol);
//         Field* pKey = pRecord->GetField(nPos);
//         _pIndexManager->GetIndex(sTableName, sCol)->Insert(pKey, iPair);
//       }
//       delete pRecord;
//     }
//   }
//   return iResVec.size();
// }

// Record* Instance::GetRecord(const String& sTableName, const PageSlotID&
// iPair,
//                             Transaction* txn) const {
//   Table* pTable = GetTable(sTableName);
//   Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
//   if (txn != nullptr) pRecord->Remove(pRecord->GetSize() - 1);
//   return pRecord;
// }

// std::vector<Record*> Instance::GetTableInfos(const String& sTableName) const
// {
//   std::vector<Record*> iVec{};
//   for (const auto& sName : GetColumnNames(sTableName)) {
//     FixedRecord* pDesc = new FixedRecord(
//         3,
//         {FieldType::STRING_TYPE, FieldType::STRING_TYPE,
//         FieldType::INT_TYPE}, {COLUMN_NAME_SIZE, 10, 4});
//     pDesc->SetField(0, new StringField(sName));
//     pDesc->SetField(1,
//                     new StringField(toString(GetColType(sTableName,
//                     sName))));
//     pDesc->SetField(2, new IntField(GetColSize(sTableName, sName)));
//     iVec.push_back(pDesc);
//   }
//   return iVec;
// }
// std::vector<String> Instance::GetTableNames() const {
//   return _pTableManager->GetTableNames();
// }
// std::vector<String> Instance::GetColumnNames(const String& sTableName) const
// {
//   return _pTableManager->GetColumnNames(sTableName);
// }

// bool Instance::IsIndex(const String& sTableName, const String& sColName)
// const {
//   return _pIndexManager->IsIndex(sTableName, sColName);
// }

// Index* Instance::GetIndex(const String& sTableName,
//                           const String& sColName) const {
//   return _pIndexManager->GetIndex(sTableName, sColName);
// }

// std::vector<Record*> Instance::GetIndexInfos() const {
//   std::vector<Record*> iVec{};
//   for (const auto& iPair : _pIndexManager->GetIndexInfos()) {
//     FixedRecord* pInfo =
//         new FixedRecord(4,
//                         {FieldType::STRING_TYPE, FieldType::STRING_TYPE,
//                          FieldType::STRING_TYPE, FieldType::INT_TYPE},
//                         {TABLE_NAME_SIZE, COLUMN_NAME_SIZE, 10, 4});
//     pInfo->SetField(0, new StringField(iPair.first));
//     pInfo->SetField(1, new StringField(iPair.second));
//     pInfo->SetField(
//         2, new StringField(toString(GetColType(iPair.first, iPair.second))));
//     pInfo->SetField(3, new IntField(GetColSize(iPair.first, iPair.second)));
//     iVec.push_back(pInfo);
//   }
//   return iVec;
// }

// bool Instance::CreateIndex(const String& sTableName, const String& sColName,
//                            FieldType iType) {
//   auto iAll = Search(sTableName, nullptr, {});
//   _pIndexManager->AddIndex(sTableName, sColName, iType);
//   Table* pTable = GetTable(sTableName);
//   // Handle Exists Data
//   for (const auto& iPair : iAll) {
//     FieldID nPos = pTable->GetPos(sColName);
//     Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
//     Field* pKey = pRecord->GetField(nPos);
//     _pIndexManager->GetIndex(sTableName, sColName)->Insert(pKey, iPair);
//     delete pRecord;
//   }
//   return true;
// }

// bool Instance::DropIndex(const String& sTableName, const String& sColName) {
//   auto iAll = Search(sTableName, nullptr, {});
//   Table* pTable = GetTable(sTableName);
//   for (const auto& iPair : iAll) {
//     FieldID nPos = pTable->GetPos(sColName);
//     Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
//     Field* pKey = pRecord->GetField(nPos);
//     _pIndexManager->GetIndex(sTableName, sColName)->Delete(pKey, iPair);
//     delete pRecord;
//   }
//   _pIndexManager->DropIndex(sTableName, sColName);
//   return true;
// }

// std::pair<std::vector<String>, std::vector<Record*>> Instance::Join(
//     std::map<String, std::vector<PageSlotID>>& iResultMap,
//     std::vector<Condition*>& iJoinConds) {
//   // LAB3 BEGIN
//   // TODO:实现正确且高效的表之间JOIN过程

//   //
//   ALERT:由于实现临时表存储具有一定难度，所以允许JOIN过程中将中间结果保留在内存中，不需要存入临时表
//   // ALERT:一定要注意，存在JOIN字段值相同的情况，需要特别重视
//   //
//   ALERT:针对于不同的JOIN情况（此处只需要考虑数据量和是否为索引列），可以选择使用不同的JOIN算法
//   // ALERT:JOIN前已经经过了Filter过程
//   // ALERT:建议不要使用不经过优化的NestedLoopJoin算法

//   // TIPS:JoinCondition中保存了JOIN两方的表名和列名
//   //
//   TIPS:利用GetTable(TableName)的方式可以获得Table*指针，之后利用lab1中的Table::GetRecord获得初始Record*数据
//   //
//   TIPs:利用Table::GetColumnNames可以获得Table初始的列名，与初始Record*顺序一致
//   //
//   TIPS:Record对象添加了Copy,Sub,Add,Remove函数，方便同学们对于Record进行处理
//   // TIPS:利用GetColID/Type/Size三个函数可以基于表名和列名获得列的信息
//   // TIPS:利用IsIndex可以判断列是否存在索引
//   // TIPS:利用GetIndex可以获得索引Index*指针

//   //
//   EXTRA:JOIN的表的数量超过2时，所以需要先计算一个JOIN执行计划（不要求复杂算法）,有兴趣的同学可以自行实现
//   // EXTRA:在多表JOIN时，可以采用并查集或执行树来确定执行JOIN的数据内容

//   // 预先获取各record
//   std::map<String, std::vector<Record*>> iRecordMap;

//   std::pair<std::vector<String>, std::vector<Record*>> ans;
//   if (iResultMap.size() == 0) return ans;

//   bool processed = false;

//   //   //   Index Join
//   //   if (!processed && iJoinConds.size() == 1) {
//   //     JoinCondition* condition =
//   dynamic_cast<JoinCondition*>(iJoinConds[0]);
//   //     // B若有Index，将其调整到A的位置
//   //     if (!IsIndex(condition->sTableA, condition->sColA) &&
//   //         IsIndex(condition->sTableB, condition->sColB)) {
//   //       String temp = condition->sTableA;
//   //       condition->sTableA = condition->sTableB;
//   //       condition->sTableB = temp;
//   //       temp = condition->sColA;
//   //       condition->sColA = condition->sColB;
//   //       condition->sColB = temp;
//   //     }

//   //     // 只有一个where_clause条件，且至少有一个有Index
//   //     if (IsIndex(condition->sTableA, condition->sColA)) {
//   //       // 预获取数据
//   //       Table* tableA = GetTable(condition->sTableA);
//   //       Table* tableB = GetTable(condition->sTableB);
//   //       Size fieldID_A = tableA->GetPos(condition->sColA),
//   //            fieldID_B = tableB->GetPos(condition->sColB);
//   //       FieldType fieldType = tableA->GetType(condition->sColA);
//   //       assert(fieldType == tableB->GetType(condition->sColB));

//   //       std::vector<PageSlotID>& psVec = iResultMap[condition->sTableB];
//   //       iRecordMap[condition->sTableB];
//   //       auto mapIter = iRecordMap.find(condition->sTableB);
//   //       for (Size i = 0; i < psVec.size(); ++i) {
//   //         PageSlotID nPageSlotID = psVec[i];
//   //         mapIter->second.push_back(
//   //             tableB->GetRecord(psVec[i].first, psVec[i].second));
//   //       }

//   //       // 若有Index，用Index.Range查询
//   //       // TODO:
//   //       // 有bug：iResultMap的数据已经经过常量过滤，但Index里的没有！！！
//   //       // 如果要再检验一遍是否在iResultMap中，复杂度就大于hash join了
//   //       std::vector<PageSlotID>& dataB = iResultMap[condition->sTableB];
//   //       if (IsIndex(condition->sTableA, condition->sColA)) {
//   //         processed = true;

//   //         Index* indexA = GetIndex(condition->sTableA, condition->sColA);
//   //         for (Size j = 0; j < dataB.size(); ++j) {
//   //           Record* recordB = iRecordMap[condition->sTableB][j];
//   //           Field *fieldB = recordB->GetField(fieldID_B),
//   //                 *fieldB_right = fieldB->Copy();
//   //           fieldB_right->Add();
//   //           auto rangeAns = indexA->Range(fieldB, fieldB_right);
//   //           for (Size i = 0; i < rangeAns.size(); ++i) {
//   //             Record* recordA =
//   //                 tableA->GetRecord(rangeAns[i].first,
//   rangeAns[i].second);
//   //             recordA->Add(recordB);
//   //             ans.second.push_back(recordA);
//   //           }
//   //           delete fieldB_right;
//   //         }
//   //       }
//   //     }
//   //   }

//   // Hash Join
//   if (!processed) {
//     // TODO:
//     // 有bug，当where_clause里的table不包含在iResultMap中，会出现查询bug
//     // 在目前框架下无法由我解决，故搁置
//     for (auto iter = iResultMap.begin(); iter != iResultMap.end(); ++iter) {
//       Table* table = GetTable(iter->first);
//       for (Size i = 0; i < iter->second.size(); ++i) {
//         iRecordMap[iter->first].push_back(
//             table->GetRecord(iter->second[i].first, iter->second[i].second));
//       }
//     }

// #ifdef JOIN_DEBUG
//     std::cout << "\n$$$$$$$$$$$$$$$$$$$ ALL DATA $$$$$$$$$$$$$$$$$$$$$\n\n";
//     static int markCharNum = 30;
//     for (auto iter = iRecordMap.begin(); iter != iRecordMap.end(); ++iter) {
//       int leftMarkCharNum = (markCharNum - iter->first.length() - 2) / 2;
//       for (int i = 0; i < leftMarkCharNum; ++i) std::cout << '-';
//       std::cout << ' ' << iter->first << ' ';
//       for (int i = 0;
//            i < markCharNum - leftMarkCharNum - iter->first.length() - 2; ++i)
//         std::cout << '-';
//       std::cout << "\n";

//       for (Size j = 0; j < iter->second.size(); ++j) {
//         Record* record = iter->second[j];
//         std::cout << record->ToString() << "\n";
//       }

//       std::cout << "------------------------------\n\n";
//     }
//     std::cout << "$$$$$$$$$$$$$$$$$$$ ALL DATA $$$$$$$$$$$$$$$$$$$$$\n\n";
// #endif

//     // 拼接Record
//     Size filedID_base;
//     vector<Record*> recordVec;
//     // 并查集
//     std::set<String> tableJoint;

//     std::map<String, Size> fieldID_base_map;

//     // 初始化一个
//     for (Size i = 0; i < iJoinConds.size(); ++i) {
//       JoinCondition* condition = dynamic_cast<JoinCondition*>(iJoinConds[i]);
//       if (iResultMap.find(condition->sTableA) == iResultMap.end()) continue;

//       fieldID_base_map[condition->sTableA] = 0;
//       std::vector<Record*> dataA = iRecordMap[condition->sTableA];
//       tableJoint.insert(condition->sTableA);
//       Table* table = GetTable(condition->sTableA);

//       auto columeNames = table->GetColumnNames();
//       filedID_base = columeNames.size();
//       ans.first = columeNames;
//       for (auto iter = dataA.begin(); iter != dataA.end(); ++iter) {
//         recordVec.push_back((*iter)->Copy());
//       }

// #ifdef JOIN_DEBUG
//       std::cout << "----------------------------\n";
//       for (Size i = 0; i < ans.first.size(); ++i) {
//         std::cout << ans.first[i] << " ";
//       }
//       std::cout << std::endl;
//       for (Size i = 0; i < recordVec.size(); ++i) {
//         std::cout << recordVec[i]->ToString() << std::endl;
//       }
//       std::cout << "----------------------------\n\n";
// #endif

//       break;
//     }

//     std::vector<Size> unprocessedConditionIndex;
//     for (Size i = 0; i < iJoinConds.size(); ++i)
//       unprocessedConditionIndex.push_back(i);

//     while (unprocessedConditionIndex.size() > 0) {
//       auto conditionIter = unprocessedConditionIndex.begin();
//       while (conditionIter != unprocessedConditionIndex.end()) {
//         JoinCondition* condition =
//             dynamic_cast<JoinCondition*>(iJoinConds[*conditionIter]);
//         bool joinFlag = true;
//         // 若仅作为where_clause的搜索条件而不join index，则做一个标记
//         if (iResultMap.find(condition->sTableB) == iResultMap.end())
//           joinFlag = false;

//         // B已经joint，将其调整到A的位置
//         if (tableJoint.find(condition->sTableA) == tableJoint.end() &&
//             tableJoint.find(condition->sTableB) != tableJoint.end()) {
//           String temp = condition->sTableA;
//           condition->sTableA = condition->sTableB;
//           condition->sTableB = temp;
//           temp = condition->sColA;
//           condition->sColA = condition->sColB;
//           condition->sColB = temp;
//         }
//         // 都没有join，留到下一轮处理
//         if (tableJoint.find(condition->sTableA) == tableJoint.end() &&
//             tableJoint.find(condition->sTableB) == tableJoint.end()) {
//           ++conditionIter;
//           continue;
//         }

//         Table* tableA = GetTable(condition->sTableA);
//         Table* tableB = GetTable(condition->sTableB);
//         FieldType fieldType = tableA->GetType(condition->sColA);
//         assert(fieldType == tableB->GetType(condition->sColB));
//         Size fieldID_A, fieldID_B;

//         // 都join过了，需要遍历并检验
//         if (tableJoint.find(condition->sTableA) != tableJoint.end() &&
//             tableJoint.find(condition->sTableB) != tableJoint.end()) {
//           conditionIter = unprocessedConditionIndex.erase(conditionIter);
//           fieldID_A = fieldID_base_map[condition->sTableA] +
//                       tableA->GetPos(condition->sColA);
//           fieldID_B = fieldID_base_map[condition->sTableB] +
//                       tableB->GetPos(condition->sColB);
//           auto recordVecIter = recordVec.begin();
//           while (recordVecIter != recordVec.end()) {
//             Field *fieldA = (*recordVecIter)->GetField(fieldID_A),
//                   *fieldB = (*recordVecIter)->GetField(fieldID_B);

// #ifdef JOIN_DEBUG
//             std::cout << "Field :  " << fieldA->ToString()
//                       << (Equal(fieldA, fieldB, fieldType) ? " = " : " != ")
//                       << fieldB->ToString() << "\n";
// #endif

//             if (Equal(fieldA, fieldB, fieldType))
//               ++recordVecIter;
//             else {
//               delete *recordVecIter;
//               recordVecIter = recordVec.erase(recordVecIter);
//             }
//           }

// #ifdef JOIN_DEBUG
//           std::cout << "CHECK\n";
//           std::cout << "----------------------------\n";
//           for (Size i = 0; i < ans.first.size(); ++i) {
//             std::cout << ans.first[i] << " ";
//           }
//           std::cout << std::endl;
//           for (Size i = 0; i < recordVec.size(); ++i) {
//             std::cout << recordVec[i]->ToString() << std::endl;
//           }
//           std::cout << "----------------------------\n\n";
// #endif
//           continue;
//         }

//         // 一个join过，一个没有join过
//         conditionIter = unprocessedConditionIndex.erase(conditionIter);
//         tableJoint.insert(condition->sTableB);
//         fieldID_base_map[condition->sTableB] = filedID_base;

//         std::vector<Record*>& dataA = iRecordMap[condition->sTableA];
//         std::vector<Record*>& dataB = iRecordMap[condition->sTableB];
//         fieldID_A = fieldID_base_map[condition->sTableA] +
//                     tableA->GetPos(condition->sColA);
//         fieldID_B = tableB->GetPos(condition->sColB);
//         auto columeNames = tableB->GetColumnNames();

// #ifdef JOIN_DEBUG
//         std::cout << ans.first.size() << " + " << columeNames.size() << " =
//         ";
// #endif

//         ans.first.insert(ans.first.end(), columeNames.begin(),
//                          columeNames.end());

// #ifdef JOIN_DEBUG
//         std::cout << ans.first.size() << "\n";
// #endif

//         HashMapping<Record*>* hashMapping;
//         if (recordVec.size() >= BIG_PRIME * 0.3)
//           hashMapping = new HashTable<Record*>();
//         else
//           hashMapping = new HashMap<Record*>();
//         for (auto iter = recordVec.begin(); iter != recordVec.end(); ++iter)
//           hashMapping->Insert((*iter)->Hash(fieldID_A), *iter);

//         std::vector<Record*> toBeDeleted = recordVec;
//         recordVec.clear();
//         for (auto iter = dataB.begin(); iter != dataB.end(); ++iter) {
//           Record* recordB = *iter;
//           Field* fieldB = recordB->GetField(fieldID_B);
//           uint32_t hash = fieldB->Hash();
//           std::vector<dbtrain_mysql::Record*> hashEntryVec =
//           hashMapping->Get(hash);

//           for (Size i = 0; i < hashEntryVec.size(); ++i) {
//             Record* recordA = hashEntryVec[i];
//             Field* fieldA = recordA->GetField(fieldID_A);
//             // 对每个recordB，遍历相等的recordA，并join起来
//             // 对应duplicate实现的功能
//             if (Equal(fieldA, fieldB, fieldType)) {
//               Record* recordNew = recordA->Copy();
//               if (joinFlag) recordNew->Add(recordB);
//               recordVec.push_back(recordNew);
//             }
//           }
//         }
//         delete hashMapping;
//         for (auto iter = toBeDeleted.begin(); iter != toBeDeleted.end();
//         ++iter)
//           delete *iter;

//         if (joinFlag) filedID_base += columeNames.size();

// #ifdef JOIN_DEBUG
//         std::cout << "----------------------------\n";
//         for (Size i = 0; i < ans.first.size(); ++i) {
//           std::cout << ans.first[i] << " ";
//         }
//         std::cout << std::endl;
//         for (Size i = 0; i < recordVec.size(); ++i) {
//           std::cout << recordVec[i]->ToString() << std::endl;
//         }
//         std::cout << "----------------------------\n\n";
// #endif
//       }
//     }
//     ans.second = recordVec;
//   }

// #ifdef JOIN_DEBUG
//   std::cout << "----------------------------\n";
//   for (Size i = 0; i < ans.first.size(); ++i) {
//     std::cout << ans.first[i] << " ";
//   }
//   std::cout << std::endl;
//   for (Size i = 0; i < ans.second.size(); ++i) {
//     std::cout << ans.second[i]->ToString() << std::endl;
//   }
//   std::cout << "----------------------------\n\n";
// #endif

//   // 析构record
//   for (auto iter = iRecordMap.begin(); iter != iRecordMap.end(); ++iter)
//     for (Size i = 0; i < iter->second.size(); ++i) delete iter->second[i];
//   return ans;

//   // LAB3 END
// }

// void Instance::DeleteForce(const String& sTableName,
//                            const PageSlotID& pageSlotID) {
//   Table* pTable = GetTable(sTableName);
//   pTable->DeleteRecord(pageSlotID.first, pageSlotID.second);
// }

// }  // namespace dbtrain_mysql
