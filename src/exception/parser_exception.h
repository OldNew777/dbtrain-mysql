#ifndef DBTRAIN_MYSQL_PARSER_EXCEPTION_H
#define DBTRAIN_MYSQL_PARSER_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class ParserException : public Exception {
 public:
  ParserException() : Exception() { _className = "ParserException"; }
  ParserException(const String& msg) : Exception(msg) {
    _className = "ParserException";
  }
};

}  // namespace dbtrain_mysql

#endif