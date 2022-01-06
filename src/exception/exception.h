#ifndef DBTRAIN_MYSQL_EXCEPTION_H
#define DBTRAIN_MYSQL_EXCEPTION_H

#include <defines.h>

#include <exception>

namespace dbtrain_mysql {

class Exception : public std::exception {
 protected:
  String _className;
  String _msg;

 public:
  Exception() : _msg("Info unknown") {
    _className = "Exception";
    _msg = _className + ": " + _msg;
  }
  Exception(const String& msg) : _msg(msg) {
    _className = "Exception";
    _msg = _className + ": " + _msg;
  }
  virtual const char* what() const throw() override { return _msg.c_str(); }
};

}  // namespace dbtrain_mysql

#endif