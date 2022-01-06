#include "null_condition.h"

namespace dbtrain_mysql {

NullCondition::NullCondition(FieldID nPos, bool bIsNull)
    : _nPos(nPos), _bIsNull(bIsNull) {}

bool NullCondition::Match(const Record &iRecord) const {
  return (iRecord.GetField(_nPos)->GetType() == FieldType::NULL_TYPE &&
          _bIsNull) ||
         (iRecord.GetField(_nPos)->GetType() != FieldType::NULL_TYPE &&
          !_bIsNull);
}

ConditionType NullCondition::GetType() const {
  return ConditionType::NULL_TYPE;
}

}  // namespace dbtrain_mysql