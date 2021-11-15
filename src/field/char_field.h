#ifndef THDB_STRING_FIELD_H_
#define THDB_STRING_FIELD_H_

#include <cstring>
#include <string>

#include "field.h"

namespace dbtrain_mysql {

class VariableRecord;

class CharField : public Field {
 public:
  CharField();
  CharField(Size nSize);
  CharField(const String& charData);
  ~CharField() = default;
  void SetSize(Size nSize);

  void SetData(const uint8_t* src, Size nSize) override;
  void GetData(uint8_t* dst, Size nSize) const override;

  FieldType GetType() const override;
  Size GetSize() const override;

  String ToString() const override;
  String GetString() const;

  uint32_t Hash() const override;

  Field* Clone() const override;
  void Add() override;

  bool operator==(const CharField& b) const;
  bool operator<(const CharField& b) const;
  bool operator<=(const CharField& b) const;
  bool operator>(const CharField& b) const;
  bool operator>=(const CharField& b) const;
  bool operator!=(const CharField& b) const;

 private:
  String charData;
  Size len;
};

}  // namespace dbtrain_mysql

#endif  // THDB_STRING_FIELD_H_
