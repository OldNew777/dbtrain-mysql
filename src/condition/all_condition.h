#ifndef DBTRAIN_MYSQL_ALL_CONDITION_H
#define DBTRAIN_MYSQL_ALL_CONDITION_H

#include "condition/condition.h"
#include "defines.h"

namespace dbtrain_mysql {

class AllCondition : public Condition {
 public:
  AllCondition();
  ~AllCondition();
  bool Match(const Record& iRecord) const override;

 private:

};

}  // namespace dbtrain_mysql

#endif