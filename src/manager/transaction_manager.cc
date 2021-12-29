#include "manager/transaction_manager.h"

#include "entity/table.h"
#include "manager/recovery_manager.h"
#include "settings.h"

namespace dbtrain_mysql {

TransactionManager::TransactionManager() : _txnID(1) {}

Transaction *TransactionManager::Begin() {
  Transaction *ans = new Transaction(_txnID, _activeTxnIDSet);
  for (const auto &activeID : _activeTxnIDSet) ++_coveredNum[activeID];
  _activeTxnIDSet.insert(_txnID);
  _posibleActiveTxnID.push(_txnID);
  _txnID++;
  return ans;
}

void TransactionManager::Commit(const Transaction *txn) {
  TxnID nTxnID = txn->GetTxnID();
  _pRecoveryManager->DeleteLog(nTxnID);

  std::vector<WriteRecord> deleteVec;
  for (const auto &writeRecord : txn->_writeRecordVec) {
    if (writeRecord.GetOrderType() == OrderType::DELETE_TYPE) {
      deleteVec.push_back(writeRecord);
      _pRecoveryManager->AddLog(
          nTxnID, Log(writeRecord.GetTableName(), writeRecord.GetPageSlotID()));
    }
  }
  if (deleteVec.size() > 0) {
    _deleteWaitingList.push({nTxnID, deleteVec});
  }

  for (const auto &activeID : txn->_activeTxnIDSet) --_coveredNum[activeID];
  _activeTxnIDSet.erase(nTxnID);

  ProcessDelete();
}

void TransactionManager::Abort(const Transaction *txn) {
  TxnID nTxnID = txn->GetTxnID();
  _pRecoveryManager->DeleteLog(nTxnID);

  for (const auto &writeRecord : txn->_writeRecordVec) {
    if (writeRecord.GetOrderType() == OrderType::INSERT_TYPE)
      writeRecord.Abort(_pInstance);
  }

  for (const auto &activeID : txn->_activeTxnIDSet) --_coveredNum[activeID];
  _activeTxnIDSet.erase(nTxnID);

  ProcessDelete();
}

void TransactionManager::ProcessDelete() {
  while (_posibleActiveTxnID.size() > 0 && !Active(_posibleActiveTxnID.front()))
    _posibleActiveTxnID.pop();

#ifdef MVCC_DEBUG
  if (_posibleActiveTxnID.size() > 0)
    printf("_posibleActiveTxnID.front() = %d\n", _posibleActiveTxnID.front());
  if (_deleteWaitingList.size() > 0)
    printf("_deleteWaitingList.top() = %d -> %d\n",
           int(_deleteWaitingList.top().first),
           int(_coveredNum[_deleteWaitingList.top().first]));
#endif

  if (_deleteWaitingList.size() == 0) return;
  std::pair<TxnID, std::vector<WriteRecord>> iPair = _deleteWaitingList.front();

  while ((_posibleActiveTxnID.size() == 0 ||
          iPair.first < _posibleActiveTxnID.front()) &&
         _coveredNum[iPair.first] == 0) {
    // 实际删除某 Txn 的delete数据
    for (const auto &deleteRecord : iPair.second) {
#ifdef MVCC_DEBUG
      PrintPageSlotID(deleteRecord.pageSlotID);
      printf(", ");
#endif

      _deleteWaitingList.pop();
      deleteRecord.Commit(_pInstance);

      // 从 redo list 中删除
      _pRecoveryManager->DeleteLog(iPair.first);
    }

    if (_deleteWaitingList.size() == 0) break;
    iPair = _deleteWaitingList.front();
  }
}

bool TransactionManager::Active(TxnID txnID) const {
  return _activeTxnIDSet.find(txnID) != _activeTxnIDSet.end();
}

}  // namespace dbtrain_mysql
