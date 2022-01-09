#include "column.h"

#include "exception/exceptions.h"

namespace dbtrain_mysql {

Column::Column(const String& sName, FieldType iType,
 bool canBeNull, bool isPrimary, Size nSize,
 std::vector<std::vector<String> > sForeignVec)
    : _sName(sName), _iType(iType), _canBeNull(canBeNull), _nSize(nSize),
     _isPrimary(isPrimary){
   for(auto& vec: sForeignVec){
      _constraintName.push_back(vec[0]);
      _foreignKey.push_back(std::make_pair(vec[1], vec[2]));
   }
}

String Column::GetName() const { return _sName; }

FieldType Column::GetType() const { return _iType; }

Size Column::GetSize() const { return _nSize; }

bool Column::GetCanBeNull() const {return _canBeNull || !_isPrimary;}

bool Column::GetIsPrimary() const {return _isPrimary;}
std::vector<std::pair<String, String> > Column::GetForeignKeyVec() const{
   return _foreignKey;
}
String Column::GetConstraintName(int pos) const{
   return _constraintName[pos];
}
}  // namespace dbtrain_mysql
