#ifndef DBTRAIN_MYSQL_CONDITION_H
#define DBTRAIN_MYSQL_CONDITION_H

#include "record/record.h"

namespace dbtrain_mysql {

enum class ConditionType {
  SIMPLE_TYPE = 0,
  JOIN_TYPE = 1,
  INDEX_TYPE = 2,
  NULL_TYPE = 3,
};

/**
 * @brief 条件检索的条件
 *
 */
class Condition {
 public:
  virtual ~Condition() = default;
  /**
   * @brief 判断记录是否符合当前条件
   *
   * @param iRecord 记录
   * @return true 符合
   * @return false 不符合
   */
  virtual bool Match(const Record& iRecord) const = 0;
  virtual ConditionType GetType() const;
};

}  // namespace dbtrain_mysql

#endif
