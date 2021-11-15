#include "int_field.h"

#include <cassert>
#include <cstring>

namespace dbtrain_mysql {

IntField::IntField(const int& dataInt) : dataInt(dataInt) {}

void IntField::SetData(const uint8_t* src, Size nSize) {
  assert(nSize == 4);
  memcpy((uint8_t*)&dataInt, src, nSize);
}

void IntField::GetData(uint8_t* dst, Size nSize) const {
  assert(nSize == 4);
  memcpy(dst, (uint8_t*)&dataInt, nSize);
}

FieldType IntField::GetType() const { return FieldType::INT_TYPE; }

Size IntField::GetSize() const { return 4; }

String IntField::ToString() const { return std::to_string(dataInt); }

int IntField::GetIntData() const { return dataInt; }

Field* IntField::Clone() const { return new IntField(dataInt); }

void IntField::Add() {
  // TODO : how to deal with INT32_MAX?
  if (dataInt != INT32_MAX) dataInt += 1;
}

uint32_t IntField::Hash() const { return dataInt; }

bool IntField::operator==(const IntField& b) const {
  return this->dataInt == b.dataInt;
}

bool IntField::operator<(const IntField& b) const {
  return this->dataInt < b.dataInt;
}

bool IntField::operator<=(const IntField& b) const {
  return this->dataInt <= b.dataInt;
}

bool IntField::operator>(const IntField& b) const {
  return this->dataInt > b.dataInt;
}

bool IntField::operator>=(const IntField& b) const {
  return this->dataInt >= b.dataInt;
}

bool IntField::operator!=(const IntField& b) const {
  return this->dataInt != b.dataInt;
}

}  // namespace dbtrain_mysql
