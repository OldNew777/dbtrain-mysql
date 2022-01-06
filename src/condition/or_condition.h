#ifndef DBTRAIN_MYSQL_OR_CONDITION_H
#define DBTRAIN_MYSQL_OR_CONDITION_H

#include "condition/condition.h"

namespace dbtrain_mysql {

class OrCondition : public Condition {
 public:
  OrCondition(const std::vector<Condition*>& iCondVec);
  ~OrCondition();
  bool Match(const Record& iRecord) const override;
  void PushBack(Condition* pCond);

 protected:
  std::vector<Condition*> _iCondVec;
};

}  // namespace dbtrain_mysql

#endif