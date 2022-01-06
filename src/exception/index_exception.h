#ifndef DBTRAIN_MYSQL_INDEX_EXCEPTION_H
#define DBTRAIN_MYSQL_INDEX_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class IndexException : public Exception {
 public:
  IndexException() : Exception() {
    _className = "IndexException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  IndexException(const String& msg) : Exception(msg) {
    _className = "IndexException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
};

}  // namespace dbtrain_mysql

#endif