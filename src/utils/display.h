#ifndef DBTRAIN_MYSQL_DISPLAY_H
#define DBTRAIN_MYSQL_DISPLAY_H

#include "result/results.h"

namespace dbtrain_mysql {

void PrintTable(std::vector<Result*>& results);

}  // namespace dbtrain_mysql

#endif  // DBTRAIN_MYSQL_DISPLAY_H
