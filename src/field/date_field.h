#ifndef DBTRAIN_MYSQL_DATE_FIELD_H
#define DBTRAIN_MYSQL_DATE_FIELD_H

#include "field.h"

namespace dbtrain_mysql {

class DateField : public Field {
 public:
  DateField() = default;
  DateField(uint16_t year, uint8_t month, uint8_t day);
  ~DateField() = default;

  virtual void SetData(const uint8_t* src, Size nSize) override;
  virtual void GetData(uint8_t* dst, Size nSize) const override;

  virtual FieldType GetType() const override;
  virtual Size GetSize() const override;

  uint16_t GetYear() const;
  uint8_t GetMonth() const;
  uint8_t GetDay() const;
  virtual std::string ToString() const override;

  virtual uint32_t Hash() const override;

  virtual Field* Clone() const override;

  virtual void Add() override;
  virtual void ToMax();
  virtual void ToMin();

  bool operator==(const DateField& b) const;
  bool operator<(const DateField& b) const;
  bool operator<=(const DateField& b) const;
  bool operator>(const DateField& b) const;
  bool operator>=(const DateField& b) const;
  bool operator!=(const DateField& b) const;

 private:
  uint16_t year;
  uint8_t month, day;
};

}  // namespace dbtrain_mysql

#endif  // DBTRAIN_MYSQL_INT_FIELD_H
