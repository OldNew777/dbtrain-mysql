#include "condition/all_condition.h"

namespace dbtrain_mysql {

AllCondition::AllCondition(){}

AllCondition::~AllCondition() {}

bool AllCondition::Match(const Record& iRecord) const {
  return true;
}

}  // namespace dbtrain_mysql
