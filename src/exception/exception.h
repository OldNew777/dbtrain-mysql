#ifndef DBTRAIN_MYSQL_EXCEPTION_H
#define DBTRAIN_MYSQL_EXCEPTION_H

#include <defines.h>

#include <exception>

namespace dbtrain_mysql {

class Exception : public std::exception {
 protected:
  String _msg;

 public:
  Exception() : _msg("Info unknown") {}
  Exception(const String& msg) : _msg(msg) {}
  virtual const char* what() const throw() {
    return ("Exception : " + _msg).c_str();
  }
};

}  // namespace dbtrain_mysql

#endif