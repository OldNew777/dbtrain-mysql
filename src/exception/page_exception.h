#ifndef DBTRAIN_MYSQL_PAGE_EXCEPTION_H
#define DBTRAIN_MYSQL_PAGE_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"
#include "field/field.h"

namespace dbtrain_mysql {

class PageException : public Exception {
 public:
  PageException() : Exception() { _className = "PageException"; }
  PageException(const String& msg) : Exception(msg) {
    _className = "PageException";
  }
};

class RecordPageException : public PageException {
 public:
  RecordPageException() : PageException() {
    _className = "RecordPageException";
  }
  RecordPageException(const String& msg) : PageException(msg) {
    _className = "RecordPageException";
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
  }

 protected:
  PageID _nPageID;
};

class RecordTypeException : public PageException {
 public:
  RecordTypeException() {
    _className = "RecordTypeException";
    _msg = "Unknown record type";
  }
  RecordTypeException(const String& msg) : PageException(msg) {
    _className = "RecordTypeException";
  }
};

}  // namespace dbtrain_mysql

#endif
