#include "column.h"

#include "exception/exceptions.h"

namespace dbtrain_mysql {

Column::Column(const String& sName, FieldType iType, bool isNull)
    : _sName(sName), _iType(iType), _isNull(isNull) {
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

Column::Column(const String& sName, FieldType iType, Size nSize, bool isNull)
    : _sName(sName), _iType(iType), _nSize(nSize),_isNull(isNull) {}

String Column::GetName() const { return _sName; }

FieldType Column::GetType() const { return _iType; }

Size Column::GetSize() const { return _nSize; }

bool Column::GetIsNull() const {return _isNull;}

}  // namespace dbtrain_mysql
