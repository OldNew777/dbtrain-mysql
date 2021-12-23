#include <iostream>

#include "backend/backend.h"
#include "utils/display.h"

using namespace dbtrain_mysql;

int main() {
  Instance *pDB = new Instance();
  String sSQL;
  std::cout << "> ";
  while (getline(std::cin, sSQL)) {
    if (sSQL == "\\q" || sSQL == "quit" || sSQL == "exit") {
      break;
    } else {
      try {
        std::vector<Result *> iResVec = Execute(pDB, sSQL);
        PrintTable(iResVec);
      } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
      }
    }
    std::cout << "> ";
  }
  delete pDB;
  Close();
}
