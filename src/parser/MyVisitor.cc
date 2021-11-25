#include "MyVisitor.h"
using namespace dbtrain_mysql;
void MyVisitor::init(){
    //get the dblist
    this->db_list = new std::list<std::string>();
    this->db_list->push_back("test");
}

bool MyVisitor::current_db_null(){
    return (this->current_db_name == "");
}
bool MyVisitor::db_available(const std::string& s){
    if(db_list == nullptr){
        assert(0);
    }
    auto it = db_list->begin();
    while(it != db_list->end()){
        if((*it) == s){
            return true;
        }
        it ++;
    }
    return false;
}
bool MyVisitor::table_available(const std::string& s){
    if(table_list == nullptr){
        assert(0);
    }
    auto it = table_list->begin();
    while(it != table_list->end()){
        if((*it) == s){
            return true;
        }
        it ++;
    }
    return false;
}
antlrcpp::Any MyVisitor::visitCreate_db(MYSQLParser::Create_dbContext *ctx){

    if (!ctx->Identifier()){
        //TODO: raise a identifier null error
    }

    std::string dbname = ctx->Identifier()->toString();
    //TODO: check identifier is unique or not

    // create_db(db_name)

    std::cout << "CREATE_DATABASE(" << dbname << ");" << std::endl;   
    //add to local list
    db_list->push_back(dbname); 

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
        if(this->table_list != nullptr){
            delete this->table_list;
        }
        this->table_list = nullptr;
    }
    //delete from local list
    auto it = db_list->begin(); 
    while(it != db_list->end()){
        if((*it) == dbname){
            db_list->erase(it);
            break;
        }
        it ++;
    }
    return 1;
}

antlrcpp::Any MyVisitor::visitShow_dbs(MYSQLParser::Show_dbsContext *ctx){
    //TODO: ask for a list from backend
    printf("\ttable list:\n");
    auto it = db_list->begin();
    while(it != db_list->end()){
        printf("\t%s\n", &(*it));
        it ++;
    }
    std::cout << "show dbs" << std::endl;
    return 1;
}
antlrcpp::Any MyVisitor::visitUse_db(MYSQLParser::Use_dbContext *ctx) {
    if (!ctx->Identifier()){
        //TODO: raise a identifier null error
    }
    std::string dbname = ctx->Identifier()->toString();

    auto it = this->db_list->begin();
    bool flag = false;
    while(it != db_list->end()){
        if((*it) == dbname){
            flag = true;
        }
        it ++;
    }
    if(!flag){//no such db
        assert(0);
    }

    this->current_db_name = dbname;
    
    //update table list
    if(this->table_list != nullptr){
        delete table_list;
    }
    table_list = new std::list<std::string>();

    std::cout << "USE_DATABASE(" << dbname << ");" << std::endl;    
    return 1;
}
antlrcpp::Any MyVisitor::visitShow_tables(MYSQLParser::Show_tablesContext *ctx) {
    printf("\ttable list\n");
    auto it = this->table_list->begin();
    while(it != this->table_list->end()){
        printf("\t%s\n", &(*it));
        it ++;
    }
    //get table list
    return 1;
}

antlrcpp::Any MyVisitor::visitShow_indexes(MYSQLParser::Show_indexesContext *ctx) {
    //TODO: wtf is show indexes
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
    this->_current_table_head = new std::vector<TableHead>();

    ctx->field_list()->accept(this);

    if(this->_current_table_head == nullptr){
        assert(0);
    }

    std::string table_name = ctx->Identifier()->toString();

    auto it = this->_current_table_head->begin();
    printf("create table\n");
    while(it != this->_current_table_head->end()){
        std::cout << it->headName << std::endl;
        it ++;
    }
    this->table_list->push_back(table_name);
    //TODO: update backend

    delete this->_current_table_head;
    this->_current_table_head = nullptr;
    //add to table list
    
    return 1;
}

antlrcpp::Any MyVisitor::visitField_list(MYSQLParser::Field_listContext *ctx) {
    return visitChildren(ctx);
}
antlrcpp::Any MyVisitor::visitNormal_field(MYSQLParser::Normal_fieldContext *ctx) {
    if(ctx->Identifier() == nullptr){
        assert(0);
    }
    std::string field_name = ctx->Identifier()->toString();
    //TODO: cha chong
    this->_current_table_head->push_back(TableHead(field_name, TYPE::INT));
    return 1;
    // return visitChildren(ctx);
}
antlrcpp::Any MyVisitor::visitDrop_table(MYSQLParser::Drop_tableContext *ctx){
    if(ctx->Identifier() == nullptr){
        assert(0);
    }
    std::string table_name = ctx->Identifier()->toString();
    //drop table

    //delete from local list
    auto it = this->table_list->begin();
    while(it != this->table_list->end()){
        if ((*it) == table_name){
            this->table_list->erase(it);
            break;
        } 
    }
    return 1;
}
antlrcpp::Any MyVisitor::visitInsert_into_table(MYSQLParser::Insert_into_tableContext *ctx){
    if(ctx->Identifier() == nullptr){
        assert(0);
    }
    std::string table_name;
    //open table
    visitChildren(ctx);
    return 1;
}

antlrcpp::Any MyVisitor::visitWhere_and_clause(MYSQLParser::Where_and_clauseContext *ctx)  {
    return visitChildren(ctx);
}
antlrcpp::Any MyVisitor::visitWhere_operator_expression(MYSQLParser::Where_operator_expressionContext *ctx){
    
    return visitChildren(ctx);
}