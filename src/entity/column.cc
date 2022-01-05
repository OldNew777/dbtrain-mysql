#include "column.h"

#include "exception/exceptions.h"

namespace dbtrain_mysql {

Column::Column(const String& sName, FieldType iType, bool isNull, bool isPrimary, Size nSize)
    : _sName(sName), _iType(iType), _isNull(isNull), _nSize(nSize), _isPrimary(isPrimary){
  // switch (iType) {
  //   case FieldType::NULL_TYPE:
  //     _nSize = 0;
  //     break;
  //   case FieldType::INT_TYPE:
  //     _nSize = 4;
  //     break;
  //   case FieldType::FLOAT_TYPE:
  //     _nSize = 4;
  //     break;
  //   case FieldType::CHAR_TYPE:
  //     _nSize = nSize;
  //     break;
  //   default:
  //     throw RecordTypeException("Column type error");
  //     break;
  // }
}

String Column::GetName() const { return _sName; }

FieldType Column::GetType() const { return _iType; }

Size Column::GetSize() const { return _nSize; }

bool Column::GetIsNull() const {return _isNull;}

bool Column::GetIsPrimary() const {return _isPrimary;}

}  // namespace dbtrain_mysql
