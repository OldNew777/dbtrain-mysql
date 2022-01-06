#include "condition/range_condition.h"

#include "assert.h"

namespace dbtrain_mysql {

RangeCondition::RangeCondition(FieldID nPos, Field* pLow, Field* pHigh)
    : _nPos(nPos), _pLow(pLow), _pHigh(pHigh) {
  assert(pLow != nullptr);
  assert(pHigh != nullptr);
}

RangeCondition::RangeCondition(const RangeCondition& t) {
  _nPos = t._nPos;
  _pLow = t._pLow->Clone();
  _pHigh = t._pHigh->Clone();
}

RangeCondition::~RangeCondition() {
  if (_pLow) delete _pLow;
  if (_pHigh) delete _pHigh;
}

bool RangeCondition::Match(const Record& iRecord) const {
  Field* pField = iRecord.GetField(_nPos);
  return LessEqual(_pLow, pField) && Greater(_pHigh, pField);
}

}  // namespace dbtrain_mysql
