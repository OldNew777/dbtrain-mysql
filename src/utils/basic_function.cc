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

float floatNext(const float& data) {
  // TODO : whether should here divided by 2?
  if (fabs(data) < __FLT_MIN__ / __FLT_EPSILON__)
    return data + __FLT_MIN__;
  else
    return data + fabs(data) * __FLT_EPSILON__;
}
int intNext(const int& data) {
  if (data != INT32_MAX)
    return data + 1;
  else
    // TODO : how to deal with INT32_MAX?
    return INT32_MAX;
}
String stringNext(const String& data) {
  // visiable char problem?
  String ans = data;
  if (data.length() == 0 || data[data.length() - 1] >= 126)
    ans += ' ';
  else
    ans[data.length() - 1] += 1;
}

}  // namespace dbtrain_mysql