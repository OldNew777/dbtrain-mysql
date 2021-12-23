#include "log.h"

namespace dbtrain_mysql {

Log::Log(const String& sTableName, const PageSlotID& pageSlotID)
    : sTableName(sTableName), pageSlotID(pageSlotID) {}
}  // namespace dbtrain_mysql