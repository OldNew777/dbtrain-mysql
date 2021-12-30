#ifndef DBTRAIN_MYSQL_DATABASE_EXCEPTION_H
#define DBTRAIN_MYSQL_DATABASE_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class DatabaseException : public Exception {
 public:
  DatabaseException() : Exception() { _className = "DatabaseException"; }
  DatabaseException(const String& msg) : Exception(msg) {
    _className = "DatabaseException";
  }

 protected:
  String _database = "";
};

class DatabaseNotExistException : public DatabaseException {
 public:
  DatabaseNotExistException() : DatabaseException() {
    _className = "DatabaseNotExistException";
  }
  DatabaseNotExistException(const String& database) {
    _className = "DatabaseNotExistException";
    this->_database = database;
    _msg = "Database '" + database + "' does not exist";
  }
};

class DatabaseExistException : public DatabaseException {
 public:
  DatabaseExistException() : DatabaseException() {
    _className = "DatabaseExistException";
  }
  DatabaseExistException(const String& database) {
    _className = "DatabaseExistException";
    this->_database = database;
    _msg = "Database '" + database + "' already exists";
  }
};

class DatabaseUnusedException : public DatabaseException {
 public:
  DatabaseUnusedException() : DatabaseException() {
    _className = "DatabaseUnusedException";
  }
};

}  // namespace dbtrain_mysql

#endif
