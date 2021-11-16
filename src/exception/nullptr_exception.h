#ifndef DBTRAIN_MYSQL_NULLPTR_EXCEPTION_H
#define DBTRAIN_MYSQL_NULLPTR_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class NullptrException : public Exception {
 public:
  NullptrException() : Exception() { _className = "NullptrException"; }
  NullptrException(const String& function) : _function(function) {
    _className = "NullptrException";
    _msg = "Nullptr exception in function '" + function + "'";
  }
  NullptrException(const String& function, const String& msg)
      : _function(function) {
    _className = "NullptrException";
    _msg = "Nullptr exception in function '" + function + "', " + msg;
  }

 protected:
  String _function = "";
};

}  // namespace dbtrain_mysql

#endif
