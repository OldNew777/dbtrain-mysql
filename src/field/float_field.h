#ifndef DBTRAIN_MYSQL_FLOAT_FIELD_H_
#define DBTRAIN_MYSQL_FLOAT_FIELD_H_

#include "field.h"

namespace dbtrain_mysql {

class FloatField : public Field {
 public:
  FloatField() = default;
  FloatField(const float& floatData);
  ~FloatField() = default;

  void SetData(const uint8_t* src, Size nSize) override;
  void GetData(uint8_t* dst, Size nSize) const override;

  FieldType GetType() const override;
  Size GetSize() const override;

  float GetFloatData() const;
  String ToString() const override;

  uint32_t Hash() const override;

  Field* Clone() const override;
  void Add() override;

  /**
   * @brief equal function. should consider again between Add() and precisely
   * equal
   */
  bool operator==(const FloatField& b) const;
  bool operator<(const FloatField& b) const;
  bool operator<=(const FloatField& b) const;
  bool operator>(const FloatField& b) const;
  bool operator>=(const FloatField& b) const;
  bool operator!=(const FloatField& b) const;

 private:
  float floatData;
};

}  // namespace dbtrain_mysql

#endif  // DBTRAIN_MYSQL_FLOAT_FIELD_H_
