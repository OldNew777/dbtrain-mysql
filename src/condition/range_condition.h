#ifndef DBTRAIN_MYSQL_RANGE_CONDITION_H
#define DBTRAIN_MYSQL_RANGE_CONDITION_H

#include <float.h>

#include "condition/condition.h"
#include "defines.h"

namespace dbtrain_mysql {

/**
 * @brief 范围检索的条件
 *
 */
class RangeCondition : public Condition {
 public:
  RangeCondition(FieldID nPos, const double& fMin, const double& fMax);
  ~RangeCondition() = default;
  bool Match(const Record& iRecord) const override;

 private:
  uint32_t _nPos = 0xFFFF;
  double _fMin = DBL_MIN, _fMax = DBL_MAX;
};

}  // namespace dbtrain_mysql

#endif