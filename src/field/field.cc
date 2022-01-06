#include "field/field.h"

#include "exception/exception.h"

namespace dbtrain_mysql {

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
    case FieldType::DATE_TYPE:
      return "DATE";
    default:
      return "Error";
  }

  auto e = Exception("Type error");
  std::cout << e.what() << "\n";
  throw e;
}

}  // namespace dbtrain_mysql
