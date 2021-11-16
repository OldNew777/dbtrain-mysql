#include "basic_function.h"

#include <algorithm>

namespace dbtrain_mysql {

void PrintPageSlotID(const PageSlotID& nPageSlotID) {
  std::cout << '(' << nPageSlotID.first << ", " << nPageSlotID.second << ')';
}

String toUpper(const String& str) {
  String ans = "";
  std::transform(str.begin(), str.end(), ans.begin(), ::toupper);
  return ans;
}

}  // namespace dbtrain_mysql