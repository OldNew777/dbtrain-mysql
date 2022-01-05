#include "record/transform.h"

#include "assert.h"
#include "exception/exceptions.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

Transform::Transform(FieldID nFieldID, FieldType iType, Field* pField)
    : _nFieldID(nFieldID), _pField(pField) {
  assert(iType == pField->GetType() ||
         pField->GetType() == FieldType::NULL_TYPE);
}

Transform::Transform(const Transform& t) {
  _nFieldID = t._nFieldID;
  _pField = t._pField->Clone();
}

Transform::~Transform() {
  if (_pField) delete _pField;
}

FieldID Transform::GetColPos() const { return _nFieldID; }

Field* Transform::GetField() const { return _pField->Clone(); }

}  // namespace dbtrain_mysql
