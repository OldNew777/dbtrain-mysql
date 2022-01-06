#include <fstream>
#include <iostream>

#include "backend/backend.h"
#include "utils/display.h"

using namespace dbtrain_mysql;
int main() {
  printf("in main\n");
  Instance *pDB = new Instance();
  String sSQL = "", sBuffer;
  std::ifstream f;
  f.open("test.sql", std::ios::in);
  while (getline(f, sBuffer)) {
    sBuffer.erase(0, sBuffer.find_first_not_of(" "));
    if (sBuffer.substr(0, 2) == "--") {
      continue;
    }
    sSQL += " " + sBuffer;
    std::cout << "> " << sBuffer << std::endl;

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
  f.close();
  delete pDB;
  Close();
}