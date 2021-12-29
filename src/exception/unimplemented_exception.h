#ifndef DBTRAIN_MYSQL_UNIMPLEMENTED_EXCEPTION_H
#define DBTRAIN_MYSQL_UNIMPLEMENTED_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class UnimplementedException : public Exception {
 public:
  UnimplementedException() : Exception() {
    _className = "UnimplementedException";
  }
  UnimplementedException(const String& function) : _function(function) {
    _className = "UnimplementedException";
    _msg = "Unimplemented exception in function '" + function + "'";
  }
  UnimplementedException(const String& function, const String& msg)
      : _function(function) {
    _className = "UnimplementedException";
    _msg = "Unimplemented exception in function '" + function + "', " + msg;
  }

 protected:
  String _function = "";
};

}  // namespace dbtrain_mysql

#endif
