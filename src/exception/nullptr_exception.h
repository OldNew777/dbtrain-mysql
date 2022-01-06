#ifndef DBTRAIN_MYSQL_NULLPTR_EXCEPTION_H
#define DBTRAIN_MYSQL_NULLPTR_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class NullptrException : public Exception {
 public:
  NullptrException() : Exception() {
    _className = "NullptrException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  NullptrException(const String& function) : _function(function) {
    _className = "NullptrException";
    _msg = "Nullptr exception in function '" + function + "'";
    _msg = _className + ": " + _msg;
  }
  NullptrException(const String& function, const String& msg)
      : _function(function) {
    _className = "NullptrException";
    _msg = "Nullptr exception in function '" + function + "', " + msg;
    _msg = _className + ": " + _msg;
  }

 protected:
  String _function = "";
};

}  // namespace dbtrain_mysql

#endif
