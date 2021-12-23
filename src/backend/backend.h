#ifndef DBTRAIN_MYSQL_BACKEND_H
#define DBTRAIN_MYSQL_BACKEND_H

#include "defines.h"
#include "result/results.h"
#include "system/instance.h"

namespace dbtrain_mysql {

bool Exists();
void Init();
void Clear();
void Close();
std::vector<Result*> Execute(Instance* pDB, const String& sSQL);

}  // namespace dbtrain_mysql

#endif