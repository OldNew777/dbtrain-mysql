#ifndef DBTRAIN_MYSQL_TABLE_EXCEPTION_H
#define DBTRAIN_MYSQL_TABLE_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class TableException : public Exception {
 public:
  TableException() : Exception() { _className = "TableException"; }
  TableException(const String& msg) : Exception(msg) {
    _className = "TableException";
  }

 protected:
  String _table = "";
};

class TableNotExistException : public TableException {
 public:
  TableNotExistException() : TableException() {
    _className = "TableNotExistException";
  }
  TableNotExistException(const String& table) {
    _className = "TableNotExistException";
    this->_table = table;
    _msg = "Table '" + table + "' does not exist";
  }
};

class TableExistException : public TableException {
 public:
  TableExistException() : TableException() {
    _className = "TableExistException";
  }
  TableExistException(const String& table) {
    _className = "TableExistException";
    this->_table = table;
    _msg = "Table '" + table + "' already exists";
  }
};

}  // namespace dbtrain_mysql

#endif
