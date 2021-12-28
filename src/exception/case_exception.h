#ifndef DBTRAIN_MYSQL_CASE_EXCEPTION_H
#define DBTRAIN_MYSQL_CASE_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class CaseException : public Exception {
 public:
  CaseException() : Exception() { _className = "CaseException"; }
};

}  // namespace dbtrain_mysql

#endif
