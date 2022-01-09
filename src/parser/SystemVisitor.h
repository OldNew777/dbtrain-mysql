#ifndef DBTRAIN_MYSQL_SYSTEM_VISITOR_H
#define DBTRAIN_MYSQL_SYSTEM_VISITOR_H

#include <string.h>

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>

#include "MYSQLBaseVisitor.h"
#include "antlr4-runtime.h"
#include "condition/conditions.h"
#include "system/instance.h"

namespace dbtrain_mysql {

class SystemVisitor : public MYSQLBaseVisitor {
 protected:
  Instance *_pDB;

 public:
  SystemVisitor(Instance *pDB);

  virtual antlrcpp::Any visitProgram(
      MYSQLParser::ProgramContext *context) override;

  virtual antlrcpp::Any visitStatement(
      MYSQLParser::StatementContext *context) override;

  virtual antlrcpp::Any visitCreate_db(
      MYSQLParser::Create_dbContext *context) override;

  virtual antlrcpp::Any visitDrop_db(
      MYSQLParser::Drop_dbContext *context) override;

  virtual antlrcpp::Any visitShow_dbs(
      MYSQLParser::Show_dbsContext *context) override;

  virtual antlrcpp::Any visitUse_db(
      MYSQLParser::Use_dbContext *context) override;

  virtual antlrcpp::Any visitRename_db(
      MYSQLParser::Rename_dbContext *context) override;

  virtual antlrcpp::Any visitShow_tables(
      MYSQLParser::Show_tablesContext *context) override;

  virtual antlrcpp::Any visitShow_indexes(
      MYSQLParser::Show_indexesContext *context) override;

  virtual antlrcpp::Any visitLoad_data(
      MYSQLParser::Load_dataContext *context) override;

  virtual antlrcpp::Any visitDump_data(
      MYSQLParser::Dump_dataContext *context) override;

  virtual antlrcpp::Any visitCreate_table(
      MYSQLParser::Create_tableContext *context) override;

  virtual antlrcpp::Any visitDrop_table(
      MYSQLParser::Drop_tableContext *context) override;

  virtual antlrcpp::Any visitDescribe_table(
      MYSQLParser::Describe_tableContext *context) override;
  virtual antlrcpp::Any visitDescribe_shadow_table(
      MYSQLParser::Describe_shadow_tableContext *context) override;
  virtual antlrcpp::Any visitInsert_into_table(
      MYSQLParser::Insert_into_tableContext *context) override;

  virtual antlrcpp::Any visitDelete_from_table(
      MYSQLParser::Delete_from_tableContext *context) override;

  virtual antlrcpp::Any visitUpdate_table(
      MYSQLParser::Update_tableContext *context) override;

  virtual antlrcpp::Any visitSelect_table_(
      MYSQLParser::Select_table_Context *context) override;

  virtual antlrcpp::Any visitSelect_table(
      MYSQLParser::Select_tableContext *context) override;

  virtual antlrcpp::Any visitAlter_add_index(
      MYSQLParser::Alter_add_indexContext *context) override;

  virtual antlrcpp::Any visitAlter_drop_index(
      MYSQLParser::Alter_drop_indexContext *context) override;

  virtual antlrcpp::Any visitAlter_table_drop_pk(
      MYSQLParser::Alter_table_drop_pkContext *context) override;

  virtual antlrcpp::Any visitAlter_table_drop_foreign_key(
      MYSQLParser::Alter_table_drop_foreign_keyContext *context) override;

  virtual antlrcpp::Any visitAlter_table_add_pk(
      MYSQLParser::Alter_table_add_pkContext *context) override;

  virtual antlrcpp::Any visitAlter_table_add_foreign_key(
      MYSQLParser::Alter_table_add_foreign_keyContext *context) override;

  virtual antlrcpp::Any visitAlter_table_add_unique(
      MYSQLParser::Alter_table_add_uniqueContext *context) override;

  virtual antlrcpp::Any visitAlter_table_drop_unique(
      MYSQLParser::Alter_table_drop_uniqueContext *context) override;

  virtual antlrcpp::Any visitAlter_table_rename(
      MYSQLParser::Alter_table_renameContext *context) override;

  virtual antlrcpp::Any visitField_list(
      MYSQLParser::Field_listContext *context) override;

  virtual antlrcpp::Any visitNormal_field(
      MYSQLParser::Normal_fieldContext *context) override;

  virtual antlrcpp::Any visitPrimary_key_field(
      MYSQLParser::Primary_key_fieldContext *context) override;

  virtual antlrcpp::Any visitForeign_key_field(
      MYSQLParser::Foreign_key_fieldContext *context) override;

  virtual antlrcpp::Any visitType_(MYSQLParser::Type_Context *context) override;

  virtual antlrcpp::Any visitValue_lists(
      MYSQLParser::Value_listsContext *context) override;

  virtual antlrcpp::Any visitValue_list(
      MYSQLParser::Value_listContext *context) override;

  virtual antlrcpp::Any visitValue(MYSQLParser::ValueContext *context) override;

  virtual antlrcpp::Any visitWhere_and_clause(
      MYSQLParser::Where_and_clauseContext *context) override;

  virtual antlrcpp::Any visitWhere_operator_expression(
      MYSQLParser::Where_operator_expressionContext *context) override;

  virtual antlrcpp::Any visitWhere_operator_select(
      MYSQLParser::Where_operator_selectContext *context) override;

  virtual antlrcpp::Any visitWhere_null(
      MYSQLParser::Where_nullContext *context) override;

  virtual antlrcpp::Any visitWhere_in_list(
      MYSQLParser::Where_in_listContext *context) override;

  virtual antlrcpp::Any visitWhere_in_select(
      MYSQLParser::Where_in_selectContext *context) override;

  virtual antlrcpp::Any visitWhere_like_string(
      MYSQLParser::Where_like_stringContext *context) override;

  virtual antlrcpp::Any visitColumn(
      MYSQLParser::ColumnContext *context) override;

  virtual antlrcpp::Any visitExpression(
      MYSQLParser::ExpressionContext *context) override;

  virtual antlrcpp::Any visitSet_clause(
      MYSQLParser::Set_clauseContext *context) override;

  virtual antlrcpp::Any visitSelectors(
      MYSQLParser::SelectorsContext *context) override;

  virtual antlrcpp::Any visitSelector(
      MYSQLParser::SelectorContext *context) override;

  virtual antlrcpp::Any visitIdentifiers(
      MYSQLParser::IdentifiersContext *context) override;

  virtual antlrcpp::Any visitOperator_(
      MYSQLParser::Operator_Context *context) override;

  virtual antlrcpp::Any visitAggregator(
      MYSQLParser::AggregatorContext *context) override;
};

}  // namespace dbtrain_mysql

#endif