#ifndef DBTRAIN_MYSQL_RECOVERY_MANAGER_H
#define DBTRAIN_MYSQL_RECOVERY_MANAGER_H

#include <map>
#include <vector>

#include "defines.h"
#include "log/log.h"
#include "macros.h"

namespace dbtrain_mysql {

class Instance;

class RecoveryManager {
  friend class Instance;

 public:
  RecoveryManager();
  ~RecoveryManager();

  void Redo();
  void Undo();

  void AddLog(const TxnID& nTxnID, const Log& log);
  void DeleteLog(const TxnID& nTxnID);

 private:
  Instance* _pInstance;

  std::map<TxnID, std::vector<Log>> _iLogMap;

  void Load();
  void Store();
};

}  // namespace dbtrain_mysql

#endif
