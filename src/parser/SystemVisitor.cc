#include "SystemVisitor.h"

#include <float.h>
#include <stdlib.h>

#include "condition/conditions.h"
#include "entity/schema.h"
#include "entity/table.h"
#include "exception/exceptions.h"
#include "field/fields.h"
#include "macros.h"
#include "record/fixed_record.h"
#include "record/transform.h"
#include "result/result.h"
#include "string.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

SystemVisitor::SystemVisitor(Instance *pDB) : _pDB{pDB} { assert(_pDB); }

antlrcpp::Any SystemVisitor::visitProgram(MYSQLParser::ProgramContext *ctx) {
  std::vector<Result *> iResVec;
  for (const auto &it : ctx->statement()) {
    if (it->Null() || it->Annotation()) continue;
    Result *res = it->accept(this);
    iResVec.push_back(res);
  }
  return iResVec;
}

antlrcpp::Any SystemVisitor::visitStatement(
    MYSQLParser::StatementContext *ctx) {
  Result *res = nullptr;
  if (ctx->db_statement())
    res = ctx->db_statement()->accept(this);
  else if (ctx->table_statement())
    res = ctx->table_statement()->accept(this);
  else if (ctx->io_statement())
    res = ctx->io_statement()->accept(this);
  else if (ctx->alter_statement())
    res = ctx->alter_statement()->accept(this);
  else {
    printf("%s\n", ctx->getText().c_str());
    throw CaseException();
  }
  return res;
}

