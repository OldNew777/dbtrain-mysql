#include "record/fixed_record.h"

#include <assert.h>

#include "exception/exceptions.h"
#include "field/fields.h"
#include "utils/basic_function.h"
#include "utils/bitmap.h"

namespace dbtrain_mysql {

FixedRecord::FixedRecord(Size nFieldSize,
                         const std::vector<FieldType>& iTypeVec,
                         const std::vector<Size>& iSizeVec)
    : Record(nFieldSize), _iTypeVec(iTypeVec), _iSizeVec(iSizeVec) {
  assert(_iTypeVec.size() == nFieldSize);
  assert(_iSizeVec.size() == nFieldSize);
}

Size FixedRecord::Load(const uint8_t* src) {
  Clear();
  // 反序列化，为定长记录导入各个字段数据

  Size size = 0;
  // load NULL info
  Bitmap bitNULL(_iFields.size());
  for (Size i : _iSizeVec) size += i;
  bitNULL.Load(src + size);

  size = 0;
  for (FieldID i = 0; i < _iFields.size(); ++i) {
    Size fieldSize = _iSizeVec[i];
    Field* field_f = nullptr;
    if (bitNULL.Get(i)) {
      field_f = new NullField();
    } else {
      switch (_iTypeVec[i]) {
        case FieldType::NULL_TYPE:
          field_f = new NullField();
          break;
        case FieldType::INT_TYPE:
          field_f = new IntField();
          break;
        case FieldType::FLOAT_TYPE:
          field_f = new FloatField();
          break;
        case FieldType::CHAR_TYPE:
          field_f = new CharField(fieldSize);
          break;
        default:
          throw RecordTypeException();
          break;
      }
      field_f->SetData(src + size, fieldSize);
    }
    size += fieldSize;
    _iFields[i] = field_f;
  }

  return size + (_iFields.size() + 7) >> 3;
}

Size FixedRecord::Store(uint8_t* dst) const {
  // 序列化，将定长数据转化为特定格式

  Size size = 0;
  Bitmap bitNULL(_iFields.size());

  for (FieldID i = 0; i < _iFields.size(); ++i) {
    Size fieldSize = _iSizeVec[i];
    Field* field_f = _iFields[i];
    if (field_f == nullptr) throw NullptrException("FixedRecord::Load");
    field_f->GetData(dst + size, fieldSize);
    if (dynamic_cast<NullField*>(field_f)) bitNULL.Set(i);
    size += fieldSize;
  }

  // store NULL info
  bitNULL.Store(dst + size);

  return size + (_iFields.size() + 7) >> 3;
}

void FixedRecord::Build(const std::vector<String>& iRawVec) {
  assert(iRawVec.size() == _iTypeVec.size());
  Clear();
  for (FieldID i = 0; i < _iFields.size(); ++i) {
    FieldType iType = _iTypeVec[i];

    // TODO : after add NULL data, code here should change

    if (toUpper(iRawVec[i]) == "NULL") {
      SetField(i, new NullField());
    } else {
      if (iType == FieldType::NULL_TYPE) {
        SetField(i, new NullField());
      } else if (iType == FieldType::INT_TYPE) {
        try {
          int nVal = std::stoi(iRawVec[i]);
          SetField(i, new IntField(nVal));
        } catch (const std::invalid_argument& e) {
          printf("INT format error\n");
          throw e;
        } catch (const std::out_of_range& e) {
          printf("INT out of range\n");
          throw e;
        }
      } else if (iType == FieldType::FLOAT_TYPE) {
        try {
          double fVal = std::stod(iRawVec[i]);
          SetField(i, new FloatField(fVal));
        } catch (const std::invalid_argument& e) {
          printf("FLOAT format error\n");
          throw e;
        } catch (const std::out_of_range& e) {
          printf("FLOAT out of range\n");
          throw e;
        }
      } else if (iType == FieldType::CHAR_TYPE) {
        // erase \' and \"
        SetField(i, new CharField(iRawVec[i].substr(1, iRawVec[i].size() - 2)));
      } else {
        throw RecordTypeException();
      }
    }
  }
}

Record* FixedRecord::Clone() const {
  Record* pRecord = new FixedRecord(GetSize(), _iTypeVec, _iSizeVec);
  for (Size i = 0; i < GetSize(); ++i)
    pRecord->SetField(i, GetField(i)->Clone());
  return pRecord;
}

void FixedRecord::Sub(const std::vector<Size>& iPos) {
  bool bInSub[GetSize()];
  memset(bInSub, 0, GetSize() * sizeof(bool));
  for (const auto nPos : iPos) bInSub[nPos] = 1;
  auto itField = _iFields.begin();
  auto itType = _iTypeVec.begin();
  auto itSize = _iSizeVec.begin();
  auto nSize = GetSize();
  for (Size i = 0; i < nSize; ++i) {
    if (!bInSub[i]) {
      Field* pField = *itField;
      if (pField) delete pField;
      itField = _iFields.erase(itField);
      itType = _iTypeVec.erase(itType);
      itSize = _iSizeVec.erase(itSize);
    } else {
      ++itField;
      ++itType;
      ++itSize;
    }
  }
}

void FixedRecord::Add(Record* pRecord) {
  FixedRecord* pFixed = dynamic_cast<FixedRecord*>(pRecord);
  assert(pFixed != nullptr);
  for (Size i = 0; i < pFixed->GetSize(); ++i) {
    _iFields.push_back(pFixed->GetField(i)->Clone());
    _iTypeVec.push_back(pFixed->_iTypeVec[i]);
    _iSizeVec.push_back(pFixed->_iSizeVec[i]);
  }
}

void FixedRecord::Remove(FieldID nPos) {
  Record::Remove(nPos);
  auto itType = _iTypeVec.begin() + nPos;
  auto itSize = _iSizeVec.begin() + nPos;
  _iTypeVec.erase(itType);
  _iSizeVec.erase(itSize);
}

}  // namespace dbtrain_mysql
