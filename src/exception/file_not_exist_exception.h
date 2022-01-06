#ifndef DBTRAIN_MYSQL_FILE_NOT_EXIST_EXCEPTION_H
#define DBTRAIN_MYSQL_FILE_NOT_EXIST_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class FileNotExistException : public Exception {
 public:
  FileNotExistException() : Exception() {
    _className = "FileNotExistException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
};

}  // namespace dbtrain_mysql

#endif