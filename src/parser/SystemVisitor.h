#ifndef DBTRAIN_MYSQL_SYSTEM_VISITOR_H
#define DBTRAIN_MYSQL_SYSTEM_VISITOR_H

#include "MYSQLBaseVisitor.h"
#include "antlr4-runtime.h"
#include "system/instance.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include "util.h"
#include "../system/instance.h"

namespace dbtrain_mysql {

class SystemVisitor : public MYSQLBaseVisitor {
 private:
  Instance* _pDB;
  std::vector<TableHead>* _current_table_head = nullptr;
  std::vector<std::vector<Data*>*>* _current_value_lists = nullptr; 
  std::vector<Data*>* _tmp_value_list = nullptr;
  std::map<std::string, Instance*> _dbs;

 public:
  std::string current_db_name = "";
  std::list<std::string>* db_list;
  std::list<std::string>* table_list = nullptr;

  SystemVisitor(Instance* pDB);
  
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
  virtual antlrcpp::Any visitField_list(MYSQLParser::Field_listContext *ctx) override;
  virtual antlrcpp::Any visitNormal_field(MYSQLParser::Normal_fieldContext *ctx) override;
  virtual antlrcpp::Any visitValue_list(MYSQLParser::Value_listContext *ctx);
  virtual antlrcpp::Any visitValue(MYSQLParser::ValueContext *ctx) override;
  virtual antlrcpp::Any visitWhere_and_clause(MYSQLParser::Where_and_clauseContext *ctx) override;
  virtual antlrcpp::Any visitWhere_operator_expression(MYSQLParser::Where_operator_expressionContext *ctx) override;

};

}  // namespace dbtrain_mysql

#endif