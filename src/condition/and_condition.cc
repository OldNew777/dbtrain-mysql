#include "condition/and_condition.h"

namespace dbtrain_mysql {

AndCondition::AndCondition(const std::vector<Condition*>& iCondVec)
    : _iCondVec(iCondVec) {}

AndCondition::~AndCondition() {
  for (const auto& pCond : _iCondVec) delete pCond;
}

void AndCondition::PushBack(Condition* pCond) { _iCondVec.push_back(pCond); }

bool AndCondition::Match(const Record& iRecord) const {
  for (auto it = _iCondVec.begin(); it != _iCondVec.end(); ++it) {
    if (!(*it)->Match(iRecord)) return false;
  }
  return true;
}

}  // namespace dbtrain_mysql
