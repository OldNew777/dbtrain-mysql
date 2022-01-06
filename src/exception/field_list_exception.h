#ifndef DBTRAIN_MYSQL_FIELD_LIST_EXCEPTION_H
#define DBTRAIN_MYSQL_FIELD_LIST_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class FieldListException : public Exception {
 public:
  FieldListException() : Exception() {
    _className = "FieldListException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  FieldListException(const String& msg) : Exception(msg) {
    _className = "FieldListException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
};

}  // namespace dbtrain_mysql

#endif