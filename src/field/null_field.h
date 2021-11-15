#ifndef DBTRAIN_MYSQL_NULL_FIELD_H_
#define DBTRAIN_MYSQL_NULL_FIELD_H_

#include "field.h"

namespace dbtrain_mysql {

class NullField : public Field {
 public:
  NullField() = default;
  ~NullField() = default;

  void SetData(const uint8_t* src, Size nSize) override;
  void GetData(uint8_t* dst, Size nSize) const override;

  FieldType GetType() const override;
  Size GetSize() const override;

  String ToString() const override;

  uint32_t Hash() const override;

  Field* Clone() const override;
  void Add() override;
};

}  // namespace dbtrain_mysql

#endif  // DBTRAIN_MYSQL_NULL_FIELD_H_
