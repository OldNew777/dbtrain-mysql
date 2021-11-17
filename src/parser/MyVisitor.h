#ifndef DBTRAIN_MYSQL_MYVISITOR_H_
#define DBTRAIN_MYSQL_MYVISITOR_H_

#include "MYSQLBaseVisitor.h"

#include <string.h>
using namespace antlr4;


namespace dbtrain_test{
    class MyVistor: public MYSQLBaseVisitor{
    public:
        virtual antlrcpp::Any visitCreate_db(MYSQLParser::Create_dbContext *ctx) override;
    };
}
    

#endif