#ifndef DBTRAIN_MYSQL_JOIN_CONDITION_H
#define DBTRAIN_MYSQL_JOIN_CONDITION_H

#include "condition/condition.h"
#include "defines.h"

namespace dbtrain_mysql {

class JoinCondition : public Condition {
 public:
  JoinCondition(const String &sTableA, const String &sColA,
                const String &sTableB, const String &sColB);
  ~JoinCondition() = default;
  bool Match(const Record &iRecord) const override;
  ConditionType GetType() const override;
  String sTableA, sTableB;
  String sColA, sColB;
};

}  // namespace dbtrain_mysql

#endif