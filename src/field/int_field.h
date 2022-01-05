#ifndef DBTRAIN_MYSQL_INT_FIELD_H
#define DBTRAIN_MYSQL_INT_FIELD_H

#include "field.h"

namespace dbtrain_mysql {

class IntField : public Field {
 public:
  IntField() = default;
  IntField(const int& dataInt);
  ~IntField() = default;

  virtual void SetData(const uint8_t* src, Size nSize) override;
  virtual void GetData(uint8_t* dst, Size nSize) const override;

  virtual FieldType GetType() const override;
  virtual Size GetSize() const override;

  int GetIntData() const;
  virtual std::string ToString() const override;

  virtual uint32_t Hash() const override;

  virtual Field* Clone() const override;

  virtual void Add() override;
  virtual void ToMax();
  virtual void ToMin();

  bool operator==(const IntField& b) const;
  bool operator<(const IntField& b) const;
  bool operator<=(const IntField& b) const;
  bool operator>(const IntField& b) const;
  bool operator>=(const IntField& b) const;
  bool operator!=(const IntField& b) const;

 private:
  int dataInt;
};

}  // namespace dbtrain_mysql

#endif  // DBTRAIN_MYSQL_INT_FIELD_H
