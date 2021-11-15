#ifndef DBTRAIN_MYSQL_INT_FIELD_H_
#define DBTRAIN_MYSQL_INT_FIELD_H_

#include "field.h"

namespace dbtrain_mysql {

class IntField : public Field {
 public:
  IntField() = default;
  IntField(const int& dataInt);
  ~IntField() = default;

  void SetData(const uint8_t* src, Size nSize) override;
  void GetData(uint8_t* dst, Size nSize) const override;

  FieldType GetType() const override;
  Size GetSize() const override;

  int GetIntData() const;
  std::string ToString() const override;

  uint32_t Hash() const override;

  Field* Clone() const override;

  void Add() override;

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

#endif  // DBTRAIN_MYSQL_INT_FIELD_H_
