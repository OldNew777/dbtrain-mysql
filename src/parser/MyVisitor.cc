#include "MyVisitor.h"
using namespace dbtrain_mysql;
bool MyVisitor::current_db_available(){
    return (this->current_db_name == "");
}
antlrcpp::Any MyVisitor::visitCreate_db(MYSQLParser::Create_dbContext *ctx){

    if (!ctx->Identifier()){
        //TODO: raise a identifier null error
    }

    std::string dbname = ctx->Identifier()->toString();
    //TODO: check identifier is unique or not

    // create_db(db_name)

    std::cout << "CREATE_DATABASE(" << dbname << ");" << std::endl;    

    return 1;
}

antlrcpp::Any MyVisitor::visitDrop_db(MYSQLParser::Drop_dbContext *ctx) {
    if (!ctx->Identifier()){
        //TODO: raise a identifier null error
    }

    std::string dbname = ctx->Identifier()->toString();

    // drop_db(db_name)

    std::cout << "DROP_DATABASE(" << dbname << ");" << std::endl;    

    if(this->current_db_name == dbname){// drop the currently used db, change currernt name to null
        this->current_db_name = "";
    }

    return 1;
}

antlrcpp::Any MyVisitor::visitShow_dbs(MYSQLParser::Show_dbsContext *ctx){
    //TODO: ask for a list from backend
    std::cout << "show dbs" << std::endl;
    return 1;
}
antlrcpp::Any MyVisitor::visitUse_db(MYSQLParser::Use_dbContext *ctx) {
    if (!ctx->Identifier()){
        //TODO: raise a identifier null error
    }

    std::string dbname = ctx->Identifier()->toString();
    //TODO: check if dbname is created 
    this->current_db_name = dbname;
    std::cout << "USE_DATABASE(" << dbname << ");" << std::endl;    
    return 1;
}
antlrcpp::Any MyVisitor::visitShow_tables(MYSQLParser::Show_tablesContext *ctx) {
    if (current_db_available()){
        //TODO: raise db not created error
    }
    //get table list
    return 1;
}

antlrcpp::Any MyVisitor::visitShow_indexes(MYSQLParser::Show_indexesContext *ctx) {
    //TODO:
    return visitChildren(ctx);
}

antlrcpp::Any MyVisitor::visitLoad_data(MYSQLParser::Load_dataContext *ctx){
    if(ctx->String() == nullptr){
    //TODO: raise miss error  
        assert(0);
    }

    std::string path = ctx->String()->toString();
    
    if(ctx->Identifier() == nullptr){
        //TODO: raise miss error
        assert(0);
    }

    FILE* file = fopen(path.data(), "r");

    if(file == nullptr){
        //TODO: raise path error
    }
    
    //TODO: select table by name

    delete file;
    return 1;
}

antlrcpp::Any MyVisitor::visitDump_data(MYSQLParser::Dump_dataContext *ctx) {
    return visitChildren(ctx);
    if(ctx->String() == nullptr){
    //TODO: raise miss error  
        assert(0);
    }

    std::string path = ctx->String()->toString();
    
    if(ctx->Identifier() == nullptr){
        //TODO: raise miss error
        assert(0);
    }

    FILE* file = fopen(path.data(), "w");
    if(file == nullptr){
        //TODO: raise path error
    }
    delete file;
    return 1;
}

antlrcpp::Any MyVisitor::visitCreate_table(MYSQLParser::Create_tableContext *ctx){
    ctx->field_list()->accept(this);
    return visitChildren(ctx);
}

antlrcpp::Any MyVisitor::visitField_list(MYSQLParser::Field_listContext *ctx) {
    std::map<std::string, TYPE>* field_list = new std::map<std::string, TYPE>();
    visitChildren(ctx);
    return field_list;
}
antlrcpp::Any MyVisitor::visitNormal_field(MYSQLParser::Normal_fieldContext *ctx) {
    if(ctx->Identifier() == nullptr){
        assert(0);
    }
    std::string field_name = ctx->Identifier()->toString();
    return field_name;
    // return visitChildren(ctx);
}