#ifndef DBTRAIN_MYSQL_PAGE_EXCEPTION_H
#define DBTRAIN_MYSQL_PAGE_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"
#include "field/field.h"

namespace dbtrain_mysql {

class PageException : public Exception {
 public:
  PageException() : Exception() {
    _className = "PageException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  PageException(const String& msg) : Exception(msg) {
    _className = "PageException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
};

class RecordPageException : public PageException {
 public:
  RecordPageException() : PageException() {
    _className = "RecordPageException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
  RecordPageException(const String& msg) : PageException(msg) {
    _className = "RecordPageException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
};

class RecordPageSlotUnusedException : public RecordPageException {
 private:
  RecordPageSlotUnusedException() = delete;
  RecordPageSlotUnusedException(const String& msg) = delete;

 public:
  RecordPageSlotUnusedException(SlotID nSlotID) : _nSlotID(nSlotID) {
    _className = "RecordPageSlotUnusedException";
    _msg = "Slot " + std::to_string(_nSlotID) + " is unused";
    _msg = _className + ": " + _msg;
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
    _className = "RecordPageFullException";
    _msg = "RecordPage " + std::to_string(_nPageID) + " is full";
    _msg = _className + ": " + _msg;
  }

 protected:
  PageID _nPageID;
};

class RecordTypeException : public PageException {
 public:
  RecordTypeException() {
    _className = "RecordTypeException";
    _msg = "Unknown record type";
    _msg = _className + ": " + _msg;
  }
  RecordTypeException(const String& msg) : PageException(msg) {
    _className = "RecordTypeException";
    _msg = _className + ": " + _msg.substr(_msg.find(":") + 2);
  }
};

}  // namespace dbtrain_mysql

#endif
