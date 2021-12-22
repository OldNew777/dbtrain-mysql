#ifndef DBTRAIN_MYSQL_NOT_CONDITION_H
#define DBTRAIN_MYSQL_NOT_CONDITION_H

#include "condition/condition.h"

namespace dbtrain_mysql {
class NotCondition : public Condition {
 public:
  NotCondition(Condition* pCond);
  ~NotCondition();
  bool Match(const Record& iRecord) const override;

 private:
  Condition* _pCond;
};
}  // namespace dbtrain_mysql

#endif