#include "SystemVisitor.h"

#include <float.h>

namespace dbtrain_mysql {

SystemVisitor::SystemVisitor(Instance *pDB) : _pDB{pDB} { assert(_pDB); }

// void SystemVisitor::init(){
// get the dblist
// TODO: load db list
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
antlrcpp::Any SystemVisitor::visitCreate_db(
    MYSQLParser::Create_dbContext *ctx) {
  if (!ctx->Identifier()) {
    // TODO: raise a identifier null error
  }

  std::string dbname = ctx->Identifier()->toString();

  if (_dbs.find(dbname) != _dbs.end()) {  // not unique
    assert(0);
  }

  std::cout << "CREATE_DATABASE(" << dbname << ");" << std::endl;
  // add to local list
  _dbs[dbname] = new Instance();

  return 1;
}

antlrcpp::Any SystemVisitor::visitDrop_db(MYSQLParser::Drop_dbContext *ctx) {
  if (!ctx->Identifier()) {
    // TODO: raise a identifier null error
  }

  std::string dbname = ctx->Identifier()->toString();

  auto tmp = _dbs.find(dbname);
  if (tmp == _dbs.end()) {  // db not exist
    assert(0);
  }

  std::cout << "DROP_DATABASE(" << dbname << ");" << std::endl;

  if (this->current_db_name ==
      dbname) {  // drop the currently used db, change currernt name to null
    this->current_db_name = "";
    if (this->table_list != nullptr) {
      delete this->table_list;
    }
    this->table_list = nullptr;
  }
  // delete from local list
  delete (*tmp).second;
  _dbs.erase(tmp);
  return 1;
}

antlrcpp::Any SystemVisitor::visitShow_dbs(MYSQLParser::Show_dbsContext *ctx) {
  // TODO: ask for a list from backend
  printf("******database list******\n");
  auto it = _dbs.begin();

  while (it != _dbs.end()) {
    std::cout << "\t" << (*it).first << std::endl;
    it++;
  }
  std::cout << "*****************" << std::endl;
  return 1;
}
antlrcpp::Any SystemVisitor::visitUse_db(MYSQLParser::Use_dbContext *ctx) {
  if (!ctx->Identifier()) {
    // TODO: raise a identifier null error
  }
  std::string dbname = ctx->Identifier()->toString();

  this->current_db_name = dbname;

  auto tmp = _dbs.find(dbname);
  if (tmp == _dbs.end()) {  // db not exist
    assert(0);
  }

  std::cout << "USE_DATABASE(" << dbname << ");" << std::endl;
  return 1;
}
antlrcpp::Any SystemVisitor::visitShow_tables(
    MYSQLParser::Show_tablesContext *ctx) {
  std::cout << "table list\n";
  // get table list
  return _pDB->GetTableNames();
}

antlrcpp::Any SystemVisitor::visitShow_indexes(
    MYSQLParser::Show_indexesContext *ctx) {
  // TODO: wtf is show indexes
  return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitLoad_data(
    MYSQLParser::Load_dataContext *ctx) {
  if (ctx->String() == nullptr) {
    // TODO: raise miss error
    assert(0);
  }

  std::string path = ctx->String()->toString();

  if (ctx->Identifier() == nullptr) {
    // TODO: raise miss error
    assert(0);
  }

  FILE *file = fopen(path.data(), "r");

  if (file == nullptr) {
    // TODO: raise path error
  }

  // TODO: select table by name

  delete file;
  return 1;
}

antlrcpp::Any SystemVisitor::visitDump_data(
    MYSQLParser::Dump_dataContext *ctx) {
  return visitChildren(ctx);
  if (ctx->String() == nullptr) {
    // TODO: raise miss error
    assert(0);
  }

  std::string path = ctx->String()->toString();

  if (ctx->Identifier() == nullptr) {
    // TODO: raise miss error
    assert(0);
  }

  FILE *file = fopen(path.data(), "w");
  if (file == nullptr) {
    // TODO: raise path error
  }
  delete file;
  return 1;
}

antlrcpp::Any SystemVisitor::visitCreate_table(
    MYSQLParser::Create_tableContext *ctx) {
  ctx->field_list()->accept(this);
  std::string table_name = ctx->Identifier()->toString();
  std::cout << table_name << " ";

  // bool flag = _pDB->CreateTable(table_name, Schema(_current_field_list));

  _current_field_list.clear();
  // add to table list
  return 1;
}

antlrcpp::Any SystemVisitor::visitNormal_field(
    MYSQLParser::Normal_fieldContext *ctx) {
  if (ctx->Identifier() == nullptr) {
    assert(0);
  }
  std::string field_name = ctx->Identifier()->toString();
  std::string type = ctx->type_()->accept(this);
  // TODO: cha chong
  FieldType tmp = FieldType::NULL_TYPE;
  std::cout << type << " ";
  bool flag = (ctx->Null() != nullptr);
  // TODO: column need a null flag
  if (type == "INT") {
    _current_field_list.push_back(Column(field_name, FieldType::INT_TYPE));
  } else if (type == "FLOAT") {
    _current_field_list.push_back(Column(field_name, FieldType::FLOAT_TYPE));
  } else {
    _current_field_list.push_back(
        Column(field_name, FieldType::CHAR_TYPE,
               stoi(ctx->type_()->Integer()->toString())));
  }

  return 1;
}
antlrcpp::Any SystemVisitor::visitPrimary_key_field(
    MYSQLParser::Primary_key_fieldContext *ctx) {
  std::vector<std::string> tmp = ctx->identifiers()->accept(this);
  for (int i = 0; i < tmp.size(); i++) {
    std::cout << tmp[i];
  }
  std::cout << std::endl;
  // TODO: set primary keys;
  return true;
}
antlrcpp::Any SystemVisitor::visitForeign_key_field(
    MYSQLParser::Foreign_key_fieldContext *ctx) {}
antlrcpp::Any SystemVisitor::visitType_(MYSQLParser::Type_Context *ctx) {
  return ctx->getText();
}
antlrcpp::Any SystemVisitor::visitDrop_table(
    MYSQLParser::Drop_tableContext *ctx) {
  if (ctx->Identifier() == nullptr) {
    assert(0);
  }
  std::string table_name = ctx->Identifier()->toString();
  // drop table
  return _pDB->DropTable(table_name);
}
antlrcpp::Any SystemVisitor::visitInsert_into_table(
    MYSQLParser::Insert_into_tableContext *ctx) {
  if (ctx->Identifier() == nullptr) {
    assert(0);
  }
  std::string table_name = ctx->Identifier()->toString();
  // open table
  ctx->value_lists()->accept(this);
  std::vector<std::vector<String>> current_value_lists = ctx->accept(this);
  for (auto it = current_value_lists.begin(); it != current_value_lists.end();
       it++) {
    std::cout << (*it)[0] << " " << (*it)[1] << std::endl;
    _pDB->Insert(table_name, (*it));
  }

  return 1;
}
antlrcpp::Any SystemVisitor::visitValue_lists(
    MYSQLParser::Value_listsContext *ctx) {
  std::vector<std::vector<String>> tmp;
  for (auto it = ctx->value_list().begin(); it != ctx->value_list().end();
       it++) {
    tmp.push_back((*it)->accept(this));
  }
  return tmp;
}
antlrcpp::Any SystemVisitor::visitValue_list(
    MYSQLParser::Value_listContext *ctx) {
  std::vector<String> tmp;
  for (auto it = ctx->value().begin(); it != ctx->value().end(); it++) {
    tmp.push_back((*it)->getText());
  }
  return tmp;
}

antlrcpp::Any SystemVisitor::visitDescribe_table(
    MYSQLParser::Describe_tableContext *ctx) {
  std::string tableName = ctx->Identifier()->toString();
  // TODO: describe_table function
  return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitDelete_from_table(
    MYSQLParser::Delete_from_tableContext *ctx) {
  std::string tableName = ctx->Identifier()->toString();
  return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitSelect_table(
    MYSQLParser::Select_tableContext *ctx) {
  std::vector<String> current_table_names = ctx->identifiers()->accept(this);
  ctx->selectors()->accept(this);
  // if(ctx->where_and_clause() != nullptr){
  //     ctx->where_and_clause()->accept(this);
  // }
  std::vector<Record *> records;
  for (auto table_name_it = current_table_names.begin();
       table_name_it != current_table_names.end(); table_name_it++) {
    std::vector<PageSlotID> pageSlotID;
    for (auto selector_it = _current_selectors.begin();
         selector_it != _current_selectors.end(); selector_it++) {
      Condition *cond = nullptr;
      std::vector<Condition *> iCond;
      if ((*selector_it) == "*") {
        cond = new AllCondition();
      }
      // TODO: wait for backend

      // for(auto it = _pDB->Search((*table_name_it), cond, iCond).begin(); it
      // != _pDB->Search((*table_name_it), cond, iCond).end(); it ++){
      //     std::cout << (*it).first << " " << (*it).second << std::endl;

      //      records.push_back(_pDB->GetRecord((*table_name_it), (*it)));
      // }
      if (cond != nullptr) {
        delete cond;
        cond = nullptr;
      }
    }
  }
  _current_selectors.clear();
  return records;
}
antlrcpp::Any SystemVisitor::visitSelectors(
    MYSQLParser::SelectorsContext *ctx) {
  std::string text = ctx->getText();
  if (text == "*") {
    _current_selectors.push_back("*");
    return 1;
  } else {
    for (int i = 0; i < ctx->selector().size(); i++) {
      if (ctx->selector()[i]->aggregator() != nullptr) {
        Col col = ctx->selector()[i]->column()->accept(this);
        _current_selectors.push_back(
            ctx->selector()[i]->aggregator()->getText() + " " + col.first +
            " " + col.second);
        std::cout << _current_selectors.back() << std::endl;
      } else if (ctx->selector()[i]->Count() != nullptr) {
        _current_selectors.push_back("countstar");
      }
    }
  }
  return 1;
}
antlrcpp::Any SystemVisitor::visitIdentifiers(
    MYSQLParser::IdentifiersContext *ctx) {
  std::vector<String> ids;
  for (int i = 0; i < ctx->Identifier().size(); i++) {
    ids.push_back(ctx->Identifier()[i]->toString());
  }
  return ids;
}
antlrcpp::Any SystemVisitor::visitColumn(MYSQLParser::ColumnContext *ctx) {
  return Col(ctx->Identifier()[0]->toString(),
             ctx->Identifier()[1]->toString());
}

antlrcpp::Any SystemVisitor::visitWhere_and_clause(
    MYSQLParser::Where_and_clauseContext *ctx) {
  std::cout << "1" << std::endl;
  std::map<Col, std::vector<String>> where_clauses;
  for (auto it = ctx->where_clause().begin(); it != ctx->where_clause().end();
       it++) {
    std::cout << "2" << std::endl;
    std::pair<Col, std::string> p = (*it)->accept(this);
    std::cout << p.first.first + " " + p.first.second << " : " << p.second
              << std::endl;
    Col column = p.first;
    if (where_clauses.find(column) == where_clauses.end()) {
      where_clauses[column] = std::vector<std::string>();
    }
    where_clauses[column].push_back(p.second);
  }
  return where_clauses;
}
antlrcpp::Any SystemVisitor::visitWhere_operator_expression(
    MYSQLParser::Where_operator_expressionContext *ctx) {
  std::cout << "where op exp" << std::endl;
  Col column = ctx->column()->accept(this);
  // TODO:
  return std::make_pair(
      column, ctx->operator_()->getText() + " " + ctx->expression()->getText());
}

antlrcpp::Any SystemVisitor::visitWhere_operator_select(
    MYSQLParser::Where_operator_selectContext *ctx) {
  std::cout << "where op sel" << std::endl;
  // TODO: WAIT BACKEND
  // std::vector<Record*> select_record =
  // ctx->select_table()->accept(this);//return vector of record deriectly
  // process the records and get to an accurate value
  Col column = ctx->column()->accept(this);
  return std::make_pair(column, "op state table");
}

antlrcpp::Any SystemVisitor::visitWhere_null(
    MYSQLParser::Where_nullContext *ctx) {
  std::cout << "where null" << std::endl;
  Col column = ctx->column()->accept(this);
  if (!ctx->getText().find("IS NOT")) {  // should use npos. maybe
    return std::make_pair(column, "IS NOT NULL");
  } else {
    return std::make_pair(column, "IS NULL");
  }
}

antlrcpp::Any SystemVisitor::visitWhere_in_list(
    MYSQLParser::Where_in_listContext *ctx) {
  std::cout << "where in list" << std::endl;
  Col column = ctx->column()->accept(this);
  std::vector<String> value_list = ctx->value_list()->accept(this);
  std::string s = "in ";
  for (std::string str : value_list) {
    s += str;
  }
  return std::make_pair(column, s);
}

antlrcpp::Any SystemVisitor::visitWhere_in_select(
    MYSQLParser::Where_in_selectContext *ctx) {
  std::cout << "where in select" << std::endl;
  Col column = ctx->column()->accept(this);
  std::vector<Record *> select_record =
      ctx->select_table()->accept(this);  // return vector of record deriectly
  return std::make_pair(column, "in state table");
}

antlrcpp::Any SystemVisitor::visitWhere_like_string(
    MYSQLParser::Where_like_stringContext *ctx) {
  std::cout << "where like" << std::endl;
  Col column = ctx->column()->accept(this);
  return std::make_pair(column, "like " + ctx->String()->getText());
}

antlrcpp::Any SystemVisitor::visitAlter_table_rename(
    MYSQLParser::Alter_table_renameContext *ctx) {
  std::string oldName = ctx->Identifier()[0]->getText();
  std::string newName = ctx->Identifier()[1]->getText();
  // TODO: rename
}
antlrcpp::Any SystemVisitor::visitAlter_table_add_pk(
    MYSQLParser::Alter_table_add_pkContext *ctx) {
  std::string tablename = ctx->Identifier()[0]->getText();
  std::vector<std::string> pks = ctx->identifiers()->accept(this);
}
antlrcpp::Any SystemVisitor::visitAlter_table_drop_pk(
    MYSQLParser::Alter_table_drop_pkContext *ctx) {
  std::string tablename = ctx->Identifier()[0].getText();
  std::vector<std::string> pks = ctx->identifiers()->accept(this);
}
antlrcpp::Any SystemVisitor::visitAlter_table_add_foreign_key(
    MYSQLParser::Alter_table_add_foreign_keyContext *ctx) {
  std::string tablename = ctx->Identifier()[0]->getText();
  std::string constriantName = ctx->Identifier()[1]->getText();
  std::string refTableName = ctx->Identifier()[2]->getText();
  std::vector<std::string> pks = ctx->identifiers()[0]->accept(this);
  std::vector<std::string> refpks = ctx->identifiers()[1]->accept(this);
}
antlrcpp::Any SystemVisitor::visitAlter_table_drop_foreign_key(
    MYSQLParser::Alter_table_drop_foreign_keyContext *ctx) {
  std::string tablename = ctx->Identifier()[0]->getText();
  std::string reftableName = ctx->Identifier()[1]->getText();
}

}  // namespace dbtrain_mysql