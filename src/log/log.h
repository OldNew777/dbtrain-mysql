#ifndef DBTRAIN_MYSQL_LOG_H
#define DBTRAIN_MYSQL_LOG_H

#include "defines.h"
#include "record/record.h"
#include "transaction/write_record.h"

namespace dbtrain_mysql {

class Log {
 public:
  String sTableName;
  PageSlotID pageSlotID;

  explicit Log(const String& sTableName, const PageSlotID& pageSlotID);
  ~Log() = default;
};

}  // namespace dbtrain_mysql

#endif