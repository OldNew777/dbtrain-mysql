#include "display.h"

namespace dbtrain_mysql {

void PrintTable(std::vector<Result*>& results) {
  for (auto result : results) {
    result->Display();
    delete result;
  }
}

}  // namespace dbtrain_mysql
