#ifndef DBTRAIN_MYSQL_TRANSACTION_H
#define DBTRAIN_MYSQL_TRANSACTION_H

#include <set>

#include "defines.h"
#include "write_record.h"

namespace dbtrain_mysql {

class TransactionManager;

class Transaction {
 public:
  friend class TransactionManager;
  explicit Transaction(TxnID txnID, std::set<TxnID> _activeTxnIDSet);
  ~Transaction() = default;

  TxnID GetTxnID() const;
  bool Valid(TxnID dataTxnID) const;
  bool Deleted(PageSlotID nPageSlotID) const;
  void AddWriteRecord(const WriteRecord& writeRecord);

  void PrintDeleted() const;

 private:
  TxnID _txnID;
  std::set<TxnID> _activeTxnIDSet;
  std::vector<WriteRecord> _writeRecordVec;

  std::set<PageSlotID> _deletePageSlotIDSet;
};

}  // namespace dbtrain_mysql

#endif  // TRANSACTION_H_
