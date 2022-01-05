#include "condition/index_condition.h"

#include <assert.h>
#include <math.h>

namespace dbtrain_mysql {

IndexCondition::IndexCondition(const String &sTableName, const String &sColName,
                               Field *pLow, Field *pHigh)
    : _sTableName(sTableName), _sColName(sColName), _pLow(pLow), _pHigh(pHigh) {
  assert(pLow != nullptr);
  assert(pHigh != nullptr);
}

IndexCondition::~IndexCondition() {
  delete _pLow;
  delete _pHigh;
}

bool IndexCondition::Match(const Record &iRecord) const { return true; }

ConditionType IndexCondition::GetType() const {
  return ConditionType::INDEX_TYPE;
}

std::pair<String, String> IndexCondition::GetIndexName() const {
  return {_sTableName, _sColName};
}

std::pair<Field *, Field *> IndexCondition::GetIndexRange() const {
  return {_pLow, _pHigh};
}

}  // namespace dbtrain_mysql
