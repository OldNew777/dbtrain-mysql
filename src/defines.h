#ifndef DBTRAIN_MYSQL_H_
#define DBTRAIN_MYSQL_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <string>
#include <vector>

#include "utils/macros.h"

namespace dbtrain_mysql {

typedef uint32_t PageID;
typedef uint16_t PageOffset;
typedef uint16_t SlotID;
typedef uint16_t FieldID;
typedef std::string String;
typedef uint32_t Size;
typedef uint32_t TxnID;

enum class OrderType {
  INSERT_TYPE = 0,
  DELETE_TYPE = 1,
};

typedef std::pair<PageID, SlotID> PageSlotID;

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

}  // namespace dbtrain_mysql

#endif