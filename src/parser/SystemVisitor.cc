#include "SystemVisitor.h"

#include <float.h>
#include <stdlib.h>

#include <unordered_map>

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
    auto e = CaseException(ctx->getText());
    std::cout << e.what() << "\n";
    throw e;
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
    if(sTableName.substr(0,1) == "@") continue;
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
  std::vector<std::vector<String>> iValueListVec;
  std::string path = ctx->String()->getText();
  path = path.substr(1, path.size() - 2);
  std::fstream fin(path, std::ios::in);
  printf("path:%s\n", path.data());
  if (!fin) {
    auto e = FileNotExistException();
    std::cout << e.what() << "\n";
    throw e;
  }
  std::string str = "";
  while (std::getline(fin, str)) {
    iValueListVec.push_back(std::vector<String>());
    if (str.find("\n") != str.npos) {
      str = str.substr(0, str.find("\n"));  // delete \n
    }
    std::string::size_type tail = str.find(",");
    std::string::size_type head = 0;
    int pt = 0;
    while (tail != std::string::npos) {
      iValueListVec.back().push_back(str.substr(head, tail - head));
      head = tail + 1;
      tail = str.find(",", head);
      pt++;
    }
    if (head != str.length()) {
      iValueListVec.back().push_back(str.substr(head));
    }
  }
  fin.close();

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

