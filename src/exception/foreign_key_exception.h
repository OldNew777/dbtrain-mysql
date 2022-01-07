#ifndef DBTRAIN_MYSQL_FOREIGN_KEY_EXCEPTION_H
#define DBTRAIN_MYSQL_FOREIGN_KEY_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class ForeignKeyException : public Exception {
 public:
  ForeignKeyException() : Exception() {
    _className = "ForeignKeyException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  ForeignKeyException(const String& msg) : Exception(msg) {
    _className = "ForeignKeyException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
};

}  // namespace dbtrain_mysql

#endif