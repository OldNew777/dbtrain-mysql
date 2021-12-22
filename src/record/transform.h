#ifndef DBTRAIN_MYSQL_TRANSFORM_H
#define DBTRAIN_MYSQL_TRANSFORM_H

#include "defines.h"
#include "field/fields.h"

namespace dbtrain_mysql {

class Transform {
 public:
  Transform(FieldID nFieldID, FieldType iType, const String& sRaw);
  ~Transform() = default;

  Field* GetField() const;
  FieldID GetPos() const;

 private:
  FieldID _nFieldID;
  FieldType _iType;
  String _sRaw;
};

}  // namespace dbtrain_mysql

#endif