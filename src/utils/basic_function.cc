#include "basic_function.h"

#include <algorithm>
#include <cmath>

namespace dbtrain_mysql {

void PrintPageSlotID(const PageSlotID& nPageSlotID) {
  std::cout << '(' << nPageSlotID.first << ", " << nPageSlotID.second << ')';
}

String toUpper(const String& str) {
  String ans = str;
  std::transform(str.begin(), str.end(), ans.begin(), ::toupper);
  return ans;
}

float floatNext(const float& floatData) {
  // TODO : whether should here divided by 2?
  if (fabs(floatData) < __FLT_MIN__ / __FLT_EPSILON__)
    return floatData + __FLT_MIN__;
  else
    return floatData + fabs(floatData) * __FLT_EPSILON__;
}

}  // namespace dbtrain_mysql