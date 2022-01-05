#include "float_field.h"

#include <cassert>
#include <cmath>
#include <cstring>
#include <sstream>

#include "utils/basic_function.h"

namespace dbtrain_mysql {

FloatField::FloatField(const float& floatData) : floatData(floatData) {}

void FloatField::SetData(const uint8_t* src, Size nSize) {
  assert(nSize == 4);
  memcpy((uint8_t*)&floatData, src, nSize);
}

void FloatField::GetData(uint8_t* dst, Size nSize) const {
  assert(nSize == 4);
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

void FloatField::Add() { floatData = floatNext(floatData); }

void FloatField::ToMax() { floatData = __FLT_MAX__; }

void FloatField::ToMin() { floatData = -__FLT_MAX__; }

uint32_t FloatField::Hash() const { return *(uint32_t*)(&floatData); }

bool FloatField::operator==(const FloatField& b) const {
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
