#ifndef DBTRAIN_MYSQL_MYVISITOR_H_
#define DBTRAIN_MYSQL_MYVISITOR_H_

#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include "util.h"
#include "../system/instance.h"
#include "MYSQLVisitor.h"
using namespace antlr4;

namespace dbtrain_mysql {
    class MyVisitor : public MYSQLVisitor {
    private:
    std::vector<TableHead>* _current_table_head = nullptr;
    std::vector<std::vector<Data*>*>* _current_value_lists = nullptr; 
    std::vector<Data*>* _tmp_value_list = nullptr;
    std::map<std::string, Instance*> _dbs;
    
    
    int _load_form_db_list(std::list<std::string>* v){
        std::ifstream in(DB_LIST_PATH);
        std::string line;
        if(in){
            while(std::getline (in, line)){
                v->push_back(line);
            }
        }

        // char tmpbuffer[1000] = {0};
        // FILE* f = fopen(DB_LIST_PATH.data(), "r");
        // while(!feof(f)){
        //     fgets(tmpbuffer, sizeof(tmpbuffer) - 1, f);

        //     v->push_back(tmpbuffer);
        //     printf("%s\n", tmpbuffer);
        // }
        // fclose(f);
    }

    public:
        std::string current_db_name = "";
        std::list<std::string>* db_list;
        std::list<std::string>* table_list = nullptr;

        bool current_db_null();
        bool db_available(const std::string&);
        bool table_available(const std::string&);
        void cast_db_list();

        void init();
        ~MyVisitor(){
            if(db_list != nullptr){
                delete db_list;
            }
            if(table_list != nullptr){
                delete table_list;
            }
        }

        

        virtual antlrcpp::Any visitProgram(
            MYSQLParser::ProgramContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitStatement(
            MYSQLParser::StatementContext *ctx) override {
            return visitChildren(ctx);
        } 

        virtual antlrcpp::Any visitCreate_db(MYSQLParser::Create_dbContext *ctx) override;
        virtual antlrcpp::Any visitDrop_db(MYSQLParser::Drop_dbContext *ctx) override;
        virtual antlrcpp::Any visitShow_dbs(MYSQLParser::Show_dbsContext *ctx) override;
        virtual antlrcpp::Any visitUse_db(MYSQLParser::Use_dbContext *ctx) override;
        virtual antlrcpp::Any visitShow_tables(MYSQLParser::Show_tablesContext *ctx) override;
        virtual antlrcpp::Any visitShow_indexes(MYSQLParser::Show_indexesContext *ctx) override;
        virtual antlrcpp::Any visitLoad_data(MYSQLParser::Load_dataContext *ctx) override;
        virtual antlrcpp::Any visitDump_data(MYSQLParser::Dump_dataContext *ctx) override;

        virtual antlrcpp::Any visitCreate_table(MYSQLParser::Create_tableContext *ctx) override;
        virtual antlrcpp::Any visitDrop_table(MYSQLParser::Drop_tableContext *ctx) override;
        virtual antlrcpp::Any visitDescribe_table(MYSQLParser::Describe_tableContext *ctx) override;

        virtual antlrcpp::Any visitInsert_into_table(MYSQLParser::Insert_into_tableContext *ctx) override;

        virtual antlrcpp::Any visitDelete_from_table(MYSQLParser::Delete_from_tableContext *ctx) override;

        virtual antlrcpp::Any visitUpdate_table(
            MYSQLParser::Update_tableContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitSelect_table_(
            MYSQLParser::Select_table_Context *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitSelect_table(
            MYSQLParser::Select_tableContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitAlter_add_index(
            MYSQLParser::Alter_add_indexContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitAlter_drop_index(
            MYSQLParser::Alter_drop_indexContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitAlter_table_drop_pk(
            MYSQLParser::Alter_table_drop_pkContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitAlter_table_drop_foreign_key(
            MYSQLParser::Alter_table_drop_foreign_keyContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitAlter_table_add_pk(
            MYSQLParser::Alter_table_add_pkContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitAlter_table_add_foreign_key(
            MYSQLParser::Alter_table_add_foreign_keyContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitAlter_table_add_unique(
            MYSQLParser::Alter_table_add_uniqueContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitField_list(MYSQLParser::Field_listContext *ctx) override;

        virtual antlrcpp::Any visitNormal_field(MYSQLParser::Normal_fieldContext *ctx) override;

        virtual antlrcpp::Any visitPrimary_key_field(
            MYSQLParser::Primary_key_fieldContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitForeign_key_field(
            MYSQLParser::Foreign_key_fieldContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitType_(MYSQLParser::Type_Context *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitValue_lists(
            MYSQLParser::Value_listsContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitValue_list(MYSQLParser::Value_listContext *ctx);
        virtual antlrcpp::Any visitValue(MYSQLParser::ValueContext *ctx) override;

        virtual antlrcpp::Any visitWhere_and_clause(MYSQLParser::Where_and_clauseContext *ctx) override;
        virtual antlrcpp::Any visitWhere_operator_expression(MYSQLParser::Where_operator_expressionContext *ctx) override;

        virtual antlrcpp::Any visitWhere_operator_select(
            MYSQLParser::Where_operator_selectContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitWhere_null(
            MYSQLParser::Where_nullContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitWhere_in_list(
            MYSQLParser::Where_in_listContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitWhere_in_select(
            MYSQLParser::Where_in_selectContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitWhere_like_string(
            MYSQLParser::Where_like_stringContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitColumn(MYSQLParser::ColumnContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitExpression(
            MYSQLParser::ExpressionContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitSet_clause(
            MYSQLParser::Set_clauseContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitSelectors(
            MYSQLParser::SelectorsContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitSelector(
            MYSQLParser::SelectorContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitIdentifiers(
            MYSQLParser::IdentifiersContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitOperator_(
            MYSQLParser::Operator_Context *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitAggregator(
            MYSQLParser::AggregatorContext *ctx) override {
            return visitChildren(ctx);
        }
    };
}  // namespace dbtrain_mysql

#endif