#include "field/field.h"

namespace dbtrain_mysql {

bool Less(Field *pA, Field *pB);
bool Equal(Field *pA, Field *pB);
bool Greater(Field *pA, Field *pB);
bool LessEqual(Field *pA, Field *pB);
bool GreaterEqual(Field *pA, Field *pB);

}  // namespace dbtrain_mysql