#include "MyVisitor.h"
using namespace dbtrain_mysql;
void MyVisitor::init(){
    //get the dblist
    //TODO: load db list
}

void MyVisitor::cast_db_list(){
    FILE* f = fopen(DB_LIST_PATH.data(), "w");
    for(auto it = _dbs.begin(); it != _dbs.end(); it ++){
        fputs(it->first.data(), f);
        fputs("\n", f);
    }
    fclose(f);
}

bool MyVisitor::current_db_null(){
    return (this->current_db_name == "");
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

    if(_dbs.find(dbname) != _dbs.end()){//not unique
        assert(0);
    }

    std::cout << "CREATE_DATABASE(" << dbname << ");" << std::endl;   
    //add to local list
    _dbs[dbname] = new Instance(); 

    return 1;
}

antlrcpp::Any MyVisitor::visitDrop_db(MYSQLParser::Drop_dbContext *ctx) {
    if (!ctx->Identifier()){
        //TODO: raise a identifier null error
    }

    std::string dbname = ctx->Identifier()->toString();

    auto tmp = _dbs.find(dbname);
    if(tmp == _dbs.end()){//db not exist
        assert(0);
    }

    std::cout << "DROP_DATABASE(" << dbname << ");" << std::endl;    

    if(this->current_db_name == dbname){// drop the currently used db, change currernt name to null
        this->current_db_name = "";
        if(this->table_list != nullptr){
            delete this->table_list;
        }
        this->table_list = nullptr;
    }
    //delete from local list
    delete (*tmp).second;
    _dbs.erase(tmp);
    return 1;
}

antlrcpp::Any MyVisitor::visitShow_dbs(MYSQLParser::Show_dbsContext *ctx){
    //TODO: ask for a list from backend
    printf("******database list******\n");
    auto it = _dbs.begin();
    
    while(it != _dbs.end()){
        std::cout  << "\t" <<(*it).first << std::endl;
        it ++;
    }
    std::cout << "*****************" << std::endl;
    return 1;
}
antlrcpp::Any MyVisitor::visitUse_db(MYSQLParser::Use_dbContext *ctx) {
    if (!ctx->Identifier()){
        //TODO: raise a identifier null error
    }
    std::string dbname = ctx->Identifier()->toString();

    
    

    this->current_db_name = dbname;

    auto tmp = _dbs.find(dbname);
    if(tmp == _dbs.end()){//db not exist
        assert(0);
    }

    std::cout << "USE_DATABASE(" << dbname << ");" << std::endl;    
    return 1;
}
antlrcpp::Any MyVisitor::visitShow_tables(MYSQLParser::Show_tablesContext *ctx) {
    std::cout << "table list\n";
    auto it = this->table_list->begin();
    while(it != this->table_list->end()){
        std::cout << *it << std::endl;
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
    std::cout << "create table" <<  table_name << " has heading of:" << std::endl;
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
    this->_current_value_lists = new std::vector<std::vector<Data*> *>();

    ctx->value_lists()->accept(this);

    //TODO: insert into table 

    //delete the _currerny value list
    for(int i = 0; i < this->_current_value_lists->size(); i ++){
        if((*_current_value_lists)[i] != nullptr){
            delete (*_current_value_lists)[i];
        }
    }
    delete _current_value_lists;
    _current_value_lists = nullptr;

    return 1;
}

antlrcpp::Any MyVisitor::visitValue_list(MYSQLParser::Value_listContext *ctx) {
    //
    _tmp_value_list = new std::vector<Data*>();
    _current_value_lists->push_back(_tmp_value_list);

    visitChildren(ctx);



    return 1;
}

antlrcpp::Any MyVisitor::visitValue(MYSQLParser::ValueContext *ctx){
    if(ctx->String() != nullptr){
        _tmp_value_list->push_back(new Str(ctx->String()->toString()));
    }
    else if(ctx->Integer() != nullptr){
        _tmp_value_list->push_back(new Int(atoi(ctx->Integer()->toString().data())));
    }
    else if(ctx->Float() != nullptr){
        _tmp_value_list->push_back(new Float(atof(ctx->Float()->toString().data())));
    }
    else{
        _tmp_value_list->push_back(new Null());
    }
    return 1;
}

antlrcpp::Any MyVisitor::visitWhere_and_clause(MYSQLParser::Where_and_clauseContext *ctx)  {
    return visitChildren(ctx);
}
antlrcpp::Any MyVisitor::visitWhere_operator_expression(MYSQLParser::Where_operator_expressionContext *ctx){
    
    return visitChildren(ctx);
}

antlrcpp::Any MyVisitor::visitDescribe_table(MYSQLParser::Describe_tableContext *ctx) {
    std::string tableName = ctx->Identifier()->toString();
    //TODO: describe_table function
    return visitChildren(ctx);
}

antlrcpp::Any MyVisitor::visitDelete_from_table(MYSQLParser::Delete_from_tableContext *ctx) {
    std::string tableName = ctx->Identifier()->toString();
    return visitChildren(ctx);
}