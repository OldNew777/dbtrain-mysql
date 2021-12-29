#ifndef DBTRAIN_MYSQL_WRITE_RECORD_H
#define DBTRAIN_MYSQL_WRITE_RECORD_H

#include "defines.h"
#include "entity/table.h"

namespace dbtrain_mysql {

class Instance;

class WriteRecord {
 private:
  String sTableName;
  OrderType orderType;
  PageSlotID pageSlotID;

 public:
  explicit WriteRecord(const OrderType& orderType, const String& sTableName,
                       const PageSlotID& pageSlotID);
  ~WriteRecord();

  void Commit(Instance* _pInstance) const;
  void Abort(Instance* _pInstance) const;

  OrderType GetOrderType() const;
  PageSlotID GetPageSlotID() const;
  String GetTableName() const;
};

}  // namespace dbtrain_mysql

#endif  // WRITE_RECORD_H_