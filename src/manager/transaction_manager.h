#ifndef DBTRAIN_MYSQL_TRANSACTION_MANAGER_H
#define DBTRAIN_MYSQL_TRANSACTION_MANAGER_H

#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

#include "defines.h"
#include "transaction/transaction.h"

namespace dbtrain_mysql {

class RecoveryManager;
class Instance;

class TransactionManager {
  friend class Instance;

 public:
  TransactionManager();
  ~TransactionManager() = default;

  Transaction *Begin();
  void Commit(const Transaction *txn);
  void Abort(const Transaction *txn);

 private:
  // TxnID to be allocated next
  TxnID _txnID;
  RecoveryManager *_pRecoveryManager;
  Instance *_pInstance;

  // queue of posible active TxnID, to find min active TxnID
  std::queue<TxnID> _posibleActiveTxnID;
  // set of active TxnID
  std::set<TxnID> _activeTxnIDSet;
  // num of Txn whose activeTxnIDSet contains 'TxnID'
  std::unordered_map<TxnID, int> _coveredNum;

  // to get min TxnID and its delelte record
  std::queue<std::pair<TxnID, std::vector<WriteRecord>>> _deleteWaitingList;

  void ProcessDelete();
  bool Active(TxnID txnID) const;
};

}  // namespace dbtrain_mysql

#endif  // TRANSACTION_MANAGER_H_
