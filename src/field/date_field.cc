#include "date_field.h"

#include <cassert>
#include <cstring>

#include "utils/basic_function.h"

namespace dbtrain_mysql {

DateField::DateField(uint16_t year, uint8_t month, uint8_t day)
    : year(year), month(month), day(day) {}

void DateField::SetData(const uint8_t* src, Size nSize) {
  assert(nSize == 3);
  uint8_t buffer[3] = {0};
  memcpy(buffer, src, nSize);
  day = buffer[0] & 0b00011111;
  month = ((buffer[0] & 0b11100000) >> 4) | (buffer[1] & 0b00000001);
  year = ((uint16_t(buffer[1] & 0b11111110)) << 6) | (buffer[2] & 0b01111111);
}

void DateField::GetData(uint8_t* dst, Size nSize) const {
  assert(nSize == 3);
  uint8_t buffer[3] = {0};
  buffer[0] = (day & 0b00011111) | ((month << 4) & 0b11100000);
  buffer[1] = (month & 0b00000001) | ((year >> 6) & 0b11111110);
  buffer[2] = year & 0b01111111;
  memcpy(dst, buffer, nSize);
}

FieldType DateField::GetType() const { return FieldType::DATE_TYPE; }

Size DateField::GetSize() const { return 3; }

String DateField::ToString() const {
  char buffer[20];
  sprintf(buffer, "%04d-%02d-%02d", year, month, day);
  return String(buffer);
}

uint16_t DateField::GetYear() const { return year; }

uint8_t DateField::GetMonth() const { return month; }

uint8_t DateField::GetDay() const { return day; }

Field* DateField::Clone() const { return new DateField(year, month, day); }

void DateField::Add() {
  if (*this == DateField(10000, 1, 1)) return;
  ++day;
  if (!LeagalDate(year, month, day)) {
    day = 1;
    ++month;
    if (month >= 13) {
      month = 1;
      ++year;
    }
  }
}

void DateField::ToMax() {
  year = 10000;
  month = 1;
  day = 1;
}

void DateField::ToMin() {
  year = 1000;
  month = 1;
  day = 1;
}

uint32_t DateField::Hash() const {
  return ((uint32_t)year << 9) | ((uint32_t)month << 5) | (uint32_t)day;
}

bool DateField::operator==(const DateField& b) const {
  return year == b.year && month == b.month && day == b.day;
}

bool DateField::operator<(const DateField& b) const {
  if (year < b.year) return true;
  if (year > b.year) return false;
  if (month < b.month) return true;
  if (month > b.month) return false;
  return day < b.day;
}

bool DateField::operator<=(const DateField& b) const {
  if (year < b.year) return true;
  if (year > b.year) return false;
  if (month < b.month) return true;
  if (month > b.month) return false;
  return day <= b.day;
}

bool DateField::operator>(const DateField& b) const {
  if (year < b.year) return false;
  if (year > b.year) return true;
  if (month < b.month) return false;
  if (month > b.month) return true;
  return day > b.day;
}

bool DateField::operator>=(const DateField& b) const {
  if (year < b.year) return false;
  if (year > b.year) return true;
  if (month < b.month) return false;
  if (month > b.month) return true;
  return day >= b.day;
}

bool DateField::operator!=(const DateField& b) const {
  return year != b.year || month != b.month || day != b.day;
}

}  // namespace dbtrain_mysql