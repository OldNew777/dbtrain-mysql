#ifndef DBTRAIN_MYSQL_BASIC_FUNCTION_H
#define DBTRAIN_MYSQL_BASIC_FUNCTION_H

#include <iostream>

#include "defines.h"

namespace dbtrain_mysql {

void PrintPageSlotID(const PageSlotID& nPageSlotID);

String toUpper(const String& str);

}  // namespace dbtrain_mysql

#endif