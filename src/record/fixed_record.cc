#include "record/fixed_record.h"

#include <assert.h>

#include "exception/exceptions.h"
#include "field/fields.h"
#include "utils/basic_function.h"

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
  // 利用Field的抽象方法SetData导入数据
  // 基于类型判断构建的指针类型

  Size size = 0;
  for (FieldID i = 0; i < _iFields.size(); ++i) {
    Size fieldSize = _iSizeVec[i];
    Field* field_f = nullptr;
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
        break;
    }
    if (field_f == nullptr) throw NullptrException("FixedRecord::Load");
    field_f->SetData(src + size, fieldSize);
    size += fieldSize;
    _iFields[i] = field_f;
  }
  return size;
}

Size FixedRecord::Store(uint8_t* dst) const {
  // 序列化，将定长数据转化为特定格式
  // 利用Field的抽象方法GetData写出数据

  Size size = 0;
  for (FieldID i = 0; i < _iFields.size(); ++i) {
    Size fieldSize = _iSizeVec[i];
    Field* field_f = _iFields[i];
    if (field_f == nullptr) throw NullptrException("FixedRecord::Load");
    field_f->GetData(dst + size, fieldSize);
    size += fieldSize;
  }
  return size;
}

void FixedRecord::Build(const std::vector<String>& iRawVec) {
  assert(iRawVec.size() == _iTypeVec.size());
  Clear();
  for (FieldID i = 0; i < _iFields.size(); ++i) {
    FieldType iType = _iTypeVec[i];

    // TODO : after add NULL data, code here should change

    Field* pField = nullptr;
    bool isNull = (toUpper(iRawVec[i]) == "NULL");
    if (iType == FieldType::INT_TYPE) {
      if (isNull) {
        pField = new IntField(0);
        pField->SetNull(true);
      } else {
        int nVal = std::stoi(iRawVec[i]);
        pField = new IntField(nVal);
      }
    } else if (iType == FieldType::FLOAT_TYPE) {
      if (isNull) {
        pField = new FloatField(0.0);
        pField->SetNull(true);
      } else {
        double fVal = std::stod(iRawVec[i]);
        pField = new FloatField(fVal);
      }
    } else if (iType == FieldType::CHAR_TYPE) {
      // TODO : set length
      if (isNull) {
        pField = new CharField();
        pField->SetNull(true);
      } else {
        // erase \' and \"
        String cVal = iRawVec[i].substr(1, iRawVec[i].size() - 2);
        pField = new CharField(cVal);
      }
    } else {
      throw RecordTypeException();
    }
    SetField(i, pField);
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
