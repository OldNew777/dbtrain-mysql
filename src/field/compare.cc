#include <assert.h>

#include "exception/exceptions.h"
#include "field/fields.h"

namespace dbtrain_mysql {

bool Less(Field *pA, Field *pB) {
  if (dynamic_cast<NullField *>(pA) || dynamic_cast<NullField *>(pB))
    return false;
  FieldType iType = pA->GetType();
  if (iType != pB->GetType()) {
    auto e = CompareException();
    std::cout << e.what() << "\n";
    throw e;
  }
  if (iType == FieldType::INT_TYPE) {
    IntField *pIntA = dynamic_cast<IntField *>(pA);
    IntField *pIntB = dynamic_cast<IntField *>(pB);
    return *pIntA < *pIntB;
  } else if (iType == FieldType::FLOAT_TYPE) {
    FloatField *pFloatA = dynamic_cast<FloatField *>(pA);
    FloatField *pFloatB = dynamic_cast<FloatField *>(pB);
    return *pFloatA < *pFloatB;
  } else if (iType == FieldType::CHAR_TYPE) {
    CharField *pCharA = dynamic_cast<CharField *>(pA);
    CharField *pCharB = dynamic_cast<CharField *>(pB);
    return *pCharA < *pCharB;
  } else {
    return false;
  }
}

bool Equal(Field *pA, Field *pB) {
  if (dynamic_cast<NullField *>(pA) || dynamic_cast<NullField *>(pB))
    return false;
  FieldType iType = pA->GetType();
  if (iType != pB->GetType()) {
    auto e = CompareException();
    std::cout << e.what() << "\n";
    throw e;
  }
  if (iType == FieldType::INT_TYPE) {
    IntField *pIntA = dynamic_cast<IntField *>(pA);
    IntField *pIntB = dynamic_cast<IntField *>(pB);
    return *pIntA == *pIntB;
  } else if (iType == FieldType::FLOAT_TYPE) {
    FloatField *pFloatA = dynamic_cast<FloatField *>(pA);
    FloatField *pFloatB = dynamic_cast<FloatField *>(pB);
    return *pFloatA == *pFloatB;
  } else if (iType == FieldType::CHAR_TYPE) {
    CharField *pCharA = dynamic_cast<CharField *>(pA);
    CharField *pCharB = dynamic_cast<CharField *>(pB);
    return *pCharA == *pCharB;
  } else {
    return false;
  }
}

bool Greater(Field *pA, Field *pB) {
  if (dynamic_cast<NullField *>(pA) || dynamic_cast<NullField *>(pB))
    return false;
  FieldType iType = pA->GetType();
  if (iType != pB->GetType()) {
    auto e = CompareException();
    std::cout << e.what() << "\n";
    throw e;
  }
  if (iType == FieldType::INT_TYPE) {
    IntField *pIntA = dynamic_cast<IntField *>(pA);
    IntField *pIntB = dynamic_cast<IntField *>(pB);
    return *pIntA > *pIntB;
  } else if (iType == FieldType::FLOAT_TYPE) {
    FloatField *pFloatA = dynamic_cast<FloatField *>(pA);
    FloatField *pFloatB = dynamic_cast<FloatField *>(pB);
    return *pFloatA > *pFloatB;
  } else if (iType == FieldType::CHAR_TYPE) {
    CharField *pCharA = dynamic_cast<CharField *>(pA);
    CharField *pCharB = dynamic_cast<CharField *>(pB);
    return *pCharA > *pCharB;
  } else {
    return false;
  }
}

bool LessEqual(Field *pA, Field *pB) {
  if (dynamic_cast<NullField *>(pA) || dynamic_cast<NullField *>(pB))
    return false;
  FieldType iType = pA->GetType();
  if (iType != pB->GetType()) {
    auto e = CompareException();
    std::cout << e.what() << "\n";
    throw e;
  }
  if (iType == FieldType::INT_TYPE) {
    IntField *pIntA = dynamic_cast<IntField *>(pA);
    IntField *pIntB = dynamic_cast<IntField *>(pB);
    return *pIntA <= *pIntB;
  } else if (iType == FieldType::FLOAT_TYPE) {
    FloatField *pFloatA = dynamic_cast<FloatField *>(pA);
    FloatField *pFloatB = dynamic_cast<FloatField *>(pB);
    return *pFloatA <= *pFloatB;
  } else if (iType == FieldType::CHAR_TYPE) {
    CharField *pCharA = dynamic_cast<CharField *>(pA);
    CharField *pCharB = dynamic_cast<CharField *>(pB);
    return *pCharA <= *pCharB;
  } else {
    return false;
  }
}

}  // namespace dbtrain_mysql