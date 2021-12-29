#ifndef DBTRAIN_MYSQL_SCHEMA_H
#define DBTRAIN_MYSQL_SCHEMA_H

#include "defines.h"
#include "entity/column.h"

namespace dbtrain_mysql {

class Schema {
 public:
  Schema(const std::vector<Column>& iColVec);
  ~Schema() = default;

  Size GetSize() const;
  Column GetColumn(Size nPos) const;

 private:
  std::vector<Column> _iColVec;
};

}  // namespace dbtrain_mysql

#endif