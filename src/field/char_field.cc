#include "char_field.h"

#include "macros.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

CharField::CharField() : _len(0) { _charData = String("\0", 0); }

CharField::CharField(Size nSize) : _len(nSize) {
  _charData = String("\0", nSize);
}

CharField::CharField(const String& charData) : _charData(charData) {
  _len = charData.length();
}

void CharField::SetSize(Size nSize) {
  _len = nSize;
  _charData = String("\0", nSize);
}

void CharField::SetData(const uint8_t* src, Size nSize) {
  char* _pData = new char[nSize + 1];
  _pData[nSize] = '\0';
  memcpy(_pData, src, nSize);
  _charData = String(_pData);
  _len = nSize;
  delete[] _pData;
}

void CharField::GetData(uint8_t* dst, Size nSize) const {
  memset(dst, 0, nSize);
  memcpy(dst, _charData.c_str(),
         (nSize <= _charData.size()) ? nSize : _charData.size());
}

FieldType CharField::GetType() const { return FieldType::CHAR_TYPE; }

Size CharField::GetSize() const { return _len; }

void CharField::Add() { _charData = stringNext(_charData); }

void CharField::ToMax() { _charData = String(FIELD_SIZE_MAX, 127); }

void CharField::ToMin() { _charData = String(""); }

String CharField::ToString() const { return _charData; }

String CharField::GetString() const { return _charData; }

Field* CharField::Clone() const { return new CharField(_charData); }

uint32_t CharField::Hash() const {
  uint32_t hash = _len;
  for (Size i = 0; i < _charData.length(); ++i)
    hash = (((hash << 3) | (hash >> 29)) ^ uint32_t(_charData[i]));
  return hash;
}

bool CharField::operator==(const CharField& b) const {
  return this->_charData == b._charData;
}

bool CharField::operator<(const CharField& b) const {
  return this->_charData < b._charData;
}

bool CharField::operator<=(const CharField& b) const {
  return this->_charData <= b._charData;
}

bool CharField::operator>(const CharField& b) const {
  return this->_charData > b._charData;
}

bool CharField::operator>=(const CharField& b) const {
  return this->_charData >= b._charData;
}

bool CharField::operator!=(const CharField& b) const {
  return this->_charData != b._charData;
}

}  // namespace dbtrain_mysql
