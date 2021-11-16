#ifndef DBTRAIN_MYSQL_FIELD_H
#define DBTRAIN_MYSQL_FIELD_H

#include "defines.h"

namespace dbtrain_mysql {

enum class FieldType {
  NULL_TYPE = 0,
  INT_TYPE = 1,
  CHAR_TYPE = 2,
  FLOAT_TYPE = 3,
};

class Field {
 public:
  virtual void SetData(const uint8_t* src, Size nSize) = 0;
  virtual void GetData(uint8_t* dst, Size nSize) const = 0;

  virtual FieldType GetType() const = 0;
  virtual Size GetSize() const = 0;
  void SetNull(bool isNull);
  bool Null() const;

  virtual String ToString() const = 0;

  virtual uint32_t Hash() const = 0;

  virtual Field* Clone() const = 0;
  /**
   * @brief add a small value to get the precise "next"
   */
  virtual void Add() = 0;

  virtual ~Field() = default;

 private:
  bool isNull = false;
};

String toString(FieldType iType);

}  // namespace dbtrain_mysql

#endif  // DBTRAIN_MYSQL_FIELD_H
