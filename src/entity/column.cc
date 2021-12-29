#include "column.h"

#include "exception/exceptions.h"

namespace dbtrain_mysql {

Column::Column(const String& sName, FieldType iType)
    : _sName(sName), _iType(iType) {
  switch (iType) {
    case FieldType::NULL_TYPE:
      _nSize = 0;
      break;
    case FieldType::INT_TYPE:
      _nSize = 4;
      break;
    case FieldType::FLOAT_TYPE:
      _nSize = 4;
      break;
    default:
      throw RecordTypeException("Column type error");
      break;
  }
}

Column::Column(const String& sName, FieldType iType, Size nSize)
    : _sName(sName), _iType(iType), _nSize(nSize) {}

String Column::GetName() const { return _sName; }

FieldType Column::GetType() const { return _iType; }

Size Column::GetSize() const { return _nSize; }

}  // namespace dbtrain_mysql
