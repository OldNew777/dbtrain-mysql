#ifndef DBTRAIN_MYSQL_IN_CONDITION_H
#define DBTRAIN_MYSQL_IN_CONDITION_H

#include <vector>

#include "condition/condition.h"
#include "defines.h"
#include "field/fields.h"

namespace dbtrain_mysql {

/**
 * @brief In检索的条件
 *
 */
class InCondition : public Condition {
 public:
  InCondition(FieldID nPos, const std::vector<Field *> &iFieldVec);
  InCondition(const InCondition &t);
  ~InCondition();
  virtual bool Match(const Record &iRecord) const override;

 protected:
  FieldID _nPos;
  std::vector<Field *> _iFieldVec;
};

}  // namespace dbtrain_mysql

#endif