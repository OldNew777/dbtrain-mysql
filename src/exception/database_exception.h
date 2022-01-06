#ifndef DBTRAIN_MYSQL_DATABASE_EXCEPTION_H
#define DBTRAIN_MYSQL_DATABASE_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class DatabaseException : public Exception {
 public:
  DatabaseException() : Exception() {
    _className = "DatabaseException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  DatabaseException(const String& msg) : Exception(msg) {
    _className = "DatabaseException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }

 protected:
  String _database = "";
};

class DatabaseNotExistException : public DatabaseException {
 public:
  DatabaseNotExistException() : DatabaseException() {
    _className = "DatabaseNotExistException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  DatabaseNotExistException(const String& database) {
    _className = "DatabaseNotExistException";
    this->_database = database;
    _msg = "Database '" + database + "' does not exist";
    _msg = _className + ": " + _msg;
  }
};

class DatabaseExistException : public DatabaseException {
 public:
  DatabaseExistException() : DatabaseException() {
    _className = "DatabaseExistException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  DatabaseExistException(const String& database) {
    _className = "DatabaseExistException";
    this->_database = database;
    _msg = "Database '" + database + "' already exists";
    _msg = _className + ": " + _msg;
  }
};

class DatabaseUnusedException : public DatabaseException {
 public:
  DatabaseUnusedException() : DatabaseException() {
    _className = "DatabaseUnusedException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  DatabaseUnusedException(const String& msg) : DatabaseException(msg) {
    _className = "DatabaseUnusedException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
};

}  // namespace dbtrain_mysql

#endif
