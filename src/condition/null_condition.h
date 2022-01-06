#ifndef DBTRAIN_MYSQL_NULL_CONDITION_H
#define DBTRAIN_MYSQL_NULL_CONDITION_H

#include "condition/condition.h"
#include "defines.h"
#include "field/fields.h"

namespace dbtrain_mysql {

/**
 * @brief Null检索的条件
 *
 */
class NullCondition : public Condition {
 public:
  NullCondition(FieldID nPos);
  NullCondition(FieldID nPos, bool bIsNull);
  ~NullCondition() = default;
  virtual bool Match(const Record &iRecord) const override;

  ConditionType GetType() const override;

 protected:
  uint32_t _nPos = 0xFFFF;
  bool _bIsNull;
};

}  // namespace dbtrain_mysql

#endif