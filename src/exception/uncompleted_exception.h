#ifndef DBTRAIN_MYSQL_UNCOMPLETED_EXCEPTION_H
#define DBTRAIN_MYSQL_UNCOMPLETED_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class UncompletedException : public Exception {
 public:
  UncompletedException() : Exception() { _className = "UncompletedException"; }
  UncompletedException(const String& function) : _function(function) {
    _className = "UncompletedException";
    _msg = "Uncompleted exception in function '" + function + "'";
  }
  UncompletedException(const String& function, const String& msg)
      : _function(function) {
    _className = "NullptrException";
    _msg = "Uncompleted exception in function '" + function + "', " + msg;
  }

 protected:
  String _function = "";
};

}  // namespace dbtrain_mysql

#endif
