#ifndef DBTRAIN_MYSQL_COMPARE_EXCEPTION_H
#define DBTRAIN_MYSQL_COMPARE_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class CompareException : public Exception {
 public:
  CompareException() : Exception() {
    _className = "CompareException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  CompareException(const String& msg) : Exception(msg) {
    _className = "CompareException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
};

}  // namespace dbtrain_mysql

#endif