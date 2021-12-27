#include "backend/backend.h"
#include "utils/display.h"
#include <iostream>
#include <fstream>

using namespace dbtrain_mysql;
int main(){
    Instance *pDB = new Instance();
    String sSQL;
    std::ifstream f;
    f.open("test.sql", std::ios::in);
    while (getline(f, sSQL)) {
        std::cout << "> " << sSQL << std::endl;
        try {
            std::vector<Result *> iResVec = Execute(pDB, sSQL);
            PrintTable(iResVec);
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }
    f.close();
    delete pDB;
    Close();
}