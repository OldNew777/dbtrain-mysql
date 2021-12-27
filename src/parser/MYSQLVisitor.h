
// Generated from MYSQL.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "MYSQLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by MYSQLParser.
 */
class  MYSQLVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by MYSQLParser.
   */
    virtual antlrcpp::Any visitProgram(MYSQLParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitStatement(MYSQLParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitCreate_db(MYSQLParser::Create_dbContext *context) = 0;

    virtual antlrcpp::Any visitDrop_db(MYSQLParser::Drop_dbContext *context) = 0;

    virtual antlrcpp::Any visitShow_dbs(MYSQLParser::Show_dbsContext *context) = 0;

    virtual antlrcpp::Any visitUse_db(MYSQLParser::Use_dbContext *context) = 0;

    virtual antlrcpp::Any visitShow_tables(MYSQLParser::Show_tablesContext *context) = 0;

    virtual antlrcpp::Any visitShow_indexes(MYSQLParser::Show_indexesContext *context) = 0;

    virtual antlrcpp::Any visitLoad_data(MYSQLParser::Load_dataContext *context) = 0;

    virtual antlrcpp::Any visitDump_data(MYSQLParser::Dump_dataContext *context) = 0;

    virtual antlrcpp::Any visitCreate_table(MYSQLParser::Create_tableContext *context) = 0;

    virtual antlrcpp::Any visitDrop_table(MYSQLParser::Drop_tableContext *context) = 0;

    virtual antlrcpp::Any visitDescribe_table(MYSQLParser::Describe_tableContext *context) = 0;

    virtual antlrcpp::Any visitInsert_into_table(MYSQLParser::Insert_into_tableContext *context) = 0;

    virtual antlrcpp::Any visitDelete_from_table(MYSQLParser::Delete_from_tableContext *context) = 0;

    virtual antlrcpp::Any visitUpdate_table(MYSQLParser::Update_tableContext *context) = 0;

    virtual antlrcpp::Any visitSelect_table_(MYSQLParser::Select_table_Context *context) = 0;

    virtual antlrcpp::Any visitSelect_table(MYSQLParser::Select_tableContext *context) = 0;

    virtual antlrcpp::Any visitAlter_add_index(MYSQLParser::Alter_add_indexContext *context) = 0;

    virtual antlrcpp::Any visitAlter_drop_index(MYSQLParser::Alter_drop_indexContext *context) = 0;

    virtual antlrcpp::Any visitAlter_table_drop_pk(MYSQLParser::Alter_table_drop_pkContext *context) = 0;

    virtual antlrcpp::Any visitAlter_table_drop_foreign_key(MYSQLParser::Alter_table_drop_foreign_keyContext *context) = 0;

    virtual antlrcpp::Any visitAlter_table_add_pk(MYSQLParser::Alter_table_add_pkContext *context) = 0;

    virtual antlrcpp::Any visitAlter_table_add_foreign_key(MYSQLParser::Alter_table_add_foreign_keyContext *context) = 0;

    virtual antlrcpp::Any visitAlter_table_add_unique(MYSQLParser::Alter_table_add_uniqueContext *context) = 0;

    virtual antlrcpp::Any visitAlter_table_rename(MYSQLParser::Alter_table_renameContext *context) = 0;

    virtual antlrcpp::Any visitField_list(MYSQLParser::Field_listContext *context) = 0;

    virtual antlrcpp::Any visitNormal_field(MYSQLParser::Normal_fieldContext *context) = 0;

    virtual antlrcpp::Any visitPrimary_key_field(MYSQLParser::Primary_key_fieldContext *context) = 0;

    virtual antlrcpp::Any visitForeign_key_field(MYSQLParser::Foreign_key_fieldContext *context) = 0;

    virtual antlrcpp::Any visitType_(MYSQLParser::Type_Context *context) = 0;

    virtual antlrcpp::Any visitValue_lists(MYSQLParser::Value_listsContext *context) = 0;

    virtual antlrcpp::Any visitValue_list(MYSQLParser::Value_listContext *context) = 0;

    virtual antlrcpp::Any visitValue(MYSQLParser::ValueContext *context) = 0;

    virtual antlrcpp::Any visitWhere_and_clause(MYSQLParser::Where_and_clauseContext *context) = 0;

    virtual antlrcpp::Any visitWhere_operator_expression(MYSQLParser::Where_operator_expressionContext *context) = 0;

    virtual antlrcpp::Any visitWhere_operator_select(MYSQLParser::Where_operator_selectContext *context) = 0;

    virtual antlrcpp::Any visitWhere_null(MYSQLParser::Where_nullContext *context) = 0;

    virtual antlrcpp::Any visitWhere_in_list(MYSQLParser::Where_in_listContext *context) = 0;

    virtual antlrcpp::Any visitWhere_in_select(MYSQLParser::Where_in_selectContext *context) = 0;

    virtual antlrcpp::Any visitWhere_like_string(MYSQLParser::Where_like_stringContext *context) = 0;

    virtual antlrcpp::Any visitColumn(MYSQLParser::ColumnContext *context) = 0;

    virtual antlrcpp::Any visitExpression(MYSQLParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitSet_clause(MYSQLParser::Set_clauseContext *context) = 0;

    virtual antlrcpp::Any visitSelectors(MYSQLParser::SelectorsContext *context) = 0;

    virtual antlrcpp::Any visitSelector(MYSQLParser::SelectorContext *context) = 0;

    virtual antlrcpp::Any visitIdentifiers(MYSQLParser::IdentifiersContext *context) = 0;

    virtual antlrcpp::Any visitOperator_(MYSQLParser::Operator_Context *context) = 0;

    virtual antlrcpp::Any visitAggregator(MYSQLParser::AggregatorContext *context) = 0;


};