antlrcpp::Any SystemVisitor::visitDump_data(
    MYSQLParser::Dump_dataContext *ctx) {
  std::string tablename = ctx->Identifier()->getText();
  std::string path = ctx->String()->getText();
  path = path.substr(1, path.length() - 2);
  std::vector<PageSlotID> pageslotvec = _pDB->Search(tablename, nullptr, {});
  Result *pResult = new MemResult(_pDB->GetColumnNames(tablename));
  for (const auto &it : pageslotvec)
    pResult->PushBack(_pDB->GetRecord(tablename, it));
  std::ofstream fout(path);
  if (!fout) {
    auto e = FileNotExistException();
    std::cout << e.what() << "\n";
    throw e;
  }
  fout.write(pResult->Dump().data(), pResult->Dump().size());
  fout.close();
  return pResult;
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
  Result *res = new MemResult({"Column Name", "Column Type", "Column Size",
                               "Can Be Null", "Primary Key"});
  String sTableName = ctx->Identifier()->getText();
  try {
    for (const auto &pRecord : _pDB->GetTableInfos(sTableName))
      res->PushBack(pRecord);
  } catch (const std::exception &e) {
  }
  return res;
}
antlrcpp::Any SystemVisitor::visitDescribe_shadow_table(
    MYSQLParser::Describe_shadow_tableContext *ctx) {
      //TODO: desc shadow table
  String sTableName = ctx->Identifier()->toString();
  int limit = INT32_MAX, offset = 0;
  std::vector<PageSlotID> psidVec = _pDB->Search("@" + sTableName, nullptr, {}, limit, offset);
  Result *res = new MemResult({SHADOW_STATUS_NAME,
     SHADOW_LOCAL_COLUMN_NAME, SHADOW_FOREIGN_TABLE_NAME, SHADOW_FOREIGN_COLUMN_NAME});
  for(auto& psid: psidVec){
    res->PushBack(_pDB->GetRecord("@" + sTableName, psid));
  }
  return res;
}
antlrcpp::Any SystemVisitor::visitInsert_into_table(
    MYSQLParser::Insert_into_tableContext *ctx) {
  // std::vector<std::vector<Field *>> iValueListVec =
  //     ctx->value_lists()->accept(this);
  // String sTableName = ctx->Identifier()->getText();
  // int inserted = 0;
  // for (const auto &iValueList : iValueListVec) {
  //   try {
  //     _pDB->Insert(sTableName, iValueList);
  //     ++inserted;
  //   } catch (const std::exception &e) {
  //   }
  // }

  std::vector<std::vector<String>> iRawListVec =
      ctx->value_lists()->accept(this);
  String sTableName = ctx->Identifier()->getText();
  int inserted = 0;
  for (const auto &iRawVec : iRawListVec) {
    try {
      _pDB->Insert(sTableName, iRawVec);
      ++inserted;
    } catch (const std::exception &e) {
    }
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

  // std::vector<std::pair<String, Field *>> iSetVec =
  //     ctx->set_clause()->accept(this);

  std::vector<std::pair<String, String>> iSetVec =
      ctx->set_clause()->accept(this);

  std::map<String, std::vector<Condition *>> iMap =
      ctx->where_and_clause()->accept(this);
  assert(iMap.size() == 1);
  std::vector<Transform> iTrans;

  // for (Size i = 0; i < iSetVec.size(); ++i) {
  //   FieldID nFieldID = _pDB->GetColID(sTableName, iSetVec[i].first);
  //   FieldType iType = _pDB->GetColType(sTableName, iSetVec[i].first);
  //   iTrans.emplace_back(Transform(nFieldID, iType, iSetVec[i].second));
  // }

  for (Size i = 0; i < iSetVec.size(); ++i) {
    FieldID nFieldID = _pDB->GetColID(sTableName, iSetVec[i].first);
    FieldType iType = _pDB->GetColType(sTableName, iSetVec[i].first);
    iTrans.emplace_back(
        Transform(nFieldID, iType, BuildField(iSetVec[i].second, iType)));
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
  // limit && offset
  int limit = INT32_MAX, offset = 0;
  if (ctx->Integer().size() > 0) {
    String temp = ctx->Integer(0)->getText();
    limit = std::stoi(temp);
    if (ctx->Integer().size() == 2) {
      String temp = ctx->Integer(1)->getText();
      offset = std::stoi(temp);
    }
  }

  for (const auto &sTableName : iTableNameVec) {
    if (iCondMap.find(sTableName) == iCondMap.end()) {
      iResultMap[sTableName] =
          _pDB->Search(sTableName, nullptr, {}, limit, offset);
    } else {
      std::vector<Condition *> iIndexCond{};
      std::vector<Condition *> iOtherCond{};
      for (const auto &pCond : iCondMap[sTableName])
        if (pCond->GetType() == ConditionType::INDEX_TYPE)
          iIndexCond.push_back(pCond);
        else
          iOtherCond.push_back(pCond);
      Condition *pCond = nullptr;
      if (iOtherCond.size() > 0) pCond = new AndCondition(iOtherCond);
      iResultMap[sTableName] =
          _pDB->Search(sTableName, pCond, iIndexCond, limit, offset);
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
  String sTableName = ctx->Identifier()->getText();
  std::vector<String> sColNameVec = ctx->identifiers()->accept(this);

  Size nSize = 0;
  for (const auto &sColName : sColNameVec) {
    try {
      _pDB->DropPrimaryKey(sTableName, sColName);
      ++nSize;
    } catch (const std::exception &e) {
    }
  }
  Result *res = new MemResult({"Drop Primary Key"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(nSize));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitAlter_table_drop_foreign_key(
  MYSQLParser::Alter_table_drop_foreign_keyContext *ctx) {
  String sTableName = ctx->Identifier()[0]->getText();
  String sColName = ctx->Identifier()[1]->getText();
  Size nSize = 0;
  try{
    _pDB->DropForeignKey(sTableName, sColName);
    nSize ++;
  }
  catch(const Exception& e){
    printf("exception:%s\n", e.what());
  }
  Result *res = new MemResult({"Drop Foreign Key"});
  FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
  pRes->SetField(0, new IntField(nSize));
  res->PushBack(pRes);
  return res;
}

antlrcpp::Any SystemVisitor::visitAlter_table_add_pk(
    MYSQLParser::Alter_table_add_pkContext *ctx) {
      
  if(ctx->Identifier().size() == 1){//not constriant
    String tableName = ctx->Identifier()[0]->getText();
    std::vector<String> sColName = ctx->identifiers()->accept(this);
    Size nSize = 0;
    try {
      _pDB->AddPrimaryKey(tableName, sColName);
      nSize += sColName.size();
    } catch (const std::exception &e) {
      printf("%s\n", e.what());
    }
    Result *res = new MemResult({"Add Primary Key"});
    FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
    pRes->SetField(0, new IntField(nSize));
    res->PushBack(pRes);
    return res;
  }
  else{
    // printf("%s %s\n", ctx->Identifier()[0]->getText().data(),ctx->Identifier()[1]->getText().data());
    //TODO: CONSTRIANT起名没有实现
  }
}

antlrcpp::Any SystemVisitor::visitAlter_table_add_foreign_key(
    MYSQLParser::Alter_table_add_foreign_keyContext *ctx) {
  if(ctx->Identifier().size() == 2){
    String lTableName = ctx->Identifier()[0]->toString();
    std::vector<String> lColVec = ctx->identifiers()[0]->accept(this);
    String fTableName = ctx->Identifier()[1]->toString();
    std::vector<String> fColVec = ctx->identifiers()[1]->accept(this);
    if(lColVec.size() != fColVec.size()){
      printf("local key number should be equal to foreign key number\n");
      throw ForeignKeyException("local key number should be equal to foreign key number");
    }
    Size nSize = 0;
    for(int i = 0; i < lColVec.size(); i ++){
      try{
        _pDB->AddForeignKey(lTableName, lColVec[i], fTableName, fColVec[i]);
        nSize ++;
      }
      catch(const Exception& e){
        printf("%s\n",e.what());
      }
    }
    Result *res = new MemResult({"Add Primary Key"});
    FixedRecord *pRes = new FixedRecord(1, {FieldType::INT_TYPE}, {4});
    pRes->SetField(0, new IntField(nSize));
    res->PushBack(pRes);
    return res;
  }else{
    //TODO: CONSTRIANT起名没有实现
  }
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
    _pDB->RenameTable("@" + sOldTableName, "@" + sNewTableName);
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
  std::vector<std::vector<String>> sColVec;
  std::unordered_map<String, int> sColMap;
  std::vector<Column> iColVec;
  for (const auto &it : ctx->field()) {
    std::vector<String> tmp = it->accept(this);
    if (tmp[0][0] == '@') {  // primary key
      for (String &str : tmp) {
        if (sColMap.find(str.substr(1)) == sColMap.end()) {
          auto e = Exception();
          std::cout << e.what() << "\n";
          throw e;
        }
        sColVec[sColMap[str.substr(1)]][3] = "1";
      }
    }
    else if(tmp[0][0] == '#'){ //foreign key
      String sForeignTableName = tmp[0].substr(1);
      for(int i = 1; i < tmp.size(); i += 2){
        if(sColMap.find(tmp[i]) == sColMap.end()){
          throw ForeignKeyException("wtf happened?");
        }
        sColVec[sColMap[tmp[i]]][4] = sForeignTableName + " " + tmp[i + 1];
      }
    }
    else{
      sColVec.push_back(tmp);
      sColMap[tmp[0]] = sColVec.size() - 1;
    }
  }
  for (auto it = sColVec.begin(); it != sColVec.end(); it++) {
    FieldType type = FieldType::NULL_TYPE;
#ifdef DATABASE_DEBUG
    printf("%s\t%s\t%s\t%s\t%s\t%s\n", (*it)[0].data(), (*it)[1].data(),
           (*it)[2].data(), (*it)[3].data(), (*it)[4].data(), (*it)[5].data());
#endif
    int size = 0;
    if ((*it)[1] == "INT") {
      type = FieldType::INT_TYPE;
      size = 4;
    } else if ((*it)[1] == "FLOAT") {
      type = FieldType::FLOAT_TYPE;
      size = 4;
    } else if ((*it)[1] == "DATE") {
      type = FieldType::DATE_TYPE;
      size = 3;
    } else {
      type = FieldType::CHAR_TYPE;
      size = std::stoi((*it)[5]);
    }
    bool canBeNull = ((*it)[2] == "1") ? true : false;
    bool isPrimary = ((*it)[3] == "1") ? true : false;
    std::pair<String, String> tPair = std::make_pair("","");
    if((*it)[4] != ""){
      Size pos = (*it)[4].find(" ");
      tPair.first = (*it)[4].substr(0, pos);
      tPair.second = (*it)[4].substr(pos + 1);
    }
    iColVec.push_back(Column((*it)[0], type, canBeNull, isPrimary, size, tPair));
  }

  return Schema(iColVec);
}

antlrcpp::Any SystemVisitor::visitNormal_field(
    MYSQLParser::Normal_fieldContext *ctx) {
  std::vector<String> vec;
  vec.push_back(ctx->Identifier()->getText());          // 0 Identifier
  vec.push_back(ctx->type_()->getText());               // 1 TYPE
  vec.push_back((ctx->Null() == nullptr) ? "1" : "0");  // 2 CAN BE NULL
  vec.push_back("0");                                   // 3 PRIMARY
  vec.push_back("");                                    // 4 Foreign
  vec.push_back((ctx->type_()->Integer() == nullptr)
                    ? "0"
                    : ctx->type_()->Integer()->getText());  // 5 SIZE
  // TODO : add NULL/PRIMARY KEY/DEFAULT
  return vec;
}

antlrcpp::Any SystemVisitor::visitPrimary_key_field(
    MYSQLParser::Primary_key_fieldContext *ctx) {
  std::vector<String> vec = ctx->identifiers()->accept(this);
  for (int i = 0; i < vec.size(); i++) {
    vec[i] = "@" + vec[i];
  }
  return vec;
}

antlrcpp::Any SystemVisitor::visitForeign_key_field(
    MYSQLParser::Foreign_key_fieldContext *ctx) {
  if(ctx->Identifier().size() == 1){
    String sForeignTableName = ctx->Identifier()[0]->toString();
    std::vector<String> sColName = ctx->identifiers()[0]->accept(this);
    std::vector<String> sForeignColName = ctx->identifiers()[1]->accept(this);
    if(sColName.size() != sForeignColName.size()){
      throw ForeignKeyException("the number of local key should equal to the number of foreign key");
    }
    std::vector<String> res;
    res.push_back("#" + sForeignTableName);
    for(int i = 0; i < sColName.size(); i ++){
      res.push_back(sColName[i]);
      res.push_back(sForeignColName[i]);
    }
    return res;
  }
  else{
    //TODO: 组合外键命名
  }
  
}

antlrcpp::Any SystemVisitor::visitType_(MYSQLParser::Type_Context *ctx) {
  return visitChildren(ctx);
}

antlrcpp::Any SystemVisitor::visitValue_lists(
    MYSQLParser::Value_listsContext *ctx) {


  std::vector<std::vector<String>> iRawListVec;
  for (const auto &it : ctx->value_list())
    iRawListVec.push_back(it->accept(this));
  return iRawListVec;
}

antlrcpp::Any SystemVisitor::visitValue_list(
    MYSQLParser::Value_listContext *ctx) {

  std::vector<String> iRawVec;
  for (const auto &it : ctx->value()) {
    iRawVec.push_back(it->accept(this));
  }
  return iRawVec;
}

antlrcpp::Any SystemVisitor::visitValue(MYSQLParser::ValueContext *ctx) {
  // Field *pField = nullptr;
  // if (ctx->Integer()) {
  //   pField = new IntField(std::stoi(ctx->Integer()->getText()));
  // } else if (ctx->Float()) {
  //   pField = new FloatField(std::stod(ctx->Float()->getText()));
  // } else if (ctx->String()) {
  //   pField = new CharField(ctx->String()->getText().substr(
  //       1, ctx->String()->getText().size() - 2));
  // } else if (ctx->Null()) {
  //   pField = new NullField();
  // }
  // return pField;

  String text = "";
  if (ctx->Integer()) {
    text = ctx->Integer()->getText();
  } else if (ctx->Float()) {
    text = ctx->Float()->getText();
  } else if (ctx->String()) {
    text = ctx->String()->getText();
  } else if (ctx->Null()) {
    text = ctx->Null()->getText();
  } else if (ctx->Date()) {
    text = ctx->Date()->getText();
  }
  return text;
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
  std::pair<String, String> column = ctx->column()->accept(this);
  FieldID nColIndex = _pDB->GetColID(column.first, column.second);
  if (ctx->expression()->column()) {
    // JOIN CONDITION
    std::pair<String, String> iPairB =
        ctx->expression()->column()->accept(this);
    return std::pair<String, Condition *>(
        "JOIN", new JoinCondition(column.first, column.second, iPairB.first,
                                  iPairB.second));
  }

  // get [pLow, pHigh)
  // Field *pLow = ctx->expression()->value()->accept(this);

  Field *pLow = BuildField(ctx->expression()->value()->accept(this),
                           _pDB->GetColType(column.first, column.second));
  Field *pHigh = pLow->Clone();

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
    auto e = CaseException();
    std::cout << e.what() << "\n";
    throw e;
  }

  if (_pDB->IsIndex(column.first, column.second)) {
    // Index
    return std::pair<String, Condition *>(
        column.first,
        new IndexCondition(column.first, column.second, pLow, pHigh));
  } else {
    // no Index
    return std::pair<String, Condition *>(
        column.first, new RangeCondition(nColIndex, pLow, pHigh));
  }
}

antlrcpp::Any SystemVisitor::visitWhere_operator_select(
    MYSQLParser::Where_operator_selectContext *ctx) {
  throw UnimplementedException();
}

antlrcpp::Any SystemVisitor::visitWhere_null(
    MYSQLParser::Where_nullContext *ctx) {
  std::pair<String, String> column = ctx->column()->accept(this);
  FieldID nColIndex = _pDB->GetColID(column.first, column.second);

  if (ctx->getText().find("NOT") != String::npos) {
    return std::pair<String, Condition *>(column.first,
                                          new NullCondition(nColIndex, false));
  } else {
    return std::pair<String, Condition *>(column.first,
                                          new NullCondition(nColIndex, true));
  }
}

antlrcpp::Any SystemVisitor::visitWhere_in_list(
    MYSQLParser::Where_in_listContext *ctx) {
  // WHERE XXX IN (...)
  std::pair<String, String> column = ctx->column()->accept(this);
  FieldID nColIndex = _pDB->GetColID(column.first, column.second);

  // std::vector<Field *> iFieldVec = ctx->value_list()->accept(this);
  // return std::pair<String, Condition *>(column.first,
  //                                       new InCondition(nColIndex,
  //                                       iFieldVec));

  std::vector<String> iRawVec = ctx->value_list()->accept(this);
  std::vector<Field *> iFieldVec;
  FieldType iType = _pDB->GetColType(column.first, column.second);
  try {
    for (const String &iRaw : iRawVec) {
      Field *pField = BuildField(iRaw, iType);
      iFieldVec.push_back(pField);
    }
  } catch (const std::exception &e) {
    for (Field *pField : iFieldVec) {
      delete pField;
    }
    throw e;
  }

  return std::pair<String, Condition *>(column.first,
                                        new InCondition(nColIndex, iFieldVec));
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
  // std::vector<std::pair<String, Field *>> iVec;
  // for (Size i = 0; i < ctx->Identifier().size(); ++i) {
  //   iVec.push_back(
  //       {ctx->Identifier(i)->getText(), ctx->value(i)->accept(this)});
  // }
  // return iVec;

  std::vector<std::pair<String, String>> iVec;
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