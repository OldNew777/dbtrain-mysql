#ifndef DBTRAIN_MYSQL_FLOAT_FIELD_H
#define DBTRAIN_MYSQL_FLOAT_FIELD_H

#include "field.h"

namespace dbtrain_mysql {

class FloatField : public Field {
 public:
  FloatField() = default;
  FloatField(const float& floatData);
  ~FloatField() = default;

  virtual void SetData(const uint8_t* src, Size nSize) override;
  virtual void GetData(uint8_t* dst, Size nSize) const override;

  virtual FieldType GetType() const override;
  virtual Size GetSize() const override;

  virtual float GetFloatData() const;
  virtual String ToString() const override;

  virtual uint32_t Hash() const override;

  virtual Field* Clone() const override;
  virtual void Add() override;

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

#endif  // DBTRAIN_MYSQL_FLOAT_FIELD_H
