#ifndef DBTRAIN_MYSQL_EXCEPTION_H
#define DBTRAIN_MYSQL_EXCEPTION_H

#include <defines.h>

#include <exception>

namespace dbtrain_mysql {

class Exception : public std::exception {
 protected:
  bool _classNameAdded = false;
  String _className;
  String _msg;

 public:
  Exception() : _msg("Info unknown") { _className = "Exception"; }
  Exception(const String& msg) : _msg(msg) { _className = "Exception"; }
  virtual const char* what() throw() {
    if (!_classNameAdded) {
      _classNameAdded = true;
      _msg = _className + ": " + _msg;
    }
    return _msg.c_str();
  }
};

}  // namespace dbtrain_mysql

#endif