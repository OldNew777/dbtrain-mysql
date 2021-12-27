#include "SystemVisitor.h"

#include <float.h>

namespace dbtrain_mysql {

SystemVisitor::SystemVisitor(Instance *pDB) : _pDB{pDB} { assert(_pDB); }

// void SystemVisitor::init(){
    //get the dblist
    //TODO: load db list
// }

// void SystemVisitor::cast_db_list(){
//     FILE* f = fopen(DB_LIST_PATH.data(), "w");
//     for(auto it = _dbs.begin(); it != _dbs.end(); it ++){
//         fputs(it->first.data(), f);
//         fputs("\n", f);
//     }
//     fclose(f);
// }

// bool SystemVisitor::current_db_null(){
//     return (this->current_db_name == "");
// }
// bool SystemVisitor::table_available(const std::string& s){
//     if(table_list == nullptr){
//         assert(0);
//     }
//     auto it = table_list->begin();
//     while(it != table_list->end()){
//         if((*it) == s){
//             return true;
//         }
//         it ++;
//     }
//     return false;
// }
antlrcpp::Any SystemVisitor::visitCreate_db(MYSQLParser::Create_dbContext *ctx){

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

antlrcpp::Any SystemVisitor::visitDrop_db(MYSQLParser::Drop_dbContext *ctx) {
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

antlrcpp::Any SystemVisitor::visitShow_dbs(MYSQLParser::Show_dbsContext *ctx){
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
antlrcpp::Any SystemVisitor::visitUse_db(MYSQLParser::Use_dbContext *ctx) {
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
antlrcpp::Any SystemVisitor::visitShow_tables(MYSQLParser::Show_tablesContext *ctx) {
    std::cout << "table list\n";
    //get table list
    return _pDB->GetTableNames();
}

antlrcpp::Any SystemVisitor::visitShow_indexes(MYSQLParser::Show_indexesContext *ctx) {
    //TODO: wtf is show indexes
    return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitLoad_data(MYSQLParser::Load_dataContext *ctx){
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

antlrcpp::Any SystemVisitor::visitDump_data(MYSQLParser::Dump_dataContext *ctx) {
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

antlrcpp::Any SystemVisitor::visitCreate_table(MYSQLParser::Create_tableContext *ctx){
    ctx->field_list()->accept(this);
    std::string table_name = ctx->Identifier()->toString();
    std::cout << table_name << " ";
    bool flag = _pDB->CreateTable(table_name, Schema(_current_field_list));
    //reset _current_field_list
    std::cout << flag << std::endl;
    _current_field_list.clear();
    //add to table list
    return flag;
}

antlrcpp::Any SystemVisitor::visitNormal_field(MYSQLParser::Normal_fieldContext *ctx) {
    if(ctx->Identifier() == nullptr){
        assert(0);
    }
    std::string field_name = ctx->Identifier()->toString();
    std::string type = ctx->type_()->accept(this);
    //TODO: cha chong
    FieldType tmp = FieldType::NULL_TYPE;
    std::cout << type << " ";
    if(type == "INT"){
        _current_field_list.push_back(Column(field_name, FieldType::INT_TYPE));    
    }
    else if(type == "FLOAT"){
        _current_field_list.push_back(Column(field_name, FieldType::FLOAT_TYPE));    
    }
    else{
        _current_field_list.push_back(Column(field_name, FieldType::CHAR_TYPE, stoi(ctx->type_()->Integer()->toString())));    
    }
    return 1;
}
antlrcpp::Any SystemVisitor::visitType_(MYSQLParser::Type_Context *ctx){
    return ctx->getText();
}
antlrcpp::Any SystemVisitor::visitDrop_table(MYSQLParser::Drop_tableContext *ctx){
    if(ctx->Identifier() == nullptr){
        assert(0);
    }
    std::string table_name = ctx->Identifier()->toString();
    //drop table
    return _pDB->DropTable(table_name);
}
antlrcpp::Any SystemVisitor::visitInsert_into_table(MYSQLParser::Insert_into_tableContext *ctx){
    if(ctx->Identifier() == nullptr){
        assert(0);
    }
    std::string table_name = ctx->Identifier()->toString();
    //open table
    ctx->value_lists()->accept(this);
    for(auto it = _current_value_lists.begin(); it != _current_value_lists.end(); it ++){
        std::cout << (*it)[0] << " " << (*it)[1] <<  std::endl;
        _pDB->Insert(table_name, (*it));
    }

    _current_value_lists.clear();

    return 1;
}

antlrcpp::Any SystemVisitor::visitValue_list(MYSQLParser::Value_listContext *ctx) {
    _current_value_lists.push_back(std::vector<String>());
    visitChildren(ctx);
    return 1;
}

antlrcpp::Any SystemVisitor::visitValue(MYSQLParser::ValueContext *ctx){
    _current_value_lists[_current_value_lists.size() - 1].push_back(ctx->getText());
    return 1;
}

antlrcpp::Any SystemVisitor::visitWhere_and_clause(MYSQLParser::Where_and_clauseContext *ctx)  {
    return visitChildren(ctx);
}
antlrcpp::Any SystemVisitor::visitWhere_operator_expression(MYSQLParser::Where_operator_expressionContext *ctx){
    
    return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitDescribe_table(MYSQLParser::Describe_tableContext *ctx) {
    std::string tableName = ctx->Identifier()->toString();
    //TODO: describe_table function
    return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitDelete_from_table(MYSQLParser::Delete_from_tableContext *ctx) {
    std::string tableName = ctx->Identifier()->toString();
    return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitSelect_table(MYSQLParser::Select_tableContext *ctx){
    ctx->identifiers()->accept(this);
    ctx->selectors()->accept(this);
    std::vector<Record*> records;
    for(auto table_name_it = _current_table_names.begin(); table_name_it != _current_table_names.end(); table_name_it ++){
        std::vector<PageSlotID> pageSlotID;
        std::cout << "selecting from " << *table_name_it << std::endl;
        for(auto selector_it = _current_selectors.begin(); selector_it != _current_selectors.end(); selector_it ++){
            Condition* cond = nullptr;
            std::vector<Condition*> iCond;
            std::cout << "using selector: " << *selector_it <<std::endl;
            if((*selector_it) == "*"){
                cond = new AllCondition();
            }
            for(auto it = _pDB->Search((*table_name_it), cond, iCond).begin(); it != _pDB->Search((*table_name_it), cond, iCond).end(); it ++){
                std::cout << (*it).first << " " << (*it).second << std::endl;
                records.push_back(_pDB->GetRecord((*table_name_it), (*it)));
            }
            if(cond != nullptr){
                delete cond;
                cond = nullptr;
            }
        }
    }
    _current_selectors.clear();
    _current_table_names.clear();
    return records;
}
antlrcpp::Any SystemVisitor::visitSelectors(MYSQLParser::SelectorsContext *ctx) {
    std::string text = ctx->getText();
    if(text == "*"){
        _current_selectors.push_back("*");
        return 1;
    }
    else{
        for(int i = 0; i < ctx->selector().size(); i ++){
            if(ctx->selector()[i]->aggregator() != nullptr){
                std::string col =  ctx->selector()[i]->column()->accept(this);
                _current_selectors.push_back(ctx->selector()[i]->aggregator()->getText() + " " + col) ;
                std::cout << _current_selectors.back() << std::endl;
            }
            else if (ctx->selector()[i]->Count() != nullptr){
                _current_selectors.push_back("countstar");
            }
        }
    }
    
    
    return 1;
}
antlrcpp::Any SystemVisitor::visitIdentifiers(MYSQLParser::IdentifiersContext *ctx){
    for(int i = 0; i < ctx->Identifier().size(); i ++){
        _current_table_names.push_back(ctx->Identifier()[i]->toString());
    }
    return 1;
}
antlrcpp::Any SystemVisitor::visitColumn(MYSQLParser::ColumnContext *ctx){
    return ctx->Identifier()[0]->toString() + " " + ctx->Identifier()[1]->toString();
}

}  // namespace dbtrain_mysql