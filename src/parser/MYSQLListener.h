
// Generated from MYSQL.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "MYSQLParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by MYSQLParser.
 */
class  MYSQLListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(MYSQLParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(MYSQLParser::ProgramContext *ctx) = 0;

  virtual void enterStatement(MYSQLParser::StatementContext *ctx) = 0;
  virtual void exitStatement(MYSQLParser::StatementContext *ctx) = 0;

  virtual void enterCreate_db(MYSQLParser::Create_dbContext *ctx) = 0;
  virtual void exitCreate_db(MYSQLParser::Create_dbContext *ctx) = 0;

  virtual void enterDrop_db(MYSQLParser::Drop_dbContext *ctx) = 0;
  virtual void exitDrop_db(MYSQLParser::Drop_dbContext *ctx) = 0;

  virtual void enterShow_dbs(MYSQLParser::Show_dbsContext *ctx) = 0;
  virtual void exitShow_dbs(MYSQLParser::Show_dbsContext *ctx) = 0;

  virtual void enterUse_db(MYSQLParser::Use_dbContext *ctx) = 0;
  virtual void exitUse_db(MYSQLParser::Use_dbContext *ctx) = 0;

  virtual void enterShow_tables(MYSQLParser::Show_tablesContext *ctx) = 0;
  virtual void exitShow_tables(MYSQLParser::Show_tablesContext *ctx) = 0;

  virtual void enterShow_indexes(MYSQLParser::Show_indexesContext *ctx) = 0;
  virtual void exitShow_indexes(MYSQLParser::Show_indexesContext *ctx) = 0;

  virtual void enterLoad_data(MYSQLParser::Load_dataContext *ctx) = 0;
  virtual void exitLoad_data(MYSQLParser::Load_dataContext *ctx) = 0;

  virtual void enterDump_data(MYSQLParser::Dump_dataContext *ctx) = 0;
  virtual void exitDump_data(MYSQLParser::Dump_dataContext *ctx) = 0;

  virtual void enterCreate_table(MYSQLParser::Create_tableContext *ctx) = 0;
  virtual void exitCreate_table(MYSQLParser::Create_tableContext *ctx) = 0;

  virtual void enterDrop_table(MYSQLParser::Drop_tableContext *ctx) = 0;
  virtual void exitDrop_table(MYSQLParser::Drop_tableContext *ctx) = 0;

  virtual void enterDescribe_table(MYSQLParser::Describe_tableContext *ctx) = 0;
  virtual void exitDescribe_table(MYSQLParser::Describe_tableContext *ctx) = 0;

  virtual void enterInsert_into_table(MYSQLParser::Insert_into_tableContext *ctx) = 0;
  virtual void exitInsert_into_table(MYSQLParser::Insert_into_tableContext *ctx) = 0;

  virtual void enterDelete_from_table(MYSQLParser::Delete_from_tableContext *ctx) = 0;
  virtual void exitDelete_from_table(MYSQLParser::Delete_from_tableContext *ctx) = 0;

  virtual void enterUpdate_table(MYSQLParser::Update_tableContext *ctx) = 0;
  virtual void exitUpdate_table(MYSQLParser::Update_tableContext *ctx) = 0;

  virtual void enterSelect_table_(MYSQLParser::Select_table_Context *ctx) = 0;
  virtual void exitSelect_table_(MYSQLParser::Select_table_Context *ctx) = 0;

  virtual void enterSelect_table(MYSQLParser::Select_tableContext *ctx) = 0;
  virtual void exitSelect_table(MYSQLParser::Select_tableContext *ctx) = 0;

  virtual void enterAlter_add_index(MYSQLParser::Alter_add_indexContext *ctx) = 0;
  virtual void exitAlter_add_index(MYSQLParser::Alter_add_indexContext *ctx) = 0;

  virtual void enterAlter_drop_index(MYSQLParser::Alter_drop_indexContext *ctx) = 0;
  virtual void exitAlter_drop_index(MYSQLParser::Alter_drop_indexContext *ctx) = 0;

  virtual void enterAlter_table_drop_pk(MYSQLParser::Alter_table_drop_pkContext *ctx) = 0;
  virtual void exitAlter_table_drop_pk(MYSQLParser::Alter_table_drop_pkContext *ctx) = 0;

  virtual void enterAlter_table_drop_foreign_key(MYSQLParser::Alter_table_drop_foreign_keyContext *ctx) = 0;
  virtual void exitAlter_table_drop_foreign_key(MYSQLParser::Alter_table_drop_foreign_keyContext *ctx) = 0;

  virtual void enterAlter_table_add_pk(MYSQLParser::Alter_table_add_pkContext *ctx) = 0;
  virtual void exitAlter_table_add_pk(MYSQLParser::Alter_table_add_pkContext *ctx) = 0;

  virtual void enterAlter_table_add_foreign_key(MYSQLParser::Alter_table_add_foreign_keyContext *ctx) = 0;
  virtual void exitAlter_table_add_foreign_key(MYSQLParser::Alter_table_add_foreign_keyContext *ctx) = 0;

  virtual void enterAlter_table_add_unique(MYSQLParser::Alter_table_add_uniqueContext *ctx) = 0;
  virtual void exitAlter_table_add_unique(MYSQLParser::Alter_table_add_uniqueContext *ctx) = 0;

  virtual void enterField_list(MYSQLParser::Field_listContext *ctx) = 0;
  virtual void exitField_list(MYSQLParser::Field_listContext *ctx) = 0;

  virtual void enterNormal_field(MYSQLParser::Normal_fieldContext *ctx) = 0;
  virtual void exitNormal_field(MYSQLParser::Normal_fieldContext *ctx) = 0;

  virtual void enterPrimary_key_field(MYSQLParser::Primary_key_fieldContext *ctx) = 0;
  virtual void exitPrimary_key_field(MYSQLParser::Primary_key_fieldContext *ctx) = 0;

  virtual void enterForeign_key_field(MYSQLParser::Foreign_key_fieldContext *ctx) = 0;
  virtual void exitForeign_key_field(MYSQLParser::Foreign_key_fieldContext *ctx) = 0;

  virtual void enterType_(MYSQLParser::Type_Context *ctx) = 0;
  virtual void exitType_(MYSQLParser::Type_Context *ctx) = 0;

  virtual void enterValue_lists(MYSQLParser::Value_listsContext *ctx) = 0;
  virtual void exitValue_lists(MYSQLParser::Value_listsContext *ctx) = 0;

  virtual void enterValue_list(MYSQLParser::Value_listContext *ctx) = 0;
  virtual void exitValue_list(MYSQLParser::Value_listContext *ctx) = 0;

  virtual void enterValue(MYSQLParser::ValueContext *ctx) = 0;
  virtual void exitValue(MYSQLParser::ValueContext *ctx) = 0;

  virtual void enterWhere_and_clause(MYSQLParser::Where_and_clauseContext *ctx) = 0;
  virtual void exitWhere_and_clause(MYSQLParser::Where_and_clauseContext *ctx) = 0;

  virtual void enterWhere_operator_expression(MYSQLParser::Where_operator_expressionContext *ctx) = 0;
  virtual void exitWhere_operator_expression(MYSQLParser::Where_operator_expressionContext *ctx) = 0;

  virtual void enterWhere_operator_select(MYSQLParser::Where_operator_selectContext *ctx) = 0;
  virtual void exitWhere_operator_select(MYSQLParser::Where_operator_selectContext *ctx) = 0;

  virtual void enterWhere_null(MYSQLParser::Where_nullContext *ctx) = 0;
  virtual void exitWhere_null(MYSQLParser::Where_nullContext *ctx) = 0;

  virtual void enterWhere_in_list(MYSQLParser::Where_in_listContext *ctx) = 0;
  virtual void exitWhere_in_list(MYSQLParser::Where_in_listContext *ctx) = 0;

  virtual void enterWhere_in_select(MYSQLParser::Where_in_selectContext *ctx) = 0;
  virtual void exitWhere_in_select(MYSQLParser::Where_in_selectContext *ctx) = 0;

  virtual void enterWhere_like_string(MYSQLParser::Where_like_stringContext *ctx) = 0;
  virtual void exitWhere_like_string(MYSQLParser::Where_like_stringContext *ctx) = 0;

  virtual void enterColumn(MYSQLParser::ColumnContext *ctx) = 0;
  virtual void exitColumn(MYSQLParser::ColumnContext *ctx) = 0;

  virtual void enterExpression(MYSQLParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(MYSQLParser::ExpressionContext *ctx) = 0;

  virtual void enterSet_clause(MYSQLParser::Set_clauseContext *ctx) = 0;
  virtual void exitSet_clause(MYSQLParser::Set_clauseContext *ctx) = 0;

  virtual void enterSelectors(MYSQLParser::SelectorsContext *ctx) = 0;
  virtual void exitSelectors(MYSQLParser::SelectorsContext *ctx) = 0;

  virtual void enterSelector(MYSQLParser::SelectorContext *ctx) = 0;
  virtual void exitSelector(MYSQLParser::SelectorContext *ctx) = 0;

  virtual void enterIdentifiers(MYSQLParser::IdentifiersContext *ctx) = 0;
  virtual void exitIdentifiers(MYSQLParser::IdentifiersContext *ctx) = 0;

  virtual void enterOperator_(MYSQLParser::Operator_Context *ctx) = 0;
  virtual void exitOperator_(MYSQLParser::Operator_Context *ctx) = 0;

  virtual void enterAggregator(MYSQLParser::AggregatorContext *ctx) = 0;
  virtual void exitAggregator(MYSQLParser::AggregatorContext *ctx) = 0;


};

