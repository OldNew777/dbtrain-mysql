#ifndef DBTRAIN_MYSQL_ALTER_EXCEPTION_H
#define DBTRAIN_MYSQL_ALTER_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class AlterException : public Exception {
 public:
  AlterException() : Exception() {
    _className = "AlterException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  AlterException(const String& msg) : Exception(msg) {
    _className = "AlterException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
};

}  // namespace dbtrain_mysql

#endif