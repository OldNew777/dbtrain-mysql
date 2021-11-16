#ifndef DBTRAIN_MYSQL_PAGE_EXCEPTION_H
#define DBTRAIN_MYSQL_PAGE_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"
#include "field/field.h"

namespace dbtrain_mysql {

class PageException : public Exception {
 public:
  PageException() : Exception() {}
  PageException(const String& msg) : Exception(msg) {}
  virtual const char* what() const throw() {
    return ("PageException : " + _msg).c_str();
  }
};

class RecordPageException : public PageException {
 public:
  RecordPageException() : PageException() {}
  RecordPageException(const String& msg) : PageException(msg) {}
  virtual const char* what() const throw() {
    return ("RecordPageException : " + _msg).c_str();
  }
};

class RecordPageSlotUnusedException : public RecordPageException {
 private:
  RecordPageSlotUnusedException() = delete;
  RecordPageSlotUnusedException(const String& msg) = delete;

 public:
  RecordPageSlotUnusedException(SlotID nSlotID) : _nSlotID(nSlotID) {
    _msg = "Slot " + std::to_string(_nSlotID) + " is unused";
  }
  virtual const char* what() const throw() {
    return ("RecordPageSlotUnusedException : " + _msg).c_str();
  }

 protected:
  SlotID _nSlotID;
};

class RecordPageFullException : public RecordPageException {
 private:
  RecordPageFullException() = delete;
  RecordPageFullException(const String& msg) = delete;

 public:
  RecordPageFullException(PageID nPageID) : _nPageID(nPageID) {
    _msg = "RecordPage " + std::to_string(_nPageID) + " is full";
  }
  virtual const char* what() const throw() {
    return ("RecordPageFullException : " + _msg).c_str();
  }

 protected:
  PageID _nPageID;
};

class RecordTypeException : public PageException {
 public:
  RecordTypeException() { _msg = "Unknown record type"; }
  RecordTypeException(const String& msg) : PageException(msg) {}
  virtual const char* what() const throw() {
    return ("RecordTypeException : " + _msg).c_str();
  }
};

}  // namespace dbtrain_mysql

#endif
