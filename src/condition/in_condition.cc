#include "in_condition.h"

#include "assert.h"

namespace dbtrain_mysql {

InCondition::InCondition(FieldID nPos, const std::vector<Field*>& iFieldVec)
    : RangeCondition(nPos), _iFieldVec(iFieldVec) {
  for (auto pField : iFieldVec) assert(pField != nullptr);
}

InCondition::~InCondition() {
  for (auto pField : _iFieldVec)
    if (pField) delete pField;
}

bool InCondition::Match(const Record& iRecord) const {
  Field* pField = iRecord.GetField(_nPos);
  for (auto pFieldTarget : _iFieldVec)
    if (Equal(pField, pFieldTarget)) return true;
  return false;
}

}  // namespace dbtrain_mysql