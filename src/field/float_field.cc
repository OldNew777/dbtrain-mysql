#include "float_field.h"

#include <cassert>
#include <cmath>
#include <cstring>
#include <sstream>

namespace dbtrain_mysql {

FloatField::FloatField(const float& floatData) : floatData(floatData) {}

void FloatField::SetData(const uint8_t* src, Size nSize) {
  assert(nSize == 8);
  memcpy((uint8_t*)&floatData, src, nSize);
}

void FloatField::GetData(uint8_t* dst, Size nSize) const {
  assert(nSize == 8);
  memcpy(dst, (uint8_t*)&floatData, nSize);
}

FieldType FloatField::GetType() const { return FieldType::FLOAT_TYPE; }

Size FloatField::GetSize() const { return 4; }

String FloatField::ToString() const {
  std::ostringstream strs;
  strs << floatData;
  return strs.str();
}

float FloatField::GetFloatData() const { return floatData; }

Field* FloatField::Clone() const { return new FloatField(floatData); }

void FloatField::Add() {
  // TODO : whether should here divided by 2?
  if (fabs(floatData) < __FLT_MIN__ / __FLT_EPSILON__)
    floatData += __FLT_MIN__;
  else
    floatData += fabs(floatData) * __FLT_EPSILON__;
}

uint32_t FloatField::Hash() const { return *(uint32_t*)(&floatData); }

bool FloatField::operator==(const FloatField& b) const {
  // TODO : balance between Add() and precisely equal function
  return this->floatData == b.floatData;
}

bool FloatField::operator<(const FloatField& b) const {
  return this->floatData < b.floatData;
}

bool FloatField::operator<=(const FloatField& b) const {
  return this->floatData <= b.floatData;
}

bool FloatField::operator>(const FloatField& b) const {
  return this->floatData > b.floatData;
}

bool FloatField::operator>=(const FloatField& b) const {
  return this->floatData >= b.floatData;
}

bool FloatField::operator!=(const FloatField& b) const {
  return this->floatData != b.floatData;
}

}  // namespace dbtrain_mysql
