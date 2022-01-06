#ifndef DBTRAIN_MYSQL_FIELD_LIST_EXCEPTION_H
#define DBTRAIN_MYSQL_FIELD_LIST_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class FieldListException : public Exception {
 public:
  FieldListException() : Exception() { _className = "FieldListException"; }
  FieldListException(const String& msg) : Exception(msg) {
    _className = "FieldListException";
  }
};

}  // namespace dbtrain_mysql

#endif