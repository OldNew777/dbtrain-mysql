#ifndef DBTRAIN_MYSQL_INDEX_CONDITION_H
#define DBTRAIN_MYSQL_INDEX_CONDITION_H

#include "condition/condition.h"
#include "field/fields.h"

namespace dbtrain_mysql {

class IndexCondition : public Condition {
 public:
  IndexCondition(const String &sTableName, const String &sColName, Field *pLow,
                 Field *pHigh);
  IndexCondition(const IndexCondition &t);
  ~IndexCondition();

  bool Match(const Record &iRecord) const override;
  ConditionType GetType() const override;

  std::pair<String, String> GetIndexName() const;
  std::pair<Field *, Field *> GetIndexRange() const;

 private:
  String _sTableName, _sColName;
  Field *_pLow, *_pHigh;
};

}  // namespace dbtrain_mysql

#endif
