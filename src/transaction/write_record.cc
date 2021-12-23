#include "write_record.h"

#include "system/instance.h"

namespace dbtrain_mysql {

WriteRecord::WriteRecord(const OrderType& orderType, const String& sTableName,
                         const PageSlotID& pageSlotID)
    : orderType(orderType), sTableName(sTableName), pageSlotID(pageSlotID) {}

WriteRecord::~WriteRecord() {}

void WriteRecord::Commit(Instance* _pInstance) const {
  if (orderType == OrderType::DELETE_TYPE)
    _pInstance->DeleteForce(sTableName, pageSlotID);
}

void WriteRecord::Abort(Instance* _pInstance) const {
  if (orderType == OrderType::INSERT_TYPE)
    _pInstance->DeleteForce(sTableName, pageSlotID);
}

OrderType WriteRecord::GetOrderType() const { return orderType; }
PageSlotID WriteRecord::GetPageSlotID() const { return pageSlotID; }
String WriteRecord::GetTableName() const { return sTableName; }

}  // namespace dbtrain_mysql