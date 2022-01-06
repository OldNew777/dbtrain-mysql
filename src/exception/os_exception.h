#ifndef DBTRAIN_MYSQL_OS_EXCEPTION_H
#define DBTRAIN_MYSQL_OS_EXCEPTION_H

#include <string>

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class OsException : public Exception {
 public:
  OsException() : Exception() {
    _className = "OsException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  OsException(const String& msg) : Exception(msg) {
    _className = "OsException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
};

class NewPageException : public OsException {
 private:
  NewPageException(const String& msg) = delete;

 public:
  NewPageException() {
    _className = "NewPageException";
    _msg = "Cannot allocate new page";
    _msg = _className + ": " + _msg;
  }
};

class PageNotInitException : public OsException {
 private:
  PageNotInitException() = delete;
  PageNotInitException(const String& msg) = delete;

 public:
  PageNotInitException(int pageID) : _nPageID(pageID) {
    _className = "PageNotInitException";
    _msg = "Page " + std::to_string(pageID) + " does not initialize";
    _msg = _className + ": " + _msg;
  }

 private:
  PageID _nPageID;
};

class PageOutOfSizeException : public OsException {
 private:
  PageOutOfSizeException() = delete;
  PageOutOfSizeException(const String& msg) = delete;

 public:
  PageOutOfSizeException(PageOffset nPageOffset) : _nPageOffset(nPageOffset) {
    _className = "PageOutOfSizeException";
    _msg = "Page out of size : " + std::to_string((int)_nPageOffset);
    _msg = _className + ": " + _msg;
  }

 private:
  PageOffset _nPageOffset;
};

}  // namespace dbtrain_mysql

#endif
