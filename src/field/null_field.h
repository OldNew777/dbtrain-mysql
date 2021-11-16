#ifndef DBTRAIN_MYSQL_NULL_FIELD_H
#define DBTRAIN_MYSQL_NULL_FIELD_H

#include "field.h"

namespace dbtrain_mysql {

class NullField : public Field {
 public:
  NullField() = default;
  ~NullField() = default;

  virtual void SetData(const uint8_t* src, Size nSize) override;
  virtual void GetData(uint8_t* dst, Size nSize) const override;

  virtual FieldType GetType() const override;
  virtual Size GetSize() const override;

  virtual String ToString() const override;

  virtual uint32_t Hash() const override;

  virtual Field* Clone() const override;
  virtual void Add() override;
};

}  // namespace dbtrain_mysql

#endif  // DBTRAIN_MYSQL_NULL_FIELD_H
