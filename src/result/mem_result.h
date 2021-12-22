#ifndef DBTRAIN_MYSQL_MEM_RESULT_H
#define DBTRAIN_MYSQL_MEM_RESULT_H

#include "defines.h"
#include "result/result.h"

namespace dbtrain_mysql {

class MemResult : public Result {
 public:
  MemResult(const std::vector<String>& iHeader);
  ~MemResult();

  void PushBack(Record* pRecord) override;
  Record* GetRecord(Size nPos) const override;
  Size GetSize() const override;
  String ToString() const override;
  std::vector<String> ToVector() const override;
  void Display() const override;

 private:
  std::vector<Record*> _iData;
};

}  // namespace dbtrain_mysql

#endif
