#ifndef DBTRAIN_MYSQL_TABLE_EXCEPTION_H
#define DBTRAIN_MYSQL_TABLE_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class TableException : public Exception {
 public:
  TableException() : Exception() {}
  TableException(const String& msg) : Exception(msg) {}
  virtual const char* what() const throw() {
    return ("TableException : " + _msg).c_str();
  }

 protected:
  String _table = "";
};

class TableNotExistException : public TableException {
 public:
  TableNotExistException() : TableException() {}
  TableNotExistException(const String& table) {
    this->_table = table;
    _msg = "Table '" + table + "' does not exist";
  }
  virtual const char* what() const throw() {
    return ("TableNotExistException : " + _msg).c_str();
  }
};

class TableExistException : public TableException {
 public:
  TableExistException() : TableException() {}
  TableExistException(const String& table) {
    this->_table = table;
    _msg = "Table '" + table + "' already exists";
  }

  virtual const char* what() const throw() {
    return ("TableExistException : " + _msg).c_str();
  }
};

}  // namespace dbtrain_mysql

#endif
