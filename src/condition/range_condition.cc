#include "condition/range_condition.h"

#include <cmath>

#include "exception/exceptions.h"
#include "field/fields.h"

namespace dbtrain_mysql {
RangeCondition::RangeCondition(FieldID nPos, Field* pLow, Field* pHigh)
    : _nPos(nPos), _pLow(pLow), _pHigh(pHigh) {}

bool RangeCondition::Match(const Record& iRecord) const {
  Field* pField = iRecord.GetField(_nPos);
  return LessEqual(_pLow, pField) && Greater(_pHigh, pField);
}

}  // namespace dbtrain_mysql
