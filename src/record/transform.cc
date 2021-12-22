#include "record/transform.h"

#include "exception/exceptions.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

Transform::Transform(FieldID nFieldID, FieldType iType, const String& sRaw)
    : _nFieldID(nFieldID), _iType(iType), _sRaw(sRaw) {}

FieldID Transform::GetPos() const { return _nFieldID; }

Field* Transform::GetField() const {
  Field* pField = nullptr;
  if (toUpper(_sRaw) == "NULL") {
    pField = new NullField();
  } else if (_iType == FieldType::INT_TYPE) {
    pField = new IntField(std::stoi(_sRaw));
  } else if (_iType == FieldType::FLOAT_TYPE) {
    pField = new FloatField(std::stod(_sRaw));
  } else if (_iType == FieldType::CHAR_TYPE) {
    pField = new CharField(_sRaw.substr(1, _sRaw.size() - 2));
  } else {
    throw Exception();
  }
  return pField;
}

}  // namespace dbtrain_mysql
