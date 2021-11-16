#ifndef DBTRAIN_MYSQL_OS_EXCEPTION_H
#define DBTRAIN_MYSQL_OS_EXCEPTION_H

#include <string>

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class OsException : public Exception {
 public:
  OsException() : Exception() {}
  OsException(const String& msg) : Exception(msg) {}
  virtual const char* what() const throw() {
    return ("OsException : " + _msg).c_str();
  }
};

class NewPageException : public OsException {
 private:
  NewPageException(const String& msg) = delete;

 public:
  NewPageException() { _msg = "Cannot allocate new page"; }
  virtual const char* what() const throw() {
    return ("NewPageException : " + _msg).c_str();
  }
};

class PageNotInitException : public OsException {
 private:
  PageNotInitException() = delete;
  PageNotInitException(const String& msg) = delete;

 public:
  PageNotInitException(int pageID) : _nPageID(pageID) {
    _msg = "Page " + std::to_string(pageID) + " does not initialize";
  }
  virtual const char* what() const throw() {
    return ("PageNotInitException : " + _msg).c_str();
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
    _msg = "Page out of size : " + std::to_string((int)_nPageOffset);
  }
  virtual const char* what() const throw() {
    return ("PageOutOfSizeException : " + _msg).c_str();
  }

 private:
  PageOffset _nPageOffset;
};

}  // namespace dbtrain_mysql

#endif
