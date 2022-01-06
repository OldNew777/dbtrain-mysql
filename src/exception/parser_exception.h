#ifndef DBTRAIN_MYSQL_PARSER_EXCEPTION_H
#define DBTRAIN_MYSQL_PARSER_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class ParserException : public Exception {
 public:
  ParserException() : Exception() {
    _className = "ParserException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  ParserException(const String& msg) : Exception(msg) {
    _className = "ParserException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
};

}  // namespace dbtrain_mysql

#endif