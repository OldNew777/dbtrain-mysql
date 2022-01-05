#ifndef DBTRAIN_MYSQL_TRANSFORM_H
#define DBTRAIN_MYSQL_TRANSFORM_H

#include "defines.h"
#include "field/fields.h"

namespace dbtrain_mysql {

class Transform {
 public:
  Transform(FieldID nFieldID, FieldType iType, Field* pField);
  Transform(const Transform& t);
  ~Transform();

  Field* GetField() const;
  FieldID GetColPos() const;

 private:
  FieldID _nFieldID;
  Field* _pField;
};

}  // namespace dbtrain_mysql

#endif