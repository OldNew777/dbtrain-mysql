#include "transaction/transaction.h"

#include "settings.h"

namespace dbtrain_mysql {

Transaction::Transaction(TxnID txnID, std::set<TxnID> _activeTxnIDSet)
    : _txnID(txnID), _activeTxnIDSet(_activeTxnIDSet) {}

TxnID Transaction::GetTxnID() const { return _txnID; }

bool Transaction::Valid(TxnID dataTxnID) const {
  return (dataTxnID <= _txnID &&
          _activeTxnIDSet.find(dataTxnID) == _activeTxnIDSet.end());
}

bool Transaction::Deleted(PageSlotID nPageSlotID) const {
  return _deletePageSlotIDSet.find(nPageSlotID) != _deletePageSlotIDSet.end();
}

void Transaction::PrintDeleted() const {
#ifdef MVCC_DEBUG
  printf("Transaction::Deleted = ");
  for (const auto& iPair : _deletePageSlotIDSet) {
    PrintPageSlotID(iPair);
    printf(", ");
  }
  printf("\n");
#endif
}

void Transaction::AddWriteRecord(const WriteRecord& writeRecord) {
  _writeRecordVec.push_back(writeRecord);
  if (writeRecord.GetOrderType() == OrderType::DELETE_TYPE)
    _deletePageSlotIDSet.insert(writeRecord.GetPageSlotID());
}

}  // namespace dbtrain_mysql
