#ifndef DBTRAIN_MYSQL_NULLPTR_EXCEPTION_H
#define DBTRAIN_MYSQL_NULLPTR_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class NullptrException : public Exception {
 public:
  NullptrException() : Exception() {}
  NullptrException(const String& function) : _function(function) {
    _msg = "Nullptr exception in function '" + function + "'";
  }
  NullptrException(const String& function, const String& msg)
      : _function(function) {
    _msg = "Nullptr exception in function '" + function + "', " + msg;
  }

  virtual const char* what() const throw() {
    return ("NullptrException : " + _msg).c_str();
  }

 protected:
  String _function = "";
};

}  // namespace dbtrain_mysql

#endif
