#ifndef DBTRAIN_MYSQL_RANGE_CONDITION_H
#define DBTRAIN_MYSQL_RANGE_CONDITION_H

#include "condition/condition.h"
#include "defines.h"
#include "field/fields.h"

namespace dbtrain_mysql {

/**
 * @brief 范围检索的条件
 *
 */
class RangeCondition : public Condition {
 public:
  RangeCondition(FieldID nPos);
  RangeCondition(FieldID nPos, Field *pLow, Field *pHigh);
  ~RangeCondition();
  virtual bool Match(const Record &iRecord) const override;

 protected:
  uint32_t _nPos = 0xFFFF;

 private:
  Field *_pLow, *_pHigh;
};

}  // namespace dbtrain_mysql

#endif