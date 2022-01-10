#include "column.h"

#include "exception/exceptions.h"

namespace dbtrain_mysql {

Column::Column(const String& sName, FieldType iType, bool canBeNull,
               bool isPrimary, Size nSize,
               std::vector<std::pair<String, String> > sForeignVec)
    : _sName(sName),
      _iType(iType),
      _canBeNull(canBeNull),
      _nSize(nSize),
      _isPrimary(isPrimary),
      _foreignKey(sForeignVec) {}

String Column::GetName() const { return _sName; }

FieldType Column::GetType() const { return _iType; }

Size Column::GetSize() const { return _nSize; }

bool Column::GetCanBeNull() const { return _canBeNull; }

bool Column::GetIsPrimary() const { return _isPrimary; }
std::vector<std::pair<String, String> > Column::GetForeignKeyVec() const {
  return _foreignKey;
}

}  // namespace dbtrain_mysql