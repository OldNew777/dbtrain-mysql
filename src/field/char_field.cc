#include "char_field.h"

namespace dbtrain_mysql {

CharField::CharField() : len(0) { charData = String("\0", 0); }

CharField::CharField(Size nSize) : len(nSize) {
  charData = String("\0", nSize);
}

CharField::CharField(const String& charData) : charData(charData) {
  len = charData.length();
}

void CharField::SetSize(Size nSize) {
  len = nSize;
  charData = String("\0", nSize);
}

void CharField::SetData(const uint8_t* src, Size nSize) {
  char* _pData = new char[nSize + 1];
  _pData[nSize] = '\0';
  memcpy(_pData, src, nSize);
  charData = String(_pData);
  len = nSize;
  delete[] _pData;
}

void CharField::GetData(uint8_t* dst, Size nSize) const {
  memset(dst, 0, nSize);
  memcpy(dst, charData.c_str(),
         (nSize <= charData.size()) ? nSize : charData.size());
}

FieldType CharField::GetType() const { return FieldType::CHAR_TYPE; }

Size CharField::GetSize() const { return len; }

void CharField::Add() {
  if (charData.length() == 0 || charData[charData.length() - 1] >= 126)
    charData += ' ';
  else
    charData[charData.length() - 1] += 1;
}

String CharField::ToString() const { return charData; }

String CharField::GetString() const { return charData; }

Field* CharField::Clone() const { return new CharField(charData); }

uint32_t CharField::Hash() const {
  uint32_t hash = len;
  for (Size i = 0; i < charData.length(); ++i)
    hash = (((hash << 3) | (hash >> 29)) ^ uint32_t(charData[i]));
  return hash;
}

bool CharField::operator==(const CharField& b) const {
  return this->charData == b.charData;
}

bool CharField::operator<(const CharField& b) const {
  return this->charData < b.charData;
}

bool CharField::operator<=(const CharField& b) const {
  return this->charData <= b.charData;
}

bool CharField::operator>(const CharField& b) const {
  return this->charData > b.charData;
}

bool CharField::operator>=(const CharField& b) const {
  return this->charData >= b.charData;
}

bool CharField::operator!=(const CharField& b) const {
  return this->charData != b.charData;
}

}  // namespace dbtrain_mysql
