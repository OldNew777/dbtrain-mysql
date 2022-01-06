#include "record/record.h"

#include <assert.h>

#include <cstring>

#include "exception/exceptions.h"
#include "utils/bitmap.h"

namespace dbtrain_mysql {

Record::Record() {}

Record::Record(Size nFieldSize) { _iFields.resize(nFieldSize, nullptr); }

Record::~Record() { Clear(); }

Field* Record::GetField(FieldID nPos) const { return _iFields[nPos]; }

void Record::SetField(FieldID nPos, Field* pField) {
  if (_iFields[nPos]) delete _iFields[nPos];
  _iFields[nPos] = pField;
}

Size Record::GetSize() const { return _iFields.size(); }

void Record::Clear() {
  for (const auto& pField : _iFields)
    if (pField) delete pField;
  for (int i = 0; i < _iFields.size(); ++i) _iFields[i] = nullptr;
}

void Record::Sub(const std::vector<Size>& iPos) {
  Bitmap bInSub(GetSize());
  for (const auto nPos : iPos) bInSub.Set(nPos);
  auto itField = _iFields.begin();
  auto nSize = GetSize();
  for (Size i = 0; i < nSize; ++i) {
    if (!bInSub.Get(i)) {
      Field* pField = *itField;
      if (pField) delete pField;
      itField = _iFields.erase(itField);
    } else {
      ++itField;
    }
  }
}

void Record::Add(Record* pRecord) {
  for (Size i = 0; i < pRecord->GetSize(); ++i) {
    _iFields.push_back(pRecord->GetField(i)->Clone());
  }
}

void Record::Remove(FieldID nPos) {
  assert(nPos < GetSize());
  auto it = _iFields.begin() + nPos;
  if (*it) delete (*it);
  _iFields.erase(it);
}

String Record::ToString() {
  String result;
  for (const auto& pField : _iFields) {
    if (pField) {
      result += pField->ToString() + " ";
    } else {
      auto e = NullptrException("Record::ToString()", "Record field nullptr");
      std::cout << e.what() << "\n";
      throw e;
    }
  }
  return result;
}

uint32_t Record::Hash(Size fieldIndex) const {
  assert(fieldIndex < _iFields.size());
  return _iFields[fieldIndex]->Hash();
};

}  // namespace dbtrain_mysql
