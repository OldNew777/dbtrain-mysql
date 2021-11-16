#ifndef DBTRAIN_MYSQL_PARSER_EXCEPTION_H
#define DBTRAIN_MYSQL_PARSER_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class ParserException : public Exception {
 public:
  ParserException() : Exception() {}
  ParserException(const String& msg) : Exception(msg) {}
  const char* what() const throw() {
    return ("ParserException : " + _msg).c_str();
  }
};

}  // namespace dbtrain_mysql

#endif