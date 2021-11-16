#ifndef DBTRAIN_MYSQL_INDEX_EXCEPTION_H
#define DBTRAIN_MYSQL_INDEX_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class IndexException : public Exception {
  IndexException() : Exception() {}
  IndexException(const String& msg) : Exception(msg) {}
  virtual const char* what() const throw() {
    return ("IndexException : " + _msg).c_str();
  }
};

}  // namespace dbtrain_mysql

#endif