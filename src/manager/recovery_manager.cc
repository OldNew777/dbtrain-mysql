#include "manager/recovery_manager.h"

#include "os/os.h"
#include "page/record_page.h"
#include "record/fixed_record.h"
#include "settings.h"
#include "system/instance.h"

namespace dbtrain_mysql {

RecoveryManager::RecoveryManager() {
  _iLogMap = {};
  Load();
}
RecoveryManager::~RecoveryManager() { Store(); }

void RecoveryManager::Load() {
  RecordPage* pPageRoot = new RecordPage(RECOVERY_MANAGER_PAGEID);
  // 根节点页面为 (TxnID, RecoveryPageID)
  FixedRecord* pRecordRoot =
      new FixedRecord(2, {FieldType::INT_TYPE, FieldType::INT_TYPE}, {4, 4});
  // RecoveryPage为 (TableName, PageID, SlotID)
  FixedRecord* pRecordLog = new FixedRecord(
      3, {FieldType::CHAR_TYPE, FieldType::INT_TYPE, FieldType::INT_TYPE},
      {TABLE_NAME_SIZE, 4, 4});

  // 遍历根节点页面
  while (true) {
    for (Size i = 0, num = 0;
         i < pPageRoot->GetCap() && num < pPageRoot->GetUsed(); ++i) {
      if (!pPageRoot->HasRecord(i)) continue;
      ++num;

      uint8_t* pData = pPageRoot->GetRecord(i);
      pRecordRoot->Load(pData);

      // TxnID, RecoveryPageID
      IntField* pIntFieldTxnID =
          dynamic_cast<IntField*>(pRecordRoot->GetField(0));
      IntField* pIntFieldRecoveryPageID =
          dynamic_cast<IntField*>(pRecordRoot->GetField(1));

      TxnID nTxnID = pIntFieldTxnID->GetIntData();
      PageID nPageID = pIntFieldRecoveryPageID->GetIntData();

      RecordPage* pPageRecovery = new RecordPage(nPageID);

      // 遍历每个TxnID对应的所有Recovery页面
      while (true) {
        for (Size i = 0, num = 0;
             i < pPageRecovery->GetCap() && num < pPageRecovery->GetUsed();
             ++i) {
          if (!pPageRecovery->HasRecord(i)) continue;
          ++num;

          uint8_t* pData = pPageRecovery->GetRecord(i);
          pRecordLog->Load(pData);

          // TableName, PageID, SlotID
          CharField* pCharFieldTableName =
              dynamic_cast<CharField*>(pRecordLog->GetField(0));
          IntField* pIntFieldPageID =
              dynamic_cast<IntField*>(pRecordLog->GetField(1));
          IntField* pIntFieldSlotID =
              dynamic_cast<IntField*>(pRecordLog->GetField(2));

          String sTableName = pCharFieldTableName->GetString();
          PageID sPageID = pIntFieldPageID->GetIntData();
          PageID sSlotID = pIntFieldSlotID->GetIntData();

          _iLogMap[nTxnID].push_back(Log(sTableName, {sPageID, sSlotID}));

          delete[] pData;
        }

        PageID nextPageID = pPageRecovery->GetNextID();
        if (nextPageID != NULL_PAGE) {
          delete pPageRecovery;
          pPageRecovery = new RecordPage(nextPageID);
        } else
          break;
      }

      pPageRecovery->ReleaseListAll();

      delete pPageRecovery;
      delete[] pData;
    }

    PageID nextPageID = pPageRoot->GetNextID();
    if (nextPageID != NULL_PAGE) {
      delete pPageRoot;
      pPageRoot = new RecordPage(nextPageID);
    } else
      break;
  }

  if (pPageRoot->GetPageID() != RECOVERY_MANAGER_PAGEID) {
    delete pPageRoot;
    pPageRoot = new RecordPage(RECOVERY_MANAGER_PAGEID);
  }
  pPageRoot->ReleaseListRight();

  delete pPageRoot;
  delete pRecordRoot;
  delete pRecordLog;
}
void RecoveryManager::Store() {
  RecordPage* pPageRoot = new RecordPage(RECOVERY_MANAGER_PAGEID);
  // 根节点页面为 (TxnID, RecoveryPageID)
  FixedRecord* pRecordRoot =
      new FixedRecord(2, {FieldType::INT_TYPE, FieldType::INT_TYPE}, {4, 4});
  // RecoveryPage为 (TableName, PageID, SlotID)
  FixedRecord* pRecordLog = new FixedRecord(
      3, {FieldType::CHAR_TYPE, FieldType::INT_TYPE, FieldType::INT_TYPE},
      {TABLE_NAME_SIZE, 4, 4});

  pPageRoot->Clear();
  for (const auto& iPair : _iLogMap) {
    if (pPageRoot->Full()) {
#ifdef RECOVERY_DEBUG
      printf("\n");
      printf("--------------- Recovery Root ----------------\n");
      pPageRoot->Print();
      printf("----------------------------------------------\n");
      printf("\n");
#endif

      RecordPage* newpPageRoot = new RecordPage(4 + 4 + 1, true);
      pPageRoot->PushBack(newpPageRoot);
      delete pPageRoot;
      pPageRoot = newpPageRoot;
    }

    RecordPage* pPageRecovery =
        new RecordPage(TABLE_NAME_SIZE + 4 + 4 + 1, true);

    // TxnID, RecoveryPageID
    IntField* pIntFieldTxnID = new IntField(iPair.first);
    IntField* pIntFieldRecoveryPageID =
        new IntField(pPageRecovery->GetPageID());

    pRecordRoot->SetField(0, pIntFieldTxnID);
    pRecordRoot->SetField(1, pIntFieldRecoveryPageID);
    uint8_t pData[4 + 4 + 1];
    pRecordRoot->Store(pData);
    pPageRoot->InsertRecord(pData);

    for (const auto& log : iPair.second) {
      if (pPageRecovery->Full()) {
#ifdef RECOVERY_DEBUG
        printf("\n");
        printf("--------------- Recovery Log -----------------\n");
        pPageRecovery->Print();
        printf("----------------------------------------------\n");
        printf("\n");
#endif

        RecordPage* newpPageRecovery =
            new RecordPage(TABLE_NAME_SIZE + 4 + 4 + 1, true);
        pPageRecovery->PushBack(newpPageRecovery);
        delete pPageRecovery;
        pPageRecovery = newpPageRecovery;
      }

      // TableName, PageID, SlotID
      CharField* pCharFieldTableName = new CharField(log.sTableName);
      IntField* pIntFieldPageID = new IntField(log.pageSlotID.first);
      IntField* pIntFieldSlotID = new IntField(log.pageSlotID.second);

      pRecordLog->SetField(0, pCharFieldTableName);
      pRecordLog->SetField(1, pIntFieldPageID);
      pRecordLog->SetField(2, pIntFieldSlotID);
      uint8_t pData[TABLE_NAME_SIZE + 4 + 4 + 1];
      pRecordLog->Store(pData);
      pPageRecovery->InsertRecord(pData);
    }

#ifdef RECOVERY_DEBUG
    printf("\n");
    printf("--------------- Recovery Log -----------------\n");
    pPageRecovery->Print();
    printf("----------------------------------------------\n");
    printf("\n");
#endif

    delete pPageRecovery;
  }

#ifdef RECOVERY_DEBUG
  printf("\n");
  printf("--------------- Recovery Root ----------------\n");
  pPageRoot->Print();
  printf("----------------------------------------------\n");
  printf("\n");
#endif

  delete pPageRoot;
  delete pRecordRoot;
  delete pRecordLog;
}

void RecoveryManager::Redo() {
  // 将所有Delete且已经Commit（但未实际删除）的数据删除
  // 由于未区分Redo和Undo的类型，故直接一起在Undo处理
}

void RecoveryManager::Undo() {
  // 将所有Insert且未Commit的数据删除
  // 由于未区分Redo和Undo的类型，故直接一起在Undo处理

  for (const auto& iPair : _iLogMap)
    for (const Log& log : iPair.second)
      _pInstance->DeleteForce(log.sTableName, log.pageSlotID);

  _iLogMap.clear();
}

void RecoveryManager::AddLog(const TxnID& nTxnID, const Log& log) {
  _iLogMap[nTxnID].push_back(log);
}

void RecoveryManager::DeleteLog(const TxnID& nTxnID) { _iLogMap.erase(nTxnID); }

}  // namespace dbtrain_mysql
