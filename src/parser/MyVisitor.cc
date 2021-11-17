#include "MyVisitor.h"
namespace dbtrain_test{
    antlrcpp::Any MyVistor::visitCreate_db(MYSQLParser::Create_dbContext *ctx) {
        if (ctx->Identifier() != nullptr){
            std::string dbname = ctx->Identifier()->toString();
            printf("\t==============\n\t\t%s\t\n\t===============\n", &dbname);
        }
        else {
            // TODO: raise an error
        }
        return visitChildren(ctx);
    }
}