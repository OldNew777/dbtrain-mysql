#ifndef DBTRAIN_MYSQL_TABLE_EXCEPTION_H
#define DBTRAIN_MYSQL_TABLE_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class TableException : public Exception {
 public:
  TableException() : Exception() {
    _className = "TableException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  TableException(const String& msg) : Exception(msg) {
    _className = "TableException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }

 protected:
  String _table = "";
};

class TableNotExistException : public TableException {
 public:
  TableNotExistException() : TableException() {
    _className = "TableNotExistException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  TableNotExistException(const String& table) {
    _className = "TableNotExistException";
    this->_table = table;
    _msg = "Table '" + table + "' does not exist";
    _msg = _className + ": " + _msg;
  }
};

class TableExistException : public TableException {
 public:
  TableExistException() : TableException() {
    _className = "TableExistException";
    _msg = _className + ": " + _msg;
  }
  TableExistException(const String& table) {
    _className = "TableExistException";
    this->_table = table;
    _msg = "Table '" + table + "' already exists";
    _msg = _className + ": " + _msg;
  }
};

}  // namespace dbtrain_mysql

#endif
