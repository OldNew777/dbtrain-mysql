#include "null_field.h"

#include <cassert>

namespace dbtrain_mysql {

void NullField::SetData(const uint8_t* src, Size nSize) { assert(nSize == 0); }

void NullField::GetData(uint8_t* dst, Size nSize) const { assert(nSize == 0); }

FieldType NullField::GetType() const { return FieldType::NULL_TYPE; }

Size NullField::GetSize() const { return 0; }

String NullField::ToString() const { return "NULL"; }

Field* NullField::Clone() const { return new NullField(); }

void NullField::Add() {}

uint32_t NullField::Hash() const { return 0; }

}  // namespace dbtrain_mysql
