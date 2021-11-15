#include "field/field.h"

namespace dbtrain_mysql {

void Field::SetNull(bool isNull) { this->isNull = isNull; }
bool Field::Null() const { return isNull; }

String toString(FieldType iType) {
  if (iType == FieldType::INT_TYPE) {
    return "INT";
  } else if (iType == FieldType::FLOAT_TYPE) {
    return "FLOAT";
  } else if (iType == FieldType::CHAR_TYPE) {
    return "CHAR";
  } else if (iType == FieldType::NULL_TYPE) {
    return "NULL";
  } else {
    return "Error";
  }
}

}  // namespace dbtrain_mysql
