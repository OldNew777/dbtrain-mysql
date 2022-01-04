#ifndef DBTRAIN_MYSQL_COLUMN_H
#define DBTRAIN_MYSQL_COLUMN_H

#include "defines.h"
#include "field/field.h"

namespace dbtrain_mysql {

class Column {
 public:
  Column(const String& sName, FieldType iType, bool isNull);
  Column(const String& sName, FieldType iType, Size nSize, bool isNull);
  ~Column() = default;

  String GetName() const;
  FieldType GetType() const;
  Size GetSize() const;
  bool GetIsNull() const;

 private:
  String _sName;
  FieldType _iType;
  Size _nSize;
  bool _isNull;
};

}  // namespace dbtrain_mysql

#endif