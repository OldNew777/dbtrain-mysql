#include <iostream>

#include "backend/backend.h"
#include "utils/basic_function.h"
#include "utils/display.h"

using namespace dbtrain_mysql;

int main() {
  Instance *pDB = new Instance();
  String sSQL = "", sBuffer;
  std::cout << "> ";
  while (getline(std::cin, sBuffer)) {
    sSQL += " " + sBuffer;
    if (toUpper(sBuffer) == "\\Q" || toUpper(sBuffer) == "QUIT" ||
        toUpper(sBuffer) == "EXIT") {
      break;
    } else {
      if (sBuffer[sBuffer.size() - 1] == ';') {
        try {
          std::vector<Result *> iResVec = Execute(pDB, sSQL);
          PrintTable(iResVec);
        } catch (const std::exception &e) {
          std::cerr << e.what() << '\n';
        }
        sSQL = "";
      }
    }
    std::cout << "> ";
  }
  delete pDB;
  Close();
}
