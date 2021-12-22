#include "condition/condition.h"

namespace dbtrain_mysql {

ConditionType Condition::GetType() const { return ConditionType::SIMPLE_TYPE; }

}  // namespace dbtrain_mysql
