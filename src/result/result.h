#ifndef DBTRAIN_MYSQL_RESULT_H
#define DBTRAIN_MYSQL_RESULT_H

#include "defines.h"
#include "record/record.h"

namespace dbtrain_mysql {

class Result {
 public:
  Result(const std::vector<String>& iHeader);
  virtual ~Result() = default;

  virtual void PushBack(Record* pRecord) = 0;
  virtual Record* GetRecord(Size nPos) const = 0;
  virtual Size GetSize() const = 0;
  virtual String ToString() const = 0;
  virtual String Dump() const = 0;
  virtual std::vector<String> ToVector() const = 0;
  virtual void Display() const = 0;

 protected:
  std::vector<String> _iHeader;
};

}  // namespace dbtrain_mysql

#endif
