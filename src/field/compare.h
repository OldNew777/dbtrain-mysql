#include "field/field.h"

namespace dbtrain_mysql {

bool Less(Field *pA, Field *pB, FieldType iType);
bool Equal(Field *pA, Field *pB, FieldType iType);
bool Greater(Field *pA, Field *pB, FieldType iType);

}  // namespace dbtrain_mysql