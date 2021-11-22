#ifndef DBTRAIN_MYSQL_SYSTEM_VISITOR_H
#define DBTRAIN_MYSQL_SYSTEM_VISITOR_H

#include "MYSQLBaseVisitor.h"
#include "antlr4-runtime.h"
#include "system/instance.h"

namespace dbtrain_mysql {

class SystemVisitor : public MYSQLBaseVisitor {
 private:
  Instance* _pDB;

 public:
  SystemVisitor(Instance* pDB);
}

}  // namespace dbtrain_mysql

#endif