antlrcpp::Any SystemVisitor::visitCreate_db(
    MYSQLParser::Create_dbContext *ctx) {
  String sDatabaseName = ctx->Identifier()->getText();
  int nSize = 0;
  try {
    _pDB->CreateDatabase(sDatabaseName);
    nSize = 1;
  } catch (std::exception &) {
  }
  Result *res = new MemResult({"Create Database"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(nSize));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitDrop_db(MYSQLParser::Drop_dbContext *ctx) {
  String sDatabaseName = ctx->Identifier()->getText();
  int nSize = 0;
  try {
    _pDB->DropDatabase(sDatabaseName);
    nSize = 1;
  } catch (std::exception &) {
  }
  Result *res = new MemResult({"Drop Database"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(nSize));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitShow_dbs(MYSQLParser::Show_dbsContext *ctx) {
  Result *res = new MemResult({"Show Databases"});
  // Add Some info
  for (const auto &sTableName : _pDB->GetDatabaseNames()) {
    FixedRecord *pRes =
        new FixedRecord(1, {FieldType::CHAR_TYPE}, {DATABASE_NAME_SIZE});
    pRes->SetField(0, new CharField(sTableName));
    res->PushBack(pRes);
  }
  return res;
}

antlrcpp::Any SystemVisitor::visitUse_db(MYSQLParser::Use_dbContext *ctx) {
  String sDatabaseName = ctx->Identifier()->getText();
  int nSize = 0;
  try {
    _pDB->UseDatabase(sDatabaseName);
    nSize = 1;
  } catch (std::exception &) {
  }
  Result *res = new MemResult({"Use Database"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(nSize));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitShow_tables(
    MYSQLParser::Show_tablesContext *ctx) {
  Result *res = new MemResult({"Show Tables"});
  // Add Some info
  for (const auto &sTableName : _pDB->GetTableNames()) {
    FixedRecord *pRes =
        new FixedRecord(1, {FieldType::CHAR_TYPE}, {TABLE_NAME_SIZE});
    pRes->SetField(0, new CharField(sTableName));
    res->PushBack(pRes);
  }
  return res;
}

antlrcpp::Any SystemVisitor::visitShow_indexes(
    MYSQLParser::Show_indexesContext *ctx) {
  Result *res = new MemResult(
      {"Table Name", "Column Name", "Column Type", "Column Size"});
  // Add Some info
  for (const auto &pRecord : _pDB->GetIndexInfos()) {
    res->PushBack(pRecord);
  }
  return res;
}

antlrcpp::Any SystemVisitor::visitLoad_data(
    MYSQLParser::Load_dataContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitDump_data(
    MYSQLParser::Dump_dataContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitCreate_table(
    MYSQLParser::Create_tableContext *ctx) {
  Size nSize = 0;
  try {
    Schema iSchema = ctx->field_list()->accept(this);
    String sTableName = ctx->Identifier()->getText();
    _pDB->CreateTable(sTableName, iSchema);
    nSize = 1;
  } catch (const std::exception &e) {
  }
  Result *res = new MemResult({"Create Table"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(nSize));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitDrop_table(
    MYSQLParser::Drop_tableContext *ctx) {
  String sTableName = ctx->Identifier()->getText();
  Size nSize = 0;
  try {
    _pDB->DropTable(sTableName);
    nSize = 1;
  } catch (const std::exception &e) {
  }
  Result *res = new MemResult({"Drop Table"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(nSize));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitDescribe_table(
    MYSQLParser::Describe_tableContext *ctx) {
  Result *res = new MemResult({"Column Name", "Column Type", "Column Size"});
  String sTableName = ctx->Identifier()->getText();
  try {
    for (const auto &pRecord : _pDB->GetTableInfos(sTableName))
      res->PushBack(pRecord);
  } catch (const std::exception &e) {
  }
  return res;
}

antlrcpp::Any SystemVisitor::visitInsert_into_table(
    MYSQLParser::Insert_into_tableContext *ctx) {
  std::vector<std::vector<Field *>> iValueListVec =
      ctx->value_lists()->accept(this);
  String sTableName = ctx->Identifier()->getText();
  int inserted = 0;
  try {
    for (const auto &iValueList : iValueListVec) {
      _pDB->Insert(sTableName, iValueList);
      ++inserted;
    }
  } catch (const std::exception &e) {
  }
  Result *res = new MemResult({"Insert"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(inserted));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitDelete_from_table(
    MYSQLParser::Delete_from_tableContext *ctx) {
  String sTableName = ctx->Identifier()->getText();
  std::map<String, std::vector<Condition *>> iMap =
      ctx->where_and_clause()->accept(this);
  assert(iMap.size() == 1);
  std::vector<Condition *> iIndexCond{};
  std::vector<Condition *> iOtherCond{};
  for (const auto &pCond : iMap[sTableName])
    if (pCond->GetType() == ConditionType::INDEX_TYPE)
      iIndexCond.push_back(pCond);
    else
      iOtherCond.push_back(pCond);
  Condition *pCond = nullptr;
  if (iOtherCond.size() > 0) pCond = new AndCondition(iOtherCond);

  Size nSize = 0;
  try {
    nSize = _pDB->Delete(sTableName, pCond, iIndexCond);
  } catch (const std::exception &e) {
  }
  // Clear Condition
  if (pCond) delete pCond;
  for (const auto &it : iIndexCond)
    if (it) delete it;

  Result *res = new MemResult({"Delete"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(nSize));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitUpdate_table(
    MYSQLParser::Update_tableContext *ctx) {
  String sTableName = ctx->Identifier()->getText();
  std::vector<std::pair<String, String>> iSetVec =
      ctx->set_clause()->accept(this);
  std::map<String, std::vector<Condition *>> iMap =
      ctx->where_and_clause()->accept(this);
  assert(iMap.size() == 1);
  std::vector<Transform> iTrans{};
  for (Size i = 0; i < iSetVec.size(); ++i) {
    FieldID nFieldID = _pDB->GetColID(sTableName, iSetVec[i].first);
    FieldType iType = _pDB->GetColType(sTableName, iSetVec[i].first);
    iTrans.push_back({nFieldID, iType, iSetVec[i].second});
  }
  std::vector<Condition *> iIndexCond{};
  std::vector<Condition *> iOtherCond{};
  for (const auto &pCond : iMap[sTableName])
    if (pCond->GetType() == ConditionType::INDEX_TYPE)
      iIndexCond.push_back(pCond);
    else
      iOtherCond.push_back(pCond);
  Condition *pCond = nullptr;
  if (iOtherCond.size() > 0) pCond = new AndCondition(iOtherCond);
  Size nSize = _pDB->Update(sTableName, pCond, iIndexCond, iTrans);
  // Clear Condition
  if (pCond) delete pCond;
  for (const auto &it : iIndexCond)
    if (it) delete it;

  Result *res = new MemResult({"Update"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(nSize));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitSelect_table_(
    MYSQLParser::Select_table_Context *ctx) {
  return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitSelect_table(
    MYSQLParser::Select_tableContext *ctx) {
  std::vector<String> iTableNameVec = ctx->identifiers()->accept(this);
  std::map<String, std::vector<PageSlotID>> iResultMap{};
  std::map<String, std::vector<Condition *>> iCondMap{};
  // Filter
  if (ctx->where_and_clause()) {
    std::map<String, std::vector<Condition *>> iTempMap =
        ctx->where_and_clause()->accept(this);
    iCondMap = iTempMap;
  }

  for (const auto &sTableName : iTableNameVec) {
    if (iCondMap.find(sTableName) == iCondMap.end())
      iResultMap[sTableName] = _pDB->Search(sTableName, nullptr, {});
    else {
      std::vector<Condition *> iIndexCond{};
      std::vector<Condition *> iOtherCond{};
      for (const auto &pCond : iCondMap[sTableName])
        if (pCond->GetType() == ConditionType::INDEX_TYPE)
          iIndexCond.push_back(pCond);
        else
          iOtherCond.push_back(pCond);
      Condition *pCond = nullptr;
      if (iOtherCond.size() > 0) pCond = new AndCondition(iOtherCond);
      iResultMap[sTableName] = _pDB->Search(sTableName, pCond, iIndexCond);
      if (pCond) delete pCond;
      for (const auto &it : iIndexCond)
        if (it) delete it;
    }
  }

  // Join
  bool bJoin = (iResultMap.size() > 1);
  std::vector<Condition *> iJoinConds = {};
  if (iCondMap.find("JOIN") != iCondMap.end()) {
    iJoinConds = iCondMap.find("JOIN")->second;
  }
  std::pair<std::vector<String>, std::vector<Record *>> iHeadDataPair{};
  if (bJoin) iHeadDataPair = _pDB->Join(iResultMap, iJoinConds);

  // Generate Result
  std::vector<PageSlotID> iData;
  if (!bJoin) {
    String sTableName = iTableNameVec[0];
    iData = iResultMap[sTableName];
    Result *pResult = new MemResult(_pDB->GetColumnNames(sTableName));
    for (const auto &it : iData)
      pResult->PushBack(_pDB->GetRecord(iTableNameVec[0], it));
    return pResult;
  } else {
    Result *pResult = new MemResult(iHeadDataPair.first);
    for (const auto &pRecord : iHeadDataPair.second) pResult->PushBack(pRecord);
    return pResult;
  }
}

antlrcpp::Any SystemVisitor::visitAlter_add_index(
    MYSQLParser::Alter_add_indexContext *ctx) {
  String sTableName = ctx->Identifier()->getText();
  std::vector<String> iColNameVec = ctx->identifiers()->accept(this);
  Size nSize = 0;
  for (const auto &sColName : iColNameVec) {
    try {
      _pDB->CreateIndex(sTableName, sColName);
      ++nSize;
    } catch (const std::exception &e) {
      // TODO
    }
  }
  Result *res = new MemResult({"Create Index"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(nSize));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitAlter_drop_index(
    MYSQLParser::Alter_drop_indexContext *ctx) {
  String sTableName = ctx->Identifier()->getText();
  std::vector<String> iColNameVec = ctx->identifiers()->accept(this);
  Size nSize = 0;
  for (const auto &sColName : iColNameVec) {
    try {
      _pDB->DropIndex(sTableName, sColName);
      ++nSize;
    } catch (const std::exception &e) {
      // TODO
    }
  }
  Result *res = new MemResult({"Drop Index"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(nSize));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitAlter_table_drop_pk(
    MYSQLParser::Alter_table_drop_pkContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitAlter_table_drop_foreign_key(
    MYSQLParser::Alter_table_drop_foreign_keyContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitAlter_table_add_pk(
    MYSQLParser::Alter_table_add_pkContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitAlter_table_add_foreign_key(
    MYSQLParser::Alter_table_add_foreign_keyContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitAlter_table_add_unique(
    MYSQLParser::Alter_table_add_uniqueContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitAlter_table_rename(
    MYSQLParser::Alter_table_renameContext *ctx) {
  String sOldTableName = ctx->Identifier()[0]->getText();
  String sNewTableName = ctx->Identifier()[1]->getText();
  int nSize = 0;
  try {
    _pDB->RenameTable(sOldTableName, sNewTableName);
    nSize = 1;
  } catch (std::exception &) {
  }
  Result *res = new MemResult({"Rename Table"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(nSize));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitField_list(
    MYSQLParser::Field_listContext *ctx) {
  std::vector<Column> iColVec;
  for (const auto &it : ctx->field()) {
    iColVec.push_back(it->accept(this));
  }
  return Schema(iColVec);
}

antlrcpp::Any SystemVisitor::visitNormal_field(
    MYSQLParser::Normal_fieldContext *ctx) {
  String sType = ctx->type_()->getText();
  // TODO : add NULL/PRIMARY KEY/DEFAULT
  if (sType == "INT") {
    return Column(ctx->Identifier()->getText(), FieldType::INT_TYPE);
  } else if (sType == "FLOAT") {
    return Column(ctx->Identifier()->getText(), FieldType::FLOAT_TYPE);
  } else {
    int nSize = atoi(ctx->type_()->Integer()->getText().c_str());
    return Column(ctx->Identifier()->getText(), FieldType::CHAR_TYPE, nSize);
  }
}

antlrcpp::Any SystemVisitor::visitPrimary_key_field(
    MYSQLParser::Primary_key_fieldContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitForeign_key_field(
    MYSQLParser::Foreign_key_fieldContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitType_(MYSQLParser::Type_Context *ctx) {
  return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitValue_lists(
    MYSQLParser::Value_listsContext *ctx) {
  std::vector<std::vector<Field *>> iValueListVec;
  for (const auto &it : ctx->value_list())
    iValueListVec.push_back(it->accept(this));
  return iValueListVec;
}

antlrcpp::Any SystemVisitor::visitValue_list(
    MYSQLParser::Value_listContext *ctx) {
  std::vector<Field *> iValueVec;
  for (const auto &it : ctx->value()) {
    iValueVec.push_back(it->accept(this));
  }
  return iValueVec;
}

antlrcpp::Any SystemVisitor::visitValue(MYSQLParser::ValueContext *ctx) {
  Field *pField = nullptr;
  if (ctx->Integer())
    pField = new IntField(std::stoi(ctx->Integer()->getText()));
  if (ctx->Float()) pField = new FloatField(std::stod(ctx->Float()->getText()));
  if (ctx->String())
    pField = new CharField(ctx->String()->getText().substr(
        1, ctx->String()->getText().size() - 2));
  if (ctx->Null()) pField = new NullField();
  return pField;
}

antlrcpp::Any SystemVisitor::visitWhere_and_clause(
    MYSQLParser::Where_and_clauseContext *ctx) {
  std::map<String, std::vector<Condition *>> iCondMap;
  for (const auto &it : ctx->where_clause()) {
    std::pair<String, Condition *> iCondPair = it->accept(this);
    if (iCondMap.find(iCondPair.first) == iCondMap.end()) {
      iCondMap[iCondPair.first] = {};
    }
    iCondMap[iCondPair.first].push_back(iCondPair.second);
  }
  return iCondMap;
}

antlrcpp::Any SystemVisitor::visitWhere_operator_expression(
    MYSQLParser::Where_operator_expressionContext *ctx) {
  std::pair<String, String> iPair = ctx->column()->accept(this);
  FieldID nColIndex = _pDB->GetColID(iPair.first, iPair.second);
  if (ctx->expression()->column()) {
    // JOIN CONDITION
    std::pair<String, String> iPairB =
        ctx->expression()->column()->accept(this);
    return std::pair<String, Condition *>(
        "JOIN", new JoinCondition(iPair.first, iPair.second, iPairB.first,
                                  iPairB.second));
  }

  // get [pLow, pHigh)
  Field *pField = ctx->expression()->value()->accept(this);
  Field *pLow = ctx->expression()->value()->accept(this),
        *pHigh = pLow->Clone();
  if (ctx->operator_()->getText() == "<") {
    pLow->ToMin();
  } else if (ctx->operator_()->getText() == ">") {
    pLow->Add();
    pHigh->ToMax();
  } else if (ctx->operator_()->getText() == "=") {
    pHigh->Add();
  } else if (ctx->operator_()->getText() == "<=") {
    pLow->ToMin();
    pHigh->Add();
  } else if (ctx->operator_()->getText() == ">=") {
    pHigh->ToMax();
  } else if (ctx->operator_()->getText() == "<>") {
  } else {
    throw CaseException();
  }

  if (_pDB->IsIndex(iPair.first, iPair.second)) {
    // Index
    return std::pair<String, Condition *>(
        iPair.first,
        new IndexCondition(iPair.first, iPair.second, pLow, pHigh));
  } else {
    // no Index
    return std::pair<String, Condition *>(
        iPair.first, new RangeCondition(nColIndex, pLow, pHigh));
  }
}

antlrcpp::Any SystemVisitor::visitWhere_operator_select(
    MYSQLParser::Where_operator_selectContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitWhere_null(
    MYSQLParser::Where_nullContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitWhere_in_list(
    MYSQLParser::Where_in_listContext *ctx) {
  // WHERE XXX IN (...)
  std::pair<String, String> iPair = ctx->column()->accept(this);
  FieldID nColIndex = _pDB->GetColID(iPair.first, iPair.second);

  return std::pair<String, Condition *>(
      iPair.first, new InCondition(nColIndex, ctx->value_list()->accept(this)));
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitWhere_in_select(
    MYSQLParser::Where_in_selectContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitWhere_like_string(
    MYSQLParser::Where_like_stringContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitColumn(MYSQLParser::ColumnContext *ctx) {
  String sTableName = ctx->Identifier(0)->getText();
  String sColumnName = ctx->Identifier(1)->getText();
  return std::pair<String, String>(sTableName, sColumnName);
}

antlrcpp::Any SystemVisitor::visitExpression(
    MYSQLParser::ExpressionContext *ctx) {
  return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitSet_clause(
    MYSQLParser::Set_clauseContext *ctx) {
  std::vector<std::pair<String, Field *>> iVec;
  for (Size i = 0; i < ctx->Identifier().size(); ++i) {
    iVec.push_back(
        {ctx->Identifier(i)->getText(), ctx->value(i)->accept(this)});
  }
  return iVec;
}

antlrcpp::Any SystemVisitor::visitSelectors(
    MYSQLParser::SelectorsContext *ctx) {
  return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitSelector(MYSQLParser::SelectorContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitIdentifiers(
    MYSQLParser::IdentifiersContext *ctx) {
  std::vector<String> iStringVec;
  for (const auto &it : ctx->Identifier()) {
    iStringVec.push_back(it->getText());
  }
  return iStringVec;
}

antlrcpp::Any SystemVisitor::visitOperator_(
    MYSQLParser::Operator_Context *ctx) {
  return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitAggregator(
    MYSQLParser::AggregatorContext *ctx) {
  return visitChildren(ctx);
}

}  // namespace dbtrain_mysql