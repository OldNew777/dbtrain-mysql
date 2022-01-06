#ifndef DBTRAIN_MYSQL_AND_CONDITION_H
#define DBTRAIN_MYSQL_AND_CONDITION_H

#include "condition/condition.h"
#include "defines.h"

namespace dbtrain_mysql {

class AndCondition : public Condition {
 public:
  AndCondition(const std::vector<Condition*>& iCondVec);
  ~AndCondition();
  bool Match(const Record& iRecord) const override;
  void PushBack(Condition* pCond);

 protected:
  std::vector<Condition*> _iCondVec;
};

}  // namespace dbtrain_mysql

#endif