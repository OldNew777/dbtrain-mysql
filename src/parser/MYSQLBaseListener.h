
// Generated from MYSQL.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "MYSQLListener.h"


/**
 * This class provides an empty implementation of MYSQLListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  MYSQLBaseListener : public MYSQLListener {
public:

  virtual void enterProgram(MYSQLParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(MYSQLParser::ProgramContext * /*ctx*/) override { }

  virtual void enterStatement(MYSQLParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(MYSQLParser::StatementContext * /*ctx*/) override { }

  virtual void enterCreate_db(MYSQLParser::Create_dbContext * /*ctx*/) override { }
  virtual void exitCreate_db(MYSQLParser::Create_dbContext * /*ctx*/) override { }

  virtual void enterDrop_db(MYSQLParser::Drop_dbContext * /*ctx*/) override { }
  virtual void exitDrop_db(MYSQLParser::Drop_dbContext * /*ctx*/) override { }

  virtual void enterShow_dbs(MYSQLParser::Show_dbsContext * /*ctx*/) override { }
  virtual void exitShow_dbs(MYSQLParser::Show_dbsContext * /*ctx*/) override { }

  virtual void enterUse_db(MYSQLParser::Use_dbContext * /*ctx*/) override { }
  virtual void exitUse_db(MYSQLParser::Use_dbContext * /*ctx*/) override { }

  virtual void enterRename_db(MYSQLParser::Rename_dbContext * /*ctx*/) override { }
  virtual void exitRename_db(MYSQLParser::Rename_dbContext * /*ctx*/) override { }

  virtual void enterShow_tables(MYSQLParser::Show_tablesContext * /*ctx*/) override { }
  virtual void exitShow_tables(MYSQLParser::Show_tablesContext * /*ctx*/) override { }

  virtual void enterShow_indexes(MYSQLParser::Show_indexesContext * /*ctx*/) override { }
  virtual void exitShow_indexes(MYSQLParser::Show_indexesContext * /*ctx*/) override { }

  virtual void enterLoad_data(MYSQLParser::Load_dataContext * /*ctx*/) override { }
  virtual void exitLoad_data(MYSQLParser::Load_dataContext * /*ctx*/) override { }

  virtual void enterDump_data(MYSQLParser::Dump_dataContext * /*ctx*/) override { }
  virtual void exitDump_data(MYSQLParser::Dump_dataContext * /*ctx*/) override { }

  virtual void enterCreate_table(MYSQLParser::Create_tableContext * /*ctx*/) override { }
  virtual void exitCreate_table(MYSQLParser::Create_tableContext * /*ctx*/) override { }

  virtual void enterDrop_table(MYSQLParser::Drop_tableContext * /*ctx*/) override { }
  virtual void exitDrop_table(MYSQLParser::Drop_tableContext * /*ctx*/) override { }

  virtual void enterDescribe_table(MYSQLParser::Describe_tableContext * /*ctx*/) override { }
  virtual void exitDescribe_table(MYSQLParser::Describe_tableContext * /*ctx*/) override { }

  virtual void enterDescribe_shadow_table(MYSQLParser::Describe_shadow_tableContext * /*ctx*/) override { }
  virtual void exitDescribe_shadow_table(MYSQLParser::Describe_shadow_tableContext * /*ctx*/) override { }

  virtual void enterInsert_into_table(MYSQLParser::Insert_into_tableContext * /*ctx*/) override { }
  virtual void exitInsert_into_table(MYSQLParser::Insert_into_tableContext * /*ctx*/) override { }

  virtual void enterDelete_from_table(MYSQLParser::Delete_from_tableContext * /*ctx*/) override { }
  virtual void exitDelete_from_table(MYSQLParser::Delete_from_tableContext * /*ctx*/) override { }

  virtual void enterUpdate_table(MYSQLParser::Update_tableContext * /*ctx*/) override { }
  virtual void exitUpdate_table(MYSQLParser::Update_tableContext * /*ctx*/) override { }

  virtual void enterSelect_table_(MYSQLParser::Select_table_Context * /*ctx*/) override { }
  virtual void exitSelect_table_(MYSQLParser::Select_table_Context * /*ctx*/) override { }

  virtual void enterSelect_table(MYSQLParser::Select_tableContext * /*ctx*/) override { }
  virtual void exitSelect_table(MYSQLParser::Select_tableContext * /*ctx*/) override { }

  virtual void enterAlter_add_index(MYSQLParser::Alter_add_indexContext * /*ctx*/) override { }
  virtual void exitAlter_add_index(MYSQLParser::Alter_add_indexContext * /*ctx*/) override { }

  virtual void enterAlter_drop_index(MYSQLParser::Alter_drop_indexContext * /*ctx*/) override { }
  virtual void exitAlter_drop_index(MYSQLParser::Alter_drop_indexContext * /*ctx*/) override { }

  virtual void enterAlter_table_drop_pk(MYSQLParser::Alter_table_drop_pkContext * /*ctx*/) override { }
  virtual void exitAlter_table_drop_pk(MYSQLParser::Alter_table_drop_pkContext * /*ctx*/) override { }

  virtual void enterAlter_table_drop_foreign_key(MYSQLParser::Alter_table_drop_foreign_keyContext * /*ctx*/) override { }
  virtual void exitAlter_table_drop_foreign_key(MYSQLParser::Alter_table_drop_foreign_keyContext * /*ctx*/) override { }

  virtual void enterAlter_table_add_pk(MYSQLParser::Alter_table_add_pkContext * /*ctx*/) override { }
  virtual void exitAlter_table_add_pk(MYSQLParser::Alter_table_add_pkContext * /*ctx*/) override { }

  virtual void enterAlter_table_add_foreign_key(MYSQLParser::Alter_table_add_foreign_keyContext * /*ctx*/) override { }
  virtual void exitAlter_table_add_foreign_key(MYSQLParser::Alter_table_add_foreign_keyContext * /*ctx*/) override { }

  virtual void enterAlter_table_add_unique(MYSQLParser::Alter_table_add_uniqueContext * /*ctx*/) override { }
  virtual void exitAlter_table_add_unique(MYSQLParser::Alter_table_add_uniqueContext * /*ctx*/) override { }

  virtual void enterAlter_table_drop_unique(MYSQLParser::Alter_table_drop_uniqueContext * /*ctx*/) override { }
  virtual void exitAlter_table_drop_unique(MYSQLParser::Alter_table_drop_uniqueContext * /*ctx*/) override { }

  virtual void enterAlter_table_rename(MYSQLParser::Alter_table_renameContext * /*ctx*/) override { }
  virtual void exitAlter_table_rename(MYSQLParser::Alter_table_renameContext * /*ctx*/) override { }

  virtual void enterField_list(MYSQLParser::Field_listContext * /*ctx*/) override { }
  virtual void exitField_list(MYSQLParser::Field_listContext * /*ctx*/) override { }

  virtual void enterNormal_field(MYSQLParser::Normal_fieldContext * /*ctx*/) override { }
  virtual void exitNormal_field(MYSQLParser::Normal_fieldContext * /*ctx*/) override { }

  virtual void enterPrimary_key_field(MYSQLParser::Primary_key_fieldContext * /*ctx*/) override { }
  virtual void exitPrimary_key_field(MYSQLParser::Primary_key_fieldContext * /*ctx*/) override { }

  virtual void enterForeign_key_field(MYSQLParser::Foreign_key_fieldContext * /*ctx*/) override { }
  virtual void exitForeign_key_field(MYSQLParser::Foreign_key_fieldContext * /*ctx*/) override { }

  virtual void enterType_(MYSQLParser::Type_Context * /*ctx*/) override { }
  virtual void exitType_(MYSQLParser::Type_Context * /*ctx*/) override { }

  virtual void enterValue_lists(MYSQLParser::Value_listsContext * /*ctx*/) override { }
  virtual void exitValue_lists(MYSQLParser::Value_listsContext * /*ctx*/) override { }

  virtual void enterValue_list(MYSQLParser::Value_listContext * /*ctx*/) override { }
  virtual void exitValue_list(MYSQLParser::Value_listContext * /*ctx*/) override { }

  virtual void enterValue(MYSQLParser::ValueContext * /*ctx*/) override { }
  virtual void exitValue(MYSQLParser::ValueContext * /*ctx*/) override { }

  virtual void enterWhere_and_clause(MYSQLParser::Where_and_clauseContext * /*ctx*/) override { }
  virtual void exitWhere_and_clause(MYSQLParser::Where_and_clauseContext * /*ctx*/) override { }

  virtual void enterWhere_operator_expression(MYSQLParser::Where_operator_expressionContext * /*ctx*/) override { }
  virtual void exitWhere_operator_expression(MYSQLParser::Where_operator_expressionContext * /*ctx*/) override { }

  virtual void enterWhere_operator_select(MYSQLParser::Where_operator_selectContext * /*ctx*/) override { }
  virtual void exitWhere_operator_select(MYSQLParser::Where_operator_selectContext * /*ctx*/) override { }

  virtual void enterWhere_null(MYSQLParser::Where_nullContext * /*ctx*/) override { }
  virtual void exitWhere_null(MYSQLParser::Where_nullContext * /*ctx*/) override { }

  virtual void enterWhere_in_list(MYSQLParser::Where_in_listContext * /*ctx*/) override { }
  virtual void exitWhere_in_list(MYSQLParser::Where_in_listContext * /*ctx*/) override { }

  virtual void enterWhere_in_select(MYSQLParser::Where_in_selectContext * /*ctx*/) override { }
  virtual void exitWhere_in_select(MYSQLParser::Where_in_selectContext * /*ctx*/) override { }

  virtual void enterWhere_like_string(MYSQLParser::Where_like_stringContext * /*ctx*/) override { }
  virtual void exitWhere_like_string(MYSQLParser::Where_like_stringContext * /*ctx*/) override { }

  virtual void enterColumn(MYSQLParser::ColumnContext * /*ctx*/) override { }
  virtual void exitColumn(MYSQLParser::ColumnContext * /*ctx*/) override { }

  virtual void enterExpression(MYSQLParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(MYSQLParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterSet_clause(MYSQLParser::Set_clauseContext * /*ctx*/) override { }
  virtual void exitSet_clause(MYSQLParser::Set_clauseContext * /*ctx*/) override { }

  virtual void enterSelectors(MYSQLParser::SelectorsContext * /*ctx*/) override { }
  virtual void exitSelectors(MYSQLParser::SelectorsContext * /*ctx*/) override { }

  virtual void enterSelector(MYSQLParser::SelectorContext * /*ctx*/) override { }
  virtual void exitSelector(MYSQLParser::SelectorContext * /*ctx*/) override { }

  virtual void enterIdentifiers(MYSQLParser::IdentifiersContext * /*ctx*/) override { }
  virtual void exitIdentifiers(MYSQLParser::IdentifiersContext * /*ctx*/) override { }

  virtual void enterOperator_(MYSQLParser::Operator_Context * /*ctx*/) override { }
  virtual void exitOperator_(MYSQLParser::Operator_Context * /*ctx*/) override { }

  virtual void enterAggregator(MYSQLParser::AggregatorContext * /*ctx*/) override { }
  virtual void exitAggregator(MYSQLParser::AggregatorContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

