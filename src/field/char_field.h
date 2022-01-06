#ifndef DBTRAIN_MYSQL_CHAR_FIELD_H
#define DBTRAIN_MYSQL_CHAR_FIELD_H

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

  virtual void SetData(const uint8_t* src, Size nSize) override;
  virtual void GetData(uint8_t* dst, Size nSize) const override;

  virtual FieldType GetType() const override;
  virtual Size GetSize() const override;

  virtual String ToString() const override;
  String GetString() const;

  virtual uint32_t Hash() const override;

  virtual Field* Clone() const override;
  virtual void Add() override;
  virtual void ToMax();
  virtual void ToMin();

  bool operator==(const CharField& b) const;
  bool operator<(const CharField& b) const;
  bool operator<=(const CharField& b) const;
  bool operator>(const CharField& b) const;
  bool operator>=(const CharField& b) const;
  bool operator!=(const CharField& b) const;

 private:
  String _charData;
  Size _len;
};

}  // namespace dbtrain_mysql

#endif  // DBTRAIN_MYSQL_CHAR_FIELD_H
