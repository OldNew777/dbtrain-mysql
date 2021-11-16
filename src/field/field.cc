#include "field/field.h"

#include "exception/exception.h"

namespace dbtrain_mysql {

void Field::SetNull(bool isNull) { this->isNull = isNull; }
bool Field::Null() const { return isNull; }

String toString(FieldType iType) {
  switch (iType) {
    case FieldType::NULL_TYPE:
      return "NULL";
    case FieldType::INT_TYPE:
      return "INT";
    case FieldType::FLOAT_TYPE:
      return "FLOAT";
    case FieldType::CHAR_TYPE:
      return "CHAR";
    default:
      return "Error";
  }

  throw Exception();
}

}  // namespace dbtrain_mysql
