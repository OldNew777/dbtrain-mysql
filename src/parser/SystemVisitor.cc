#include "SystemVisitor.h"

#include <float.h>
#include <stdlib.h>

#include "condition/conditions.h"
#include "exception/exceptions.h"
#include "record/fixed_record.h"
#include "record/transform.h"
#include "result/result.h"
#include "table/schema.h"
#include "table/table.h"

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
    throw Exception("Statement type error");
  }
  return res;
}

antlrcpp::Any SystemVisitor::visitCreate_db(
    MYSQLParser::Create_dbContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitDrop_db(MYSQLParser::Drop_dbContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitShow_dbs(MYSQLParser::Show_dbsContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitUse_db(MYSQLParser::Use_dbContext *ctx) {
  throw UncompletedException();
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
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitDump_data(
    MYSQLParser::Dump_dataContext *ctx) {
  throw UncompletedException();
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
    std::cerr << e.what() << '\n';
  }
  Result *res = new MemResult({"Create Table"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(nSize));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitDrop_table(
    MYSQLParser::Drop_tableContext *ctx) {
  Size nSize = 0;
  try {
    String sTableName = ctx->Identifier()->getText();
    _pDB->DropTable(sTableName);
    nSize = 1;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
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
  for (const auto &pRecord : _pDB->GetTableInfos(sTableName))
    res->PushBack(pRecord);
  return res;
}

antlrcpp::Any SystemVisitor::visitInsert_into_table(
    MYSQLParser::Insert_into_tableContext *ctx) {
  std::vector<std::vector<String>> iValueListVec =
      ctx->value_lists()->accept(this);
  String sTableName = ctx->Identifier()->getText();
  for (const auto &iValueList : iValueListVec) {
    _pDB->Insert(sTableName, iValueList);
  }
  Result *res = new MemResult({"Insert"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(iValueListVec.size()));
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
  Size nSize = _pDB->Delete(sTableName, pCond, iIndexCond);
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
  std::vector<std::pair<String, String>> iSetVec =
      ctx->set_clause()->accept(this);
  String sTableName = ctx->Identifier()->getText();
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
  return ctx->select_table()->accept(this);
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
      FieldType iType = _pDB->GetColType(sTableName, sColName);
      _pDB->CreateIndex(sTableName, sColName, iType);
      ++nSize;
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
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
      std::cerr << e.what() << '\n';
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
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitAlter_table_drop_foreign_key(
    MYSQLParser::Alter_table_drop_foreign_keyContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitAlter_table_add_pk(
    MYSQLParser::Alter_table_add_pkContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitAlter_table_add_foreign_key(
    MYSQLParser::Alter_table_add_foreign_keyContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitAlter_table_add_unique(
    MYSQLParser::Alter_table_add_uniqueContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitAlter_table_rename(
    MYSQLParser::Alter_table_renameContext *ctx) {
  throw UncompletedException();
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
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitForeign_key_field(
    MYSQLParser::Foreign_key_fieldContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitType_(MYSQLParser::Type_Context *ctx) {
  return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitValue_lists(
    MYSQLParser::Value_listsContext *ctx) {
  std::vector<std::vector<String>> iValueListVec;
  for (const auto &it : ctx->value_list())
    iValueListVec.push_back(it->accept(this));
  return iValueListVec;
}

antlrcpp::Any SystemVisitor::visitValue_list(
    MYSQLParser::Value_listContext *ctx) {
  std::vector<String> iValueList;
  for (const auto &it : ctx->value()) iValueList.push_back(it->getText());
  return iValueList;
}

antlrcpp::Any SystemVisitor::visitValue(MYSQLParser::ValueContext *ctx) {
  return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitWhere_and_clause(
    MYSQLParser::Where_and_clauseContext *ctx) {
  std::map<String, std::vector<Condition *>> iCondMap;
  for (const auto &it : ctx->where_clause()) {
    std::pair<String, Condition *> iCondPair = it->accept(this);
    // TODO: JOIN CONDITION
    if (iCondPair.second->GetType() == ConditionType::JOIN_TYPE) {
    }
    // Not Join Condition
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
  if (_pDB->IsIndex(iPair.first, iPair.second)) {
    double fValue = stod(ctx->expression()->value()->getText());
    FieldType iType = _pDB->GetColType(iPair.first, iPair.second);
    if (ctx->children[1]->getText() == "<") {
      return std::pair<String, Condition *>(
          iPair.first, new IndexCondition(iPair.first, iPair.second, DBL_MIN,
                                          fValue, iType));
    } else if (ctx->children[1]->getText() == ">") {
      return std::pair<String, Condition *>(
          iPair.first, new IndexCondition(iPair.first, iPair.second,
                                          fValue + EPOSILO, DBL_MAX, iType));
    } else if (ctx->children[1]->getText() == "=") {
      return std::pair<String, Condition *>(
          iPair.first, new IndexCondition(iPair.first, iPair.second, fValue,
                                          fValue + EPOSILO, iType));
    } else if (ctx->children[1]->getText() == "<=") {
      return std::pair<String, Condition *>(
          iPair.first, new IndexCondition(iPair.first, iPair.second, DBL_MIN,
                                          fValue + EPOSILO, iType));
    } else if (ctx->children[1]->getText() == ">=") {
      return std::pair<String, Condition *>(
          iPair.first, new IndexCondition(iPair.first, iPair.second, fValue,
                                          DBL_MAX, iType));
    } else if (ctx->children[1]->getText() == "<>") {
      return std::pair<String, Condition *>(
          iPair.first, new NotCondition(new RangeCondition(nColIndex, fValue,
                                                           fValue + EPOSILO)));
    } else {
      throw Exception();
    }
  } else {
    double fValue = stod(ctx->expression()->value()->getText());
    if (ctx->children[1]->getText() == "<") {
      return std::pair<String, Condition *>(
          iPair.first, new RangeCondition(nColIndex, DBL_MIN, fValue));
    } else if (ctx->children[1]->getText() == ">") {
      return std::pair<String, Condition *>(
          iPair.first,
          new RangeCondition(nColIndex, fValue + EPOSILO, DBL_MAX));
    } else if (ctx->children[1]->getText() == "=") {
      return std::pair<String, Condition *>(
          iPair.first, new RangeCondition(nColIndex, fValue, fValue + EPOSILO));
    } else if (ctx->children[1]->getText() == "<=") {
      return std::pair<String, Condition *>(
          iPair.first,
          new RangeCondition(nColIndex, DBL_MIN, fValue + EPOSILO));
    } else if (ctx->children[1]->getText() == ">=") {
      return std::pair<String, Condition *>(
          iPair.first, new RangeCondition(nColIndex, fValue, DBL_MAX));
    } else if (ctx->children[1]->getText() == "<>") {
      return std::pair<String, Condition *>(
          iPair.first, new NotCondition(new RangeCondition(nColIndex, fValue,
                                                           fValue + EPOSILO)));
    } else {
      throw SpecialException();
    }
  }
}

antlrcpp::Any SystemVisitor::visitWhere_operator_select(
    MYSQLParser::Where_operator_selectContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitWhere_null(
    MYSQLParser::Where_nullContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitWhere_in_list(
    MYSQLParser::Where_in_listContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitWhere_in_select(
    MYSQLParser::Where_in_selectContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitWhere_like_string(
    MYSQLParser::Where_like_stringContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitColumn(MYSQLParser::ColumnContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitExpression(
    MYSQLParser::ExpressionContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitSet_clause(
    MYSQLParser::Set_clauseContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitSelectors(
    MYSQLParser::SelectorsContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitSelector(MYSQLParser::SelectorContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitIdentifiers(
    MYSQLParser::IdentifiersContext *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitOperator_(
    MYSQLParser::Operator_Context *ctx) {
  throw UncompletedException();
}

antlrcpp::Any SystemVisitor::visitAggregator(
    MYSQLParser::AggregatorContext *ctx) {
  throw UncompletedException();
}

}  // namespace dbtrain_mysql