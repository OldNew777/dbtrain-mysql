#ifndef DBTRAIN_MYSQL_COLUMN_H
#define DBTRAIN_MYSQL_COLUMN_H

#include "defines.h"
#include "field/field.h"

namespace dbtrain_mysql {

class Column {
 public:
  // Column(const String& sName, FieldType iType, bool isNull);
  Column(const String& sName, FieldType iType, bool CanBeNull, 
    bool isPrimary, Size nSize,std::vector<std::pair<String, String> > sForeignVec);
  ~Column() = default;

  String GetName() const;
  FieldType GetType() const;
  Size GetSize() const;
  bool GetCanBeNull() const;
  bool GetIsPrimary() const;
  std::vector<std::pair<String, String> > GetForeignKeyVec() const;

 private:
  String _sName;
  FieldType _iType;
  Size _nSize;
  bool _canBeNull;
  bool _isPrimary;
  std::vector<std::pair<String, String> > _foreignKey; //@first: table name @second: column name
};

}  // namespace dbtrain_mysql

#endif