#include "parser/parse.h"
using namespace dbtrain_mysql;

int main(){
    dbtrain_mysql::Parser p;
    p.init("../test/create.sql");
    p.parse();
}