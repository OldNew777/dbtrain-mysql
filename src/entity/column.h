#ifndef DBTRAIN_MYSQL_COLUMN_H
#define DBTRAIN_MYSQL_COLUMN_H

#include "defines.h"
#include "field/field.h"

namespace dbtrain_mysql {

class Column {
 public:
  // Column(const String& sName, FieldType iType, bool isNull);
  Column(const String& sName, FieldType iType, bool CanBeNull, const Size& nSize, bool isPrimary);
  Column(const std::vector<std::vector<String> >& sPKVec, 
    const std::vector<String>& sPKNameVec,
    const std::vector<std::vector<std::vector<String> > >& sFKVec,
    const std::vector<String>& sFKNameVec
  );

  ~Column() = default;

  String GetName() const;
  FieldType GetType() const;
  Size GetSize() const;
  bool GetCanBeNull() const;
  bool GetIsPrimary() const;
  std::vector<String> GetPKNameVec() const;
  std::vector<String> GetFKNameVec() const;
  std::vector<std::vector<String> > GetPKVec() const;
  std::vector<std::vector<std::vector<String> > > GetFKVec() const;
  void Show() const;

 private:
  String _sName = "";
  FieldType _iType;
  Size _nSize;
  bool _CanBeNull;
  bool _IsPrimary;

  std::vector<String> _sPKNameVec;
  std::vector<String> _sFKNameVec;
  std::vector<std::vector<String> > _PKVec;
  std::vector<std::vector<std::vector<String> > > _FKVec; //@first: table name @second: column name
};

}  // namespace dbtrain_mysql

#endif