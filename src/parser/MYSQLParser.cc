
// Generated from MYSQL.g4 by ANTLR 4.7


#include "MYSQLListener.h"
#include "MYSQLVisitor.h"

#include "MYSQLParser.h"


using namespace antlrcpp;
using namespace antlr4;

MYSQLParser::MYSQLParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

MYSQLParser::~MYSQLParser() {
  delete _interpreter;
}

std::string MYSQLParser::getGrammarFileName() const {
  return "MYSQL.g4";
}

const std::vector<std::string>& MYSQLParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& MYSQLParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

MYSQLParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MYSQLParser::ProgramContext::EOF() {
  return getToken(MYSQLParser::EOF, 0);
}

std::vector<MYSQLParser::StatementContext *> MYSQLParser::ProgramContext::statement() {
  return getRuleContexts<MYSQLParser::StatementContext>();
}

MYSQLParser::StatementContext* MYSQLParser::ProgramContext::statement(size_t i) {
  return getRuleContext<MYSQLParser::StatementContext>(i);
}


size_t MYSQLParser::ProgramContext::getRuleIndex() const {
  return MYSQLParser::RuleProgram;
}

void MYSQLParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void MYSQLParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


antlrcpp::Any MYSQLParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::ProgramContext* MYSQLParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, MYSQLParser::RuleProgram);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(49);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << MYSQLParser::T__1)
      | (1ULL << MYSQLParser::T__3)
      | (1ULL << MYSQLParser::T__4)
      | (1ULL << MYSQLParser::T__6)
      | (1ULL << MYSQLParser::T__9)
      | (1ULL << MYSQLParser::T__14)
      | (1ULL << MYSQLParser::T__17)
      | (1ULL << MYSQLParser::T__18)
      | (1ULL << MYSQLParser::T__21)
      | (1ULL << MYSQLParser::T__23)
      | (1ULL << MYSQLParser::T__25)
      | (1ULL << MYSQLParser::T__30)
      | (1ULL << MYSQLParser::Null))) != 0) || _la == MYSQLParser::Annotation) {
      setState(46);
      statement();
      setState(51);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(52);
    match(MYSQLParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

MYSQLParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MYSQLParser::Db_statementContext* MYSQLParser::StatementContext::db_statement() {
  return getRuleContext<MYSQLParser::Db_statementContext>(0);
}

MYSQLParser::Io_statementContext* MYSQLParser::StatementContext::io_statement() {
  return getRuleContext<MYSQLParser::Io_statementContext>(0);
}

MYSQLParser::Table_statementContext* MYSQLParser::StatementContext::table_statement() {
  return getRuleContext<MYSQLParser::Table_statementContext>(0);
}

MYSQLParser::Alter_statementContext* MYSQLParser::StatementContext::alter_statement() {
  return getRuleContext<MYSQLParser::Alter_statementContext>(0);
}

tree::TerminalNode* MYSQLParser::StatementContext::Annotation() {
  return getToken(MYSQLParser::Annotation, 0);
}

tree::TerminalNode* MYSQLParser::StatementContext::Null() {
  return getToken(MYSQLParser::Null, 0);
}


size_t MYSQLParser::StatementContext::getRuleIndex() const {
  return MYSQLParser::RuleStatement;
}

void MYSQLParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void MYSQLParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


antlrcpp::Any MYSQLParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::StatementContext* MYSQLParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, MYSQLParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(70);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(54);
      db_statement();
      setState(55);
      match(MYSQLParser::T__0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(57);
      io_statement();
      setState(58);
      match(MYSQLParser::T__0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(60);
      table_statement();
      setState(61);
      match(MYSQLParser::T__0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(63);
      alter_statement();
      setState(64);
      match(MYSQLParser::T__0);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(66);
      match(MYSQLParser::Annotation);
      setState(67);
      match(MYSQLParser::T__0);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(68);
      match(MYSQLParser::Null);
      setState(69);
      match(MYSQLParser::T__0);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Db_statementContext ------------------------------------------------------------------

MYSQLParser::Db_statementContext::Db_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MYSQLParser::Db_statementContext::getRuleIndex() const {
  return MYSQLParser::RuleDb_statement;
}

void MYSQLParser::Db_statementContext::copyFrom(Db_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Show_dbsContext ------------------------------------------------------------------

MYSQLParser::Show_dbsContext::Show_dbsContext(Db_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Show_dbsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShow_dbs(this);
}
void MYSQLParser::Show_dbsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShow_dbs(this);
}

antlrcpp::Any MYSQLParser::Show_dbsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitShow_dbs(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Drop_dbContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Drop_dbContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::Drop_dbContext::Drop_dbContext(Db_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Drop_dbContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDrop_db(this);
}
void MYSQLParser::Drop_dbContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDrop_db(this);
}

antlrcpp::Any MYSQLParser::Drop_dbContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitDrop_db(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Show_tablesContext ------------------------------------------------------------------

MYSQLParser::Show_tablesContext::Show_tablesContext(Db_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Show_tablesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShow_tables(this);
}
void MYSQLParser::Show_tablesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShow_tables(this);
}

antlrcpp::Any MYSQLParser::Show_tablesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitShow_tables(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Create_dbContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Create_dbContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::Create_dbContext::Create_dbContext(Db_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Create_dbContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreate_db(this);
}
void MYSQLParser::Create_dbContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreate_db(this);
}

antlrcpp::Any MYSQLParser::Create_dbContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitCreate_db(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Use_dbContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Use_dbContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::Use_dbContext::Use_dbContext(Db_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Use_dbContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUse_db(this);
}
void MYSQLParser::Use_dbContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUse_db(this);
}

antlrcpp::Any MYSQLParser::Use_dbContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitUse_db(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Show_indexesContext ------------------------------------------------------------------

MYSQLParser::Show_indexesContext::Show_indexesContext(Db_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Show_indexesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShow_indexes(this);
}
void MYSQLParser::Show_indexesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShow_indexes(this);
}

antlrcpp::Any MYSQLParser::Show_indexesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitShow_indexes(this);
  else
    return visitor->visitChildren(this);
}
MYSQLParser::Db_statementContext* MYSQLParser::db_statement() {
  Db_statementContext *_localctx = _tracker.createInstance<Db_statementContext>(_ctx, getState());
  enterRule(_localctx, 4, MYSQLParser::RuleDb_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(86);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<Db_statementContext *>(_tracker.createInstance<MYSQLParser::Create_dbContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(72);
      match(MYSQLParser::T__1);
      setState(73);
      match(MYSQLParser::T__2);
      setState(74);
      match(MYSQLParser::Identifier);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<Db_statementContext *>(_tracker.createInstance<MYSQLParser::Drop_dbContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(75);
      match(MYSQLParser::T__3);
      setState(76);
      match(MYSQLParser::T__2);
      setState(77);
      match(MYSQLParser::Identifier);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<Db_statementContext *>(_tracker.createInstance<MYSQLParser::Show_dbsContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(78);
      match(MYSQLParser::T__4);
      setState(79);
      match(MYSQLParser::T__5);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<Db_statementContext *>(_tracker.createInstance<MYSQLParser::Use_dbContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(80);
      match(MYSQLParser::T__6);
      setState(81);
      match(MYSQLParser::Identifier);
      break;
    }

    case 5: {
      _localctx = dynamic_cast<Db_statementContext *>(_tracker.createInstance<MYSQLParser::Show_tablesContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(82);
      match(MYSQLParser::T__4);
      setState(83);
      match(MYSQLParser::T__7);
      break;
    }

    case 6: {
      _localctx = dynamic_cast<Db_statementContext *>(_tracker.createInstance<MYSQLParser::Show_indexesContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(84);
      match(MYSQLParser::T__4);
      setState(85);
      match(MYSQLParser::T__8);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Io_statementContext ------------------------------------------------------------------

MYSQLParser::Io_statementContext::Io_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MYSQLParser::Io_statementContext::getRuleIndex() const {
  return MYSQLParser::RuleIo_statement;
}

void MYSQLParser::Io_statementContext::copyFrom(Io_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Dump_dataContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Dump_dataContext::String() {
  return getToken(MYSQLParser::String, 0);
}

tree::TerminalNode* MYSQLParser::Dump_dataContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::Dump_dataContext::Dump_dataContext(Io_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Dump_dataContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDump_data(this);
}
void MYSQLParser::Dump_dataContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDump_data(this);
}

antlrcpp::Any MYSQLParser::Dump_dataContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitDump_data(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Load_dataContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Load_dataContext::String() {
  return getToken(MYSQLParser::String, 0);
}

tree::TerminalNode* MYSQLParser::Load_dataContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::Load_dataContext::Load_dataContext(Io_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Load_dataContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLoad_data(this);
}
void MYSQLParser::Load_dataContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLoad_data(this);
}

antlrcpp::Any MYSQLParser::Load_dataContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitLoad_data(this);
  else
    return visitor->visitChildren(this);
}
MYSQLParser::Io_statementContext* MYSQLParser::io_statement() {
  Io_statementContext *_localctx = _tracker.createInstance<Io_statementContext>(_ctx, getState());
  enterRule(_localctx, 6, MYSQLParser::RuleIo_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(102);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MYSQLParser::T__9: {
        _localctx = dynamic_cast<Io_statementContext *>(_tracker.createInstance<MYSQLParser::Load_dataContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(88);
        match(MYSQLParser::T__9);
        setState(89);
        match(MYSQLParser::T__10);
        setState(90);
        match(MYSQLParser::T__11);
        setState(91);
        match(MYSQLParser::String);
        setState(92);
        match(MYSQLParser::T__12);
        setState(93);
        match(MYSQLParser::T__13);
        setState(94);
        match(MYSQLParser::Identifier);
        break;
      }

      case MYSQLParser::T__14: {
        _localctx = dynamic_cast<Io_statementContext *>(_tracker.createInstance<MYSQLParser::Dump_dataContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(95);
        match(MYSQLParser::T__14);
        setState(96);
        match(MYSQLParser::T__12);
        setState(97);
        match(MYSQLParser::T__11);
        setState(98);
        match(MYSQLParser::String);
        setState(99);
        match(MYSQLParser::T__10);
        setState(100);
        match(MYSQLParser::T__13);
        setState(101);
        match(MYSQLParser::Identifier);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Table_statementContext ------------------------------------------------------------------

MYSQLParser::Table_statementContext::Table_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MYSQLParser::Table_statementContext::getRuleIndex() const {
  return MYSQLParser::RuleTable_statement;
}

void MYSQLParser::Table_statementContext::copyFrom(Table_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Delete_from_tableContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Delete_from_tableContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::Where_and_clauseContext* MYSQLParser::Delete_from_tableContext::where_and_clause() {
  return getRuleContext<MYSQLParser::Where_and_clauseContext>(0);
}

MYSQLParser::Delete_from_tableContext::Delete_from_tableContext(Table_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Delete_from_tableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDelete_from_table(this);
}
void MYSQLParser::Delete_from_tableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDelete_from_table(this);
}

antlrcpp::Any MYSQLParser::Delete_from_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitDelete_from_table(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Insert_into_tableContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Insert_into_tableContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::Value_listsContext* MYSQLParser::Insert_into_tableContext::value_lists() {
  return getRuleContext<MYSQLParser::Value_listsContext>(0);
}

MYSQLParser::Insert_into_tableContext::Insert_into_tableContext(Table_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Insert_into_tableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInsert_into_table(this);
}
void MYSQLParser::Insert_into_tableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInsert_into_table(this);
}

antlrcpp::Any MYSQLParser::Insert_into_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitInsert_into_table(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Create_tableContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Create_tableContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::Field_listContext* MYSQLParser::Create_tableContext::field_list() {
  return getRuleContext<MYSQLParser::Field_listContext>(0);
}

MYSQLParser::Create_tableContext::Create_tableContext(Table_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Create_tableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreate_table(this);
}
void MYSQLParser::Create_tableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreate_table(this);
}

antlrcpp::Any MYSQLParser::Create_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitCreate_table(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Describe_tableContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Describe_tableContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::Describe_tableContext::Describe_tableContext(Table_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Describe_tableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDescribe_table(this);
}
void MYSQLParser::Describe_tableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDescribe_table(this);
}

antlrcpp::Any MYSQLParser::Describe_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitDescribe_table(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Select_table_Context ------------------------------------------------------------------

MYSQLParser::Select_tableContext* MYSQLParser::Select_table_Context::select_table() {
  return getRuleContext<MYSQLParser::Select_tableContext>(0);
}

MYSQLParser::Select_table_Context::Select_table_Context(Table_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Select_table_Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelect_table_(this);
}
void MYSQLParser::Select_table_Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelect_table_(this);
}

antlrcpp::Any MYSQLParser::Select_table_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitSelect_table_(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Drop_tableContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Drop_tableContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::Drop_tableContext::Drop_tableContext(Table_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Drop_tableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDrop_table(this);
}
void MYSQLParser::Drop_tableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDrop_table(this);
}

antlrcpp::Any MYSQLParser::Drop_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitDrop_table(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Update_tableContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Update_tableContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::Set_clauseContext* MYSQLParser::Update_tableContext::set_clause() {
  return getRuleContext<MYSQLParser::Set_clauseContext>(0);
}

MYSQLParser::Where_and_clauseContext* MYSQLParser::Update_tableContext::where_and_clause() {
  return getRuleContext<MYSQLParser::Where_and_clauseContext>(0);
}

MYSQLParser::Update_tableContext::Update_tableContext(Table_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Update_tableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUpdate_table(this);
}
void MYSQLParser::Update_tableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUpdate_table(this);
}

antlrcpp::Any MYSQLParser::Update_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitUpdate_table(this);
  else
    return visitor->visitChildren(this);
}
MYSQLParser::Table_statementContext* MYSQLParser::table_statement() {
  Table_statementContext *_localctx = _tracker.createInstance<Table_statementContext>(_ctx, getState());
  enterRule(_localctx, 8, MYSQLParser::RuleTable_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(134);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MYSQLParser::T__1: {
        _localctx = dynamic_cast<Table_statementContext *>(_tracker.createInstance<MYSQLParser::Create_tableContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(104);
        match(MYSQLParser::T__1);
        setState(105);
        match(MYSQLParser::T__13);
        setState(106);
        match(MYSQLParser::Identifier);
        setState(107);
        match(MYSQLParser::T__15);
        setState(108);
        field_list();
        setState(109);
        match(MYSQLParser::T__16);
        break;
      }

      case MYSQLParser::T__3: {
        _localctx = dynamic_cast<Table_statementContext *>(_tracker.createInstance<MYSQLParser::Drop_tableContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(111);
        match(MYSQLParser::T__3);
        setState(112);
        match(MYSQLParser::T__13);
        setState(113);
        match(MYSQLParser::Identifier);
        break;
      }

      case MYSQLParser::T__17: {
        _localctx = dynamic_cast<Table_statementContext *>(_tracker.createInstance<MYSQLParser::Describe_tableContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(114);
        match(MYSQLParser::T__17);
        setState(115);
        match(MYSQLParser::Identifier);
        break;
      }

      case MYSQLParser::T__18: {
        _localctx = dynamic_cast<Table_statementContext *>(_tracker.createInstance<MYSQLParser::Insert_into_tableContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(116);
        match(MYSQLParser::T__18);
        setState(117);
        match(MYSQLParser::T__19);
        setState(118);
        match(MYSQLParser::Identifier);
        setState(119);
        match(MYSQLParser::T__20);
        setState(120);
        value_lists();
        break;
      }

      case MYSQLParser::T__21: {
        _localctx = dynamic_cast<Table_statementContext *>(_tracker.createInstance<MYSQLParser::Delete_from_tableContext>(_localctx));
        enterOuterAlt(_localctx, 5);
        setState(121);
        match(MYSQLParser::T__21);
        setState(122);
        match(MYSQLParser::T__10);
        setState(123);
        match(MYSQLParser::Identifier);
        setState(124);
        match(MYSQLParser::T__22);
        setState(125);
        where_and_clause();
        break;
      }

      case MYSQLParser::T__23: {
        _localctx = dynamic_cast<Table_statementContext *>(_tracker.createInstance<MYSQLParser::Update_tableContext>(_localctx));
        enterOuterAlt(_localctx, 6);
        setState(126);
        match(MYSQLParser::T__23);
        setState(127);
        match(MYSQLParser::Identifier);
        setState(128);
        match(MYSQLParser::T__24);
        setState(129);
        set_clause();
        setState(130);
        match(MYSQLParser::T__22);
        setState(131);
        where_and_clause();
        break;
      }

      case MYSQLParser::T__25: {
        _localctx = dynamic_cast<Table_statementContext *>(_tracker.createInstance<MYSQLParser::Select_table_Context>(_localctx));
        enterOuterAlt(_localctx, 7);
        setState(133);
        select_table();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Select_tableContext ------------------------------------------------------------------

MYSQLParser::Select_tableContext::Select_tableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MYSQLParser::SelectorsContext* MYSQLParser::Select_tableContext::selectors() {
  return getRuleContext<MYSQLParser::SelectorsContext>(0);
}

MYSQLParser::IdentifiersContext* MYSQLParser::Select_tableContext::identifiers() {
  return getRuleContext<MYSQLParser::IdentifiersContext>(0);
}

MYSQLParser::Where_and_clauseContext* MYSQLParser::Select_tableContext::where_and_clause() {
  return getRuleContext<MYSQLParser::Where_and_clauseContext>(0);
}

MYSQLParser::ColumnContext* MYSQLParser::Select_tableContext::column() {
  return getRuleContext<MYSQLParser::ColumnContext>(0);
}

std::vector<tree::TerminalNode *> MYSQLParser::Select_tableContext::Integer() {
  return getTokens(MYSQLParser::Integer);
}

tree::TerminalNode* MYSQLParser::Select_tableContext::Integer(size_t i) {
  return getToken(MYSQLParser::Integer, i);
}


size_t MYSQLParser::Select_tableContext::getRuleIndex() const {
  return MYSQLParser::RuleSelect_table;
}

void MYSQLParser::Select_tableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelect_table(this);
}

void MYSQLParser::Select_tableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelect_table(this);
}


antlrcpp::Any MYSQLParser::Select_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitSelect_table(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::Select_tableContext* MYSQLParser::select_table() {
  Select_tableContext *_localctx = _tracker.createInstance<Select_tableContext>(_ctx, getState());
  enterRule(_localctx, 10, MYSQLParser::RuleSelect_table);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(136);
    match(MYSQLParser::T__25);
    setState(137);
    selectors();
    setState(138);
    match(MYSQLParser::T__10);
    setState(139);
    identifiers();
    setState(142);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MYSQLParser::T__22) {
      setState(140);
      match(MYSQLParser::T__22);
      setState(141);
      where_and_clause();
    }
    setState(147);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MYSQLParser::T__26) {
      setState(144);
      match(MYSQLParser::T__26);
      setState(145);
      match(MYSQLParser::T__27);
      setState(146);
      column();
    }
    setState(155);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MYSQLParser::T__28) {
      setState(149);
      match(MYSQLParser::T__28);
      setState(150);
      match(MYSQLParser::Integer);
      setState(153);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MYSQLParser::T__29) {
        setState(151);
        match(MYSQLParser::T__29);
        setState(152);
        match(MYSQLParser::Integer);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Alter_statementContext ------------------------------------------------------------------

MYSQLParser::Alter_statementContext::Alter_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MYSQLParser::Alter_statementContext::getRuleIndex() const {
  return MYSQLParser::RuleAlter_statement;
}

void MYSQLParser::Alter_statementContext::copyFrom(Alter_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Alter_table_drop_pkContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> MYSQLParser::Alter_table_drop_pkContext::Identifier() {
  return getTokens(MYSQLParser::Identifier);
}

tree::TerminalNode* MYSQLParser::Alter_table_drop_pkContext::Identifier(size_t i) {
  return getToken(MYSQLParser::Identifier, i);
}

MYSQLParser::Alter_table_drop_pkContext::Alter_table_drop_pkContext(Alter_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Alter_table_drop_pkContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlter_table_drop_pk(this);
}
void MYSQLParser::Alter_table_drop_pkContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlter_table_drop_pk(this);
}

antlrcpp::Any MYSQLParser::Alter_table_drop_pkContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitAlter_table_drop_pk(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Alter_table_add_foreign_keyContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> MYSQLParser::Alter_table_add_foreign_keyContext::Identifier() {
  return getTokens(MYSQLParser::Identifier);
}

tree::TerminalNode* MYSQLParser::Alter_table_add_foreign_keyContext::Identifier(size_t i) {
  return getToken(MYSQLParser::Identifier, i);
}

std::vector<MYSQLParser::IdentifiersContext *> MYSQLParser::Alter_table_add_foreign_keyContext::identifiers() {
  return getRuleContexts<MYSQLParser::IdentifiersContext>();
}

MYSQLParser::IdentifiersContext* MYSQLParser::Alter_table_add_foreign_keyContext::identifiers(size_t i) {
  return getRuleContext<MYSQLParser::IdentifiersContext>(i);
}

MYSQLParser::Alter_table_add_foreign_keyContext::Alter_table_add_foreign_keyContext(Alter_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Alter_table_add_foreign_keyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlter_table_add_foreign_key(this);
}
void MYSQLParser::Alter_table_add_foreign_keyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlter_table_add_foreign_key(this);
}

antlrcpp::Any MYSQLParser::Alter_table_add_foreign_keyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitAlter_table_add_foreign_key(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Alter_table_add_uniqueContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Alter_table_add_uniqueContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::IdentifiersContext* MYSQLParser::Alter_table_add_uniqueContext::identifiers() {
  return getRuleContext<MYSQLParser::IdentifiersContext>(0);
}

MYSQLParser::Alter_table_add_uniqueContext::Alter_table_add_uniqueContext(Alter_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Alter_table_add_uniqueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlter_table_add_unique(this);
}
void MYSQLParser::Alter_table_add_uniqueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlter_table_add_unique(this);
}

antlrcpp::Any MYSQLParser::Alter_table_add_uniqueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitAlter_table_add_unique(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Alter_drop_indexContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Alter_drop_indexContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::IdentifiersContext* MYSQLParser::Alter_drop_indexContext::identifiers() {
  return getRuleContext<MYSQLParser::IdentifiersContext>(0);
}

MYSQLParser::Alter_drop_indexContext::Alter_drop_indexContext(Alter_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Alter_drop_indexContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlter_drop_index(this);
}
void MYSQLParser::Alter_drop_indexContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlter_drop_index(this);
}

antlrcpp::Any MYSQLParser::Alter_drop_indexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitAlter_drop_index(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Alter_add_indexContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Alter_add_indexContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::IdentifiersContext* MYSQLParser::Alter_add_indexContext::identifiers() {
  return getRuleContext<MYSQLParser::IdentifiersContext>(0);
}

MYSQLParser::Alter_add_indexContext::Alter_add_indexContext(Alter_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Alter_add_indexContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlter_add_index(this);
}
void MYSQLParser::Alter_add_indexContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlter_add_index(this);
}

antlrcpp::Any MYSQLParser::Alter_add_indexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitAlter_add_index(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Alter_table_drop_foreign_keyContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> MYSQLParser::Alter_table_drop_foreign_keyContext::Identifier() {
  return getTokens(MYSQLParser::Identifier);
}

tree::TerminalNode* MYSQLParser::Alter_table_drop_foreign_keyContext::Identifier(size_t i) {
  return getToken(MYSQLParser::Identifier, i);
}

MYSQLParser::Alter_table_drop_foreign_keyContext::Alter_table_drop_foreign_keyContext(Alter_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Alter_table_drop_foreign_keyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlter_table_drop_foreign_key(this);
}
void MYSQLParser::Alter_table_drop_foreign_keyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlter_table_drop_foreign_key(this);
}

antlrcpp::Any MYSQLParser::Alter_table_drop_foreign_keyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitAlter_table_drop_foreign_key(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Alter_table_add_pkContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> MYSQLParser::Alter_table_add_pkContext::Identifier() {
  return getTokens(MYSQLParser::Identifier);
}

tree::TerminalNode* MYSQLParser::Alter_table_add_pkContext::Identifier(size_t i) {
  return getToken(MYSQLParser::Identifier, i);
}

MYSQLParser::IdentifiersContext* MYSQLParser::Alter_table_add_pkContext::identifiers() {
  return getRuleContext<MYSQLParser::IdentifiersContext>(0);
}

MYSQLParser::Alter_table_add_pkContext::Alter_table_add_pkContext(Alter_statementContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Alter_table_add_pkContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlter_table_add_pk(this);
}
void MYSQLParser::Alter_table_add_pkContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlter_table_add_pk(this);
}

antlrcpp::Any MYSQLParser::Alter_table_add_pkContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitAlter_table_add_pk(this);
  else
    return visitor->visitChildren(this);
}
MYSQLParser::Alter_statementContext* MYSQLParser::alter_statement() {
  Alter_statementContext *_localctx = _tracker.createInstance<Alter_statementContext>(_ctx, getState());
  enterRule(_localctx, 12, MYSQLParser::RuleAlter_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(229);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<Alter_statementContext *>(_tracker.createInstance<MYSQLParser::Alter_add_indexContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(157);
      match(MYSQLParser::T__30);
      setState(158);
      match(MYSQLParser::T__13);
      setState(159);
      match(MYSQLParser::Identifier);
      setState(160);
      match(MYSQLParser::T__31);
      setState(161);
      match(MYSQLParser::T__32);
      setState(162);
      match(MYSQLParser::T__15);
      setState(163);
      identifiers();
      setState(164);
      match(MYSQLParser::T__16);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<Alter_statementContext *>(_tracker.createInstance<MYSQLParser::Alter_drop_indexContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(166);
      match(MYSQLParser::T__30);
      setState(167);
      match(MYSQLParser::T__13);
      setState(168);
      match(MYSQLParser::Identifier);
      setState(169);
      match(MYSQLParser::T__3);
      setState(170);
      match(MYSQLParser::T__32);
      setState(171);
      match(MYSQLParser::T__15);
      setState(172);
      identifiers();
      setState(173);
      match(MYSQLParser::T__16);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<Alter_statementContext *>(_tracker.createInstance<MYSQLParser::Alter_table_drop_pkContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(175);
      match(MYSQLParser::T__30);
      setState(176);
      match(MYSQLParser::T__13);
      setState(177);
      match(MYSQLParser::Identifier);
      setState(178);
      match(MYSQLParser::T__3);
      setState(179);
      match(MYSQLParser::T__33);
      setState(180);
      match(MYSQLParser::T__34);
      setState(182);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MYSQLParser::Identifier) {
        setState(181);
        match(MYSQLParser::Identifier);
      }
      break;
    }

    case 4: {
      _localctx = dynamic_cast<Alter_statementContext *>(_tracker.createInstance<MYSQLParser::Alter_table_drop_foreign_keyContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(184);
      match(MYSQLParser::T__30);
      setState(185);
      match(MYSQLParser::T__13);
      setState(186);
      match(MYSQLParser::Identifier);
      setState(187);
      match(MYSQLParser::T__3);
      setState(188);
      match(MYSQLParser::T__35);
      setState(189);
      match(MYSQLParser::T__34);
      setState(190);
      match(MYSQLParser::Identifier);
      break;
    }

    case 5: {
      _localctx = dynamic_cast<Alter_statementContext *>(_tracker.createInstance<MYSQLParser::Alter_table_add_pkContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(191);
      match(MYSQLParser::T__30);
      setState(192);
      match(MYSQLParser::T__13);
      setState(193);
      match(MYSQLParser::Identifier);
      setState(194);
      match(MYSQLParser::T__31);
      setState(195);
      match(MYSQLParser::T__36);
      setState(196);
      match(MYSQLParser::Identifier);
      setState(197);
      match(MYSQLParser::T__33);
      setState(198);
      match(MYSQLParser::T__34);
      setState(199);
      match(MYSQLParser::T__15);
      setState(200);
      identifiers();
      setState(201);
      match(MYSQLParser::T__16);
      break;
    }

    case 6: {
      _localctx = dynamic_cast<Alter_statementContext *>(_tracker.createInstance<MYSQLParser::Alter_table_add_foreign_keyContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(203);
      match(MYSQLParser::T__30);
      setState(204);
      match(MYSQLParser::T__13);
      setState(205);
      match(MYSQLParser::Identifier);
      setState(206);
      match(MYSQLParser::T__31);
      setState(207);
      match(MYSQLParser::T__36);
      setState(208);
      match(MYSQLParser::Identifier);
      setState(209);
      match(MYSQLParser::T__35);
      setState(210);
      match(MYSQLParser::T__34);
      setState(211);
      match(MYSQLParser::T__15);
      setState(212);
      identifiers();
      setState(213);
      match(MYSQLParser::T__16);
      setState(214);
      match(MYSQLParser::T__37);
      setState(215);
      match(MYSQLParser::Identifier);
      setState(216);
      match(MYSQLParser::T__15);
      setState(217);
      identifiers();
      setState(218);
      match(MYSQLParser::T__16);
      break;
    }

    case 7: {
      _localctx = dynamic_cast<Alter_statementContext *>(_tracker.createInstance<MYSQLParser::Alter_table_add_uniqueContext>(_localctx));
      enterOuterAlt(_localctx, 7);
      setState(220);
      match(MYSQLParser::T__30);
      setState(221);
      match(MYSQLParser::T__13);
      setState(222);
      match(MYSQLParser::Identifier);
      setState(223);
      match(MYSQLParser::T__31);
      setState(224);
      match(MYSQLParser::T__38);
      setState(225);
      match(MYSQLParser::T__15);
      setState(226);
      identifiers();
      setState(227);
      match(MYSQLParser::T__16);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Field_listContext ------------------------------------------------------------------

MYSQLParser::Field_listContext::Field_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MYSQLParser::FieldContext *> MYSQLParser::Field_listContext::field() {
  return getRuleContexts<MYSQLParser::FieldContext>();
}

MYSQLParser::FieldContext* MYSQLParser::Field_listContext::field(size_t i) {
  return getRuleContext<MYSQLParser::FieldContext>(i);
}


size_t MYSQLParser::Field_listContext::getRuleIndex() const {
  return MYSQLParser::RuleField_list;
}

void MYSQLParser::Field_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterField_list(this);
}

void MYSQLParser::Field_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitField_list(this);
}


antlrcpp::Any MYSQLParser::Field_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitField_list(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::Field_listContext* MYSQLParser::field_list() {
  Field_listContext *_localctx = _tracker.createInstance<Field_listContext>(_ctx, getState());
  enterRule(_localctx, 14, MYSQLParser::RuleField_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(231);
    field();
    setState(236);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MYSQLParser::T__39) {
      setState(232);
      match(MYSQLParser::T__39);
      setState(233);
      field();
      setState(238);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldContext ------------------------------------------------------------------

MYSQLParser::FieldContext::FieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MYSQLParser::FieldContext::getRuleIndex() const {
  return MYSQLParser::RuleField;
}

void MYSQLParser::FieldContext::copyFrom(FieldContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Primary_key_fieldContext ------------------------------------------------------------------

MYSQLParser::IdentifiersContext* MYSQLParser::Primary_key_fieldContext::identifiers() {
  return getRuleContext<MYSQLParser::IdentifiersContext>(0);
}

tree::TerminalNode* MYSQLParser::Primary_key_fieldContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::Primary_key_fieldContext::Primary_key_fieldContext(FieldContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Primary_key_fieldContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimary_key_field(this);
}
void MYSQLParser::Primary_key_fieldContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimary_key_field(this);
}

antlrcpp::Any MYSQLParser::Primary_key_fieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitPrimary_key_field(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Foreign_key_fieldContext ------------------------------------------------------------------

std::vector<MYSQLParser::IdentifiersContext *> MYSQLParser::Foreign_key_fieldContext::identifiers() {
  return getRuleContexts<MYSQLParser::IdentifiersContext>();
}

MYSQLParser::IdentifiersContext* MYSQLParser::Foreign_key_fieldContext::identifiers(size_t i) {
  return getRuleContext<MYSQLParser::IdentifiersContext>(i);
}

std::vector<tree::TerminalNode *> MYSQLParser::Foreign_key_fieldContext::Identifier() {
  return getTokens(MYSQLParser::Identifier);
}

tree::TerminalNode* MYSQLParser::Foreign_key_fieldContext::Identifier(size_t i) {
  return getToken(MYSQLParser::Identifier, i);
}

MYSQLParser::Foreign_key_fieldContext::Foreign_key_fieldContext(FieldContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Foreign_key_fieldContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForeign_key_field(this);
}
void MYSQLParser::Foreign_key_fieldContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForeign_key_field(this);
}

antlrcpp::Any MYSQLParser::Foreign_key_fieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitForeign_key_field(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Normal_fieldContext ------------------------------------------------------------------

tree::TerminalNode* MYSQLParser::Normal_fieldContext::Identifier() {
  return getToken(MYSQLParser::Identifier, 0);
}

MYSQLParser::Type_Context* MYSQLParser::Normal_fieldContext::type_() {
  return getRuleContext<MYSQLParser::Type_Context>(0);
}

tree::TerminalNode* MYSQLParser::Normal_fieldContext::Null() {
  return getToken(MYSQLParser::Null, 0);
}

MYSQLParser::ValueContext* MYSQLParser::Normal_fieldContext::value() {
  return getRuleContext<MYSQLParser::ValueContext>(0);
}

MYSQLParser::Normal_fieldContext::Normal_fieldContext(FieldContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Normal_fieldContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNormal_field(this);
}
void MYSQLParser::Normal_fieldContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNormal_field(this);
}

antlrcpp::Any MYSQLParser::Normal_fieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitNormal_field(this);
  else
    return visitor->visitChildren(this);
}
MYSQLParser::FieldContext* MYSQLParser::field() {
  FieldContext *_localctx = _tracker.createInstance<FieldContext>(_ctx, getState());
  enterRule(_localctx, 16, MYSQLParser::RuleField);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(272);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MYSQLParser::Identifier: {
        _localctx = dynamic_cast<FieldContext *>(_tracker.createInstance<MYSQLParser::Normal_fieldContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(239);
        match(MYSQLParser::Identifier);
        setState(240);
        type_();
        setState(243);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MYSQLParser::T__40) {
          setState(241);
          match(MYSQLParser::T__40);
          setState(242);
          match(MYSQLParser::Null);
        }
        setState(247);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MYSQLParser::T__41) {
          setState(245);
          match(MYSQLParser::T__41);
          setState(246);
          value();
        }
        break;
      }

      case MYSQLParser::T__33: {
        _localctx = dynamic_cast<FieldContext *>(_tracker.createInstance<MYSQLParser::Primary_key_fieldContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(249);
        match(MYSQLParser::T__33);
        setState(250);
        match(MYSQLParser::T__34);
        setState(252);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MYSQLParser::Identifier) {
          setState(251);
          match(MYSQLParser::Identifier);
        }
        setState(254);
        match(MYSQLParser::T__15);
        setState(255);
        identifiers();
        setState(256);
        match(MYSQLParser::T__16);
        break;
      }

      case MYSQLParser::T__35: {
        _localctx = dynamic_cast<FieldContext *>(_tracker.createInstance<MYSQLParser::Foreign_key_fieldContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(258);
        match(MYSQLParser::T__35);
        setState(259);
        match(MYSQLParser::T__34);
        setState(261);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MYSQLParser::Identifier) {
          setState(260);
          match(MYSQLParser::Identifier);
        }
        setState(263);
        match(MYSQLParser::T__15);
        setState(264);
        identifiers();
        setState(265);
        match(MYSQLParser::T__16);
        setState(266);
        match(MYSQLParser::T__37);
        setState(267);
        match(MYSQLParser::Identifier);
        setState(268);
        match(MYSQLParser::T__15);
        setState(269);
        identifiers();
        setState(270);
        match(MYSQLParser::T__16);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Type_Context ------------------------------------------------------------------

MYSQLParser::Type_Context::Type_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MYSQLParser::Type_Context::Integer() {
  return getToken(MYSQLParser::Integer, 0);
}


size_t MYSQLParser::Type_Context::getRuleIndex() const {
  return MYSQLParser::RuleType_;
}

void MYSQLParser::Type_Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType_(this);
}

void MYSQLParser::Type_Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType_(this);
}


antlrcpp::Any MYSQLParser::Type_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitType_(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::Type_Context* MYSQLParser::type_() {
  Type_Context *_localctx = _tracker.createInstance<Type_Context>(_ctx, getState());
  enterRule(_localctx, 18, MYSQLParser::RuleType_);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(280);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MYSQLParser::T__42: {
        enterOuterAlt(_localctx, 1);
        setState(274);
        match(MYSQLParser::T__42);
        break;
      }

      case MYSQLParser::T__43: {
        enterOuterAlt(_localctx, 2);
        setState(275);
        match(MYSQLParser::T__43);
        setState(276);
        match(MYSQLParser::T__15);
        setState(277);
        match(MYSQLParser::Integer);
        setState(278);
        match(MYSQLParser::T__16);
        break;
      }

      case MYSQLParser::T__44: {
        enterOuterAlt(_localctx, 3);
        setState(279);
        match(MYSQLParser::T__44);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Value_listsContext ------------------------------------------------------------------

MYSQLParser::Value_listsContext::Value_listsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MYSQLParser::Value_listContext *> MYSQLParser::Value_listsContext::value_list() {
  return getRuleContexts<MYSQLParser::Value_listContext>();
}

MYSQLParser::Value_listContext* MYSQLParser::Value_listsContext::value_list(size_t i) {
  return getRuleContext<MYSQLParser::Value_listContext>(i);
}


size_t MYSQLParser::Value_listsContext::getRuleIndex() const {
  return MYSQLParser::RuleValue_lists;
}

void MYSQLParser::Value_listsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue_lists(this);
}

void MYSQLParser::Value_listsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue_lists(this);
}


antlrcpp::Any MYSQLParser::Value_listsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitValue_lists(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::Value_listsContext* MYSQLParser::value_lists() {
  Value_listsContext *_localctx = _tracker.createInstance<Value_listsContext>(_ctx, getState());
  enterRule(_localctx, 20, MYSQLParser::RuleValue_lists);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(282);
    value_list();
    setState(287);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MYSQLParser::T__39) {
      setState(283);
      match(MYSQLParser::T__39);
      setState(284);
      value_list();
      setState(289);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Value_listContext ------------------------------------------------------------------

MYSQLParser::Value_listContext::Value_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MYSQLParser::ValueContext *> MYSQLParser::Value_listContext::value() {
  return getRuleContexts<MYSQLParser::ValueContext>();
}

MYSQLParser::ValueContext* MYSQLParser::Value_listContext::value(size_t i) {
  return getRuleContext<MYSQLParser::ValueContext>(i);
}


size_t MYSQLParser::Value_listContext::getRuleIndex() const {
  return MYSQLParser::RuleValue_list;
}

void MYSQLParser::Value_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue_list(this);
}

void MYSQLParser::Value_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue_list(this);
}


antlrcpp::Any MYSQLParser::Value_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitValue_list(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::Value_listContext* MYSQLParser::value_list() {
  Value_listContext *_localctx = _tracker.createInstance<Value_listContext>(_ctx, getState());
  enterRule(_localctx, 22, MYSQLParser::RuleValue_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(290);
    match(MYSQLParser::T__15);
    setState(291);
    value();
    setState(296);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MYSQLParser::T__39) {
      setState(292);
      match(MYSQLParser::T__39);
      setState(293);
      value();
      setState(298);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(299);
    match(MYSQLParser::T__16);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

MYSQLParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MYSQLParser::ValueContext::Integer() {
  return getToken(MYSQLParser::Integer, 0);
}

tree::TerminalNode* MYSQLParser::ValueContext::String() {
  return getToken(MYSQLParser::String, 0);
}

tree::TerminalNode* MYSQLParser::ValueContext::Float() {
  return getToken(MYSQLParser::Float, 0);
}

tree::TerminalNode* MYSQLParser::ValueContext::Null() {
  return getToken(MYSQLParser::Null, 0);
}


size_t MYSQLParser::ValueContext::getRuleIndex() const {
  return MYSQLParser::RuleValue;
}

void MYSQLParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void MYSQLParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}


antlrcpp::Any MYSQLParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::ValueContext* MYSQLParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 24, MYSQLParser::RuleValue);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(301);
    _la = _input->LA(1);
    if (!(((((_la - 63) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 63)) & ((1ULL << (MYSQLParser::Null - 63))
      | (1ULL << (MYSQLParser::Integer - 63))
      | (1ULL << (MYSQLParser::String - 63))
      | (1ULL << (MYSQLParser::Float - 63)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Where_and_clauseContext ------------------------------------------------------------------

MYSQLParser::Where_and_clauseContext::Where_and_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MYSQLParser::Where_clauseContext *> MYSQLParser::Where_and_clauseContext::where_clause() {
  return getRuleContexts<MYSQLParser::Where_clauseContext>();
}

MYSQLParser::Where_clauseContext* MYSQLParser::Where_and_clauseContext::where_clause(size_t i) {
  return getRuleContext<MYSQLParser::Where_clauseContext>(i);
}


size_t MYSQLParser::Where_and_clauseContext::getRuleIndex() const {
  return MYSQLParser::RuleWhere_and_clause;
}

void MYSQLParser::Where_and_clauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhere_and_clause(this);
}

void MYSQLParser::Where_and_clauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhere_and_clause(this);
}


antlrcpp::Any MYSQLParser::Where_and_clauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitWhere_and_clause(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::Where_and_clauseContext* MYSQLParser::where_and_clause() {
  Where_and_clauseContext *_localctx = _tracker.createInstance<Where_and_clauseContext>(_ctx, getState());
  enterRule(_localctx, 26, MYSQLParser::RuleWhere_and_clause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(303);
    where_clause();
    setState(308);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MYSQLParser::T__45) {
      setState(304);
      match(MYSQLParser::T__45);
      setState(305);
      where_clause();
      setState(310);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Where_clauseContext ------------------------------------------------------------------

MYSQLParser::Where_clauseContext::Where_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MYSQLParser::Where_clauseContext::getRuleIndex() const {
  return MYSQLParser::RuleWhere_clause;
}

void MYSQLParser::Where_clauseContext::copyFrom(Where_clauseContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Where_in_listContext ------------------------------------------------------------------

MYSQLParser::ColumnContext* MYSQLParser::Where_in_listContext::column() {
  return getRuleContext<MYSQLParser::ColumnContext>(0);
}

MYSQLParser::Value_listContext* MYSQLParser::Where_in_listContext::value_list() {
  return getRuleContext<MYSQLParser::Value_listContext>(0);
}

MYSQLParser::Where_in_listContext::Where_in_listContext(Where_clauseContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Where_in_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhere_in_list(this);
}
void MYSQLParser::Where_in_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhere_in_list(this);
}

antlrcpp::Any MYSQLParser::Where_in_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitWhere_in_list(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Where_operator_selectContext ------------------------------------------------------------------

MYSQLParser::ColumnContext* MYSQLParser::Where_operator_selectContext::column() {
  return getRuleContext<MYSQLParser::ColumnContext>(0);
}

MYSQLParser::Operator_Context* MYSQLParser::Where_operator_selectContext::operator_() {
  return getRuleContext<MYSQLParser::Operator_Context>(0);
}

MYSQLParser::Select_tableContext* MYSQLParser::Where_operator_selectContext::select_table() {
  return getRuleContext<MYSQLParser::Select_tableContext>(0);
}

MYSQLParser::Where_operator_selectContext::Where_operator_selectContext(Where_clauseContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Where_operator_selectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhere_operator_select(this);
}
void MYSQLParser::Where_operator_selectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhere_operator_select(this);
}

antlrcpp::Any MYSQLParser::Where_operator_selectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitWhere_operator_select(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Where_nullContext ------------------------------------------------------------------

MYSQLParser::ColumnContext* MYSQLParser::Where_nullContext::column() {
  return getRuleContext<MYSQLParser::ColumnContext>(0);
}

tree::TerminalNode* MYSQLParser::Where_nullContext::Null() {
  return getToken(MYSQLParser::Null, 0);
}

MYSQLParser::Where_nullContext::Where_nullContext(Where_clauseContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Where_nullContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhere_null(this);
}
void MYSQLParser::Where_nullContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhere_null(this);
}

antlrcpp::Any MYSQLParser::Where_nullContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitWhere_null(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Where_operator_expressionContext ------------------------------------------------------------------

MYSQLParser::ColumnContext* MYSQLParser::Where_operator_expressionContext::column() {
  return getRuleContext<MYSQLParser::ColumnContext>(0);
}

MYSQLParser::Operator_Context* MYSQLParser::Where_operator_expressionContext::operator_() {
  return getRuleContext<MYSQLParser::Operator_Context>(0);
}

MYSQLParser::ExpressionContext* MYSQLParser::Where_operator_expressionContext::expression() {
  return getRuleContext<MYSQLParser::ExpressionContext>(0);
}

MYSQLParser::Where_operator_expressionContext::Where_operator_expressionContext(Where_clauseContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Where_operator_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhere_operator_expression(this);
}
void MYSQLParser::Where_operator_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhere_operator_expression(this);
}

antlrcpp::Any MYSQLParser::Where_operator_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitWhere_operator_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Where_in_selectContext ------------------------------------------------------------------

MYSQLParser::ColumnContext* MYSQLParser::Where_in_selectContext::column() {
  return getRuleContext<MYSQLParser::ColumnContext>(0);
}

MYSQLParser::Select_tableContext* MYSQLParser::Where_in_selectContext::select_table() {
  return getRuleContext<MYSQLParser::Select_tableContext>(0);
}

MYSQLParser::Where_in_selectContext::Where_in_selectContext(Where_clauseContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Where_in_selectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhere_in_select(this);
}
void MYSQLParser::Where_in_selectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhere_in_select(this);
}

antlrcpp::Any MYSQLParser::Where_in_selectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitWhere_in_select(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Where_like_stringContext ------------------------------------------------------------------

MYSQLParser::ColumnContext* MYSQLParser::Where_like_stringContext::column() {
  return getRuleContext<MYSQLParser::ColumnContext>(0);
}

tree::TerminalNode* MYSQLParser::Where_like_stringContext::String() {
  return getToken(MYSQLParser::String, 0);
}

MYSQLParser::Where_like_stringContext::Where_like_stringContext(Where_clauseContext *ctx) { copyFrom(ctx); }

void MYSQLParser::Where_like_stringContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhere_like_string(this);
}
void MYSQLParser::Where_like_stringContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhere_like_string(this);
}

antlrcpp::Any MYSQLParser::Where_like_stringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitWhere_like_string(this);
  else
    return visitor->visitChildren(this);
}
MYSQLParser::Where_clauseContext* MYSQLParser::where_clause() {
  Where_clauseContext *_localctx = _tracker.createInstance<Where_clauseContext>(_ctx, getState());
  enterRule(_localctx, 28, MYSQLParser::RuleWhere_clause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(342);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<Where_clauseContext *>(_tracker.createInstance<MYSQLParser::Where_operator_expressionContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(311);
      column();
      setState(312);
      operator_();
      setState(313);
      expression();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<Where_clauseContext *>(_tracker.createInstance<MYSQLParser::Where_operator_selectContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(315);
      column();
      setState(316);
      operator_();
      setState(317);
      match(MYSQLParser::T__15);
      setState(318);
      select_table();
      setState(319);
      match(MYSQLParser::T__16);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<Where_clauseContext *>(_tracker.createInstance<MYSQLParser::Where_nullContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(321);
      column();
      setState(322);
      match(MYSQLParser::T__46);
      setState(324);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MYSQLParser::T__40) {
        setState(323);
        match(MYSQLParser::T__40);
      }
      setState(326);
      match(MYSQLParser::Null);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<Where_clauseContext *>(_tracker.createInstance<MYSQLParser::Where_in_listContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(328);
      column();
      setState(329);
      match(MYSQLParser::T__47);
      setState(330);
      value_list();
      break;
    }

    case 5: {
      _localctx = dynamic_cast<Where_clauseContext *>(_tracker.createInstance<MYSQLParser::Where_in_selectContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(332);
      column();
      setState(333);
      match(MYSQLParser::T__47);
      setState(334);
      match(MYSQLParser::T__15);
      setState(335);
      select_table();
      setState(336);
      match(MYSQLParser::T__16);
      break;
    }

    case 6: {
      _localctx = dynamic_cast<Where_clauseContext *>(_tracker.createInstance<MYSQLParser::Where_like_stringContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(338);
      column();
      setState(339);
      match(MYSQLParser::T__48);
      setState(340);
      match(MYSQLParser::String);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnContext ------------------------------------------------------------------

MYSQLParser::ColumnContext::ColumnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MYSQLParser::ColumnContext::Identifier() {
  return getTokens(MYSQLParser::Identifier);
}

tree::TerminalNode* MYSQLParser::ColumnContext::Identifier(size_t i) {
  return getToken(MYSQLParser::Identifier, i);
}


size_t MYSQLParser::ColumnContext::getRuleIndex() const {
  return MYSQLParser::RuleColumn;
}

void MYSQLParser::ColumnContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColumn(this);
}

void MYSQLParser::ColumnContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColumn(this);
}


antlrcpp::Any MYSQLParser::ColumnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitColumn(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::ColumnContext* MYSQLParser::column() {
  ColumnContext *_localctx = _tracker.createInstance<ColumnContext>(_ctx, getState());
  enterRule(_localctx, 30, MYSQLParser::RuleColumn);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(344);
    match(MYSQLParser::Identifier);
    setState(345);
    match(MYSQLParser::T__49);
    setState(346);
    match(MYSQLParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

MYSQLParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MYSQLParser::ValueContext* MYSQLParser::ExpressionContext::value() {
  return getRuleContext<MYSQLParser::ValueContext>(0);
}

MYSQLParser::ColumnContext* MYSQLParser::ExpressionContext::column() {
  return getRuleContext<MYSQLParser::ColumnContext>(0);
}


size_t MYSQLParser::ExpressionContext::getRuleIndex() const {
  return MYSQLParser::RuleExpression;
}

void MYSQLParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void MYSQLParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


antlrcpp::Any MYSQLParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::ExpressionContext* MYSQLParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 32, MYSQLParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(350);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MYSQLParser::Null:
      case MYSQLParser::Integer:
      case MYSQLParser::String:
      case MYSQLParser::Float: {
        enterOuterAlt(_localctx, 1);
        setState(348);
        value();
        break;
      }

      case MYSQLParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(349);
        column();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Set_clauseContext ------------------------------------------------------------------

MYSQLParser::Set_clauseContext::Set_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MYSQLParser::Set_clauseContext::Identifier() {
  return getTokens(MYSQLParser::Identifier);
}

tree::TerminalNode* MYSQLParser::Set_clauseContext::Identifier(size_t i) {
  return getToken(MYSQLParser::Identifier, i);
}

std::vector<tree::TerminalNode *> MYSQLParser::Set_clauseContext::EqualOrAssign() {
  return getTokens(MYSQLParser::EqualOrAssign);
}

tree::TerminalNode* MYSQLParser::Set_clauseContext::EqualOrAssign(size_t i) {
  return getToken(MYSQLParser::EqualOrAssign, i);
}

std::vector<MYSQLParser::ValueContext *> MYSQLParser::Set_clauseContext::value() {
  return getRuleContexts<MYSQLParser::ValueContext>();
}

MYSQLParser::ValueContext* MYSQLParser::Set_clauseContext::value(size_t i) {
  return getRuleContext<MYSQLParser::ValueContext>(i);
}


size_t MYSQLParser::Set_clauseContext::getRuleIndex() const {
  return MYSQLParser::RuleSet_clause;
}

void MYSQLParser::Set_clauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSet_clause(this);
}

void MYSQLParser::Set_clauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSet_clause(this);
}


antlrcpp::Any MYSQLParser::Set_clauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitSet_clause(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::Set_clauseContext* MYSQLParser::set_clause() {
  Set_clauseContext *_localctx = _tracker.createInstance<Set_clauseContext>(_ctx, getState());
  enterRule(_localctx, 34, MYSQLParser::RuleSet_clause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(352);
    match(MYSQLParser::Identifier);
    setState(353);
    match(MYSQLParser::EqualOrAssign);
    setState(354);
    value();
    setState(361);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MYSQLParser::T__39) {
      setState(355);
      match(MYSQLParser::T__39);
      setState(356);
      match(MYSQLParser::Identifier);
      setState(357);
      match(MYSQLParser::EqualOrAssign);
      setState(358);
      value();
      setState(363);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorsContext ------------------------------------------------------------------

MYSQLParser::SelectorsContext::SelectorsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MYSQLParser::SelectorContext *> MYSQLParser::SelectorsContext::selector() {
  return getRuleContexts<MYSQLParser::SelectorContext>();
}

MYSQLParser::SelectorContext* MYSQLParser::SelectorsContext::selector(size_t i) {
  return getRuleContext<MYSQLParser::SelectorContext>(i);
}


size_t MYSQLParser::SelectorsContext::getRuleIndex() const {
  return MYSQLParser::RuleSelectors;
}

void MYSQLParser::SelectorsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectors(this);
}

void MYSQLParser::SelectorsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectors(this);
}


antlrcpp::Any MYSQLParser::SelectorsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitSelectors(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::SelectorsContext* MYSQLParser::selectors() {
  SelectorsContext *_localctx = _tracker.createInstance<SelectorsContext>(_ctx, getState());
  enterRule(_localctx, 36, MYSQLParser::RuleSelectors);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(373);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MYSQLParser::T__50: {
        enterOuterAlt(_localctx, 1);
        setState(364);
        match(MYSQLParser::T__50);
        break;
      }

      case MYSQLParser::Count:
      case MYSQLParser::Average:
      case MYSQLParser::Max:
      case MYSQLParser::Min:
      case MYSQLParser::Sum:
      case MYSQLParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(365);
        selector();
        setState(370);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == MYSQLParser::T__39) {
          setState(366);
          match(MYSQLParser::T__39);
          setState(367);
          selector();
          setState(372);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorContext ------------------------------------------------------------------

MYSQLParser::SelectorContext::SelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MYSQLParser::ColumnContext* MYSQLParser::SelectorContext::column() {
  return getRuleContext<MYSQLParser::ColumnContext>(0);
}

MYSQLParser::AggregatorContext* MYSQLParser::SelectorContext::aggregator() {
  return getRuleContext<MYSQLParser::AggregatorContext>(0);
}

tree::TerminalNode* MYSQLParser::SelectorContext::Count() {
  return getToken(MYSQLParser::Count, 0);
}


size_t MYSQLParser::SelectorContext::getRuleIndex() const {
  return MYSQLParser::RuleSelector;
}

void MYSQLParser::SelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelector(this);
}

void MYSQLParser::SelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelector(this);
}


antlrcpp::Any MYSQLParser::SelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitSelector(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::SelectorContext* MYSQLParser::selector() {
  SelectorContext *_localctx = _tracker.createInstance<SelectorContext>(_ctx, getState());
  enterRule(_localctx, 38, MYSQLParser::RuleSelector);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(385);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(375);
      column();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(376);
      aggregator();
      setState(377);
      match(MYSQLParser::T__15);
      setState(378);
      column();
      setState(379);
      match(MYSQLParser::T__16);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(381);
      match(MYSQLParser::Count);
      setState(382);
      match(MYSQLParser::T__15);
      setState(383);
      match(MYSQLParser::T__50);
      setState(384);
      match(MYSQLParser::T__16);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifiersContext ------------------------------------------------------------------

MYSQLParser::IdentifiersContext::IdentifiersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MYSQLParser::IdentifiersContext::Identifier() {
  return getTokens(MYSQLParser::Identifier);
}

tree::TerminalNode* MYSQLParser::IdentifiersContext::Identifier(size_t i) {
  return getToken(MYSQLParser::Identifier, i);
}


size_t MYSQLParser::IdentifiersContext::getRuleIndex() const {
  return MYSQLParser::RuleIdentifiers;
}

void MYSQLParser::IdentifiersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifiers(this);
}

void MYSQLParser::IdentifiersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifiers(this);
}


antlrcpp::Any MYSQLParser::IdentifiersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitIdentifiers(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::IdentifiersContext* MYSQLParser::identifiers() {
  IdentifiersContext *_localctx = _tracker.createInstance<IdentifiersContext>(_ctx, getState());
  enterRule(_localctx, 40, MYSQLParser::RuleIdentifiers);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(387);
    match(MYSQLParser::Identifier);
    setState(392);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MYSQLParser::T__39) {
      setState(388);
      match(MYSQLParser::T__39);
      setState(389);
      match(MYSQLParser::Identifier);
      setState(394);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Operator_Context ------------------------------------------------------------------

MYSQLParser::Operator_Context::Operator_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MYSQLParser::Operator_Context::EqualOrAssign() {
  return getToken(MYSQLParser::EqualOrAssign, 0);
}

tree::TerminalNode* MYSQLParser::Operator_Context::Less() {
  return getToken(MYSQLParser::Less, 0);
}

tree::TerminalNode* MYSQLParser::Operator_Context::LessEqual() {
  return getToken(MYSQLParser::LessEqual, 0);
}

tree::TerminalNode* MYSQLParser::Operator_Context::Greater() {
  return getToken(MYSQLParser::Greater, 0);
}

tree::TerminalNode* MYSQLParser::Operator_Context::GreaterEqual() {
  return getToken(MYSQLParser::GreaterEqual, 0);
}

tree::TerminalNode* MYSQLParser::Operator_Context::NotEqual() {
  return getToken(MYSQLParser::NotEqual, 0);
}


size_t MYSQLParser::Operator_Context::getRuleIndex() const {
  return MYSQLParser::RuleOperator_;
}

void MYSQLParser::Operator_Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperator_(this);
}

void MYSQLParser::Operator_Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperator_(this);
}


antlrcpp::Any MYSQLParser::Operator_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitOperator_(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::Operator_Context* MYSQLParser::operator_() {
  Operator_Context *_localctx = _tracker.createInstance<Operator_Context>(_ctx, getState());
  enterRule(_localctx, 42, MYSQLParser::RuleOperator_);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(395);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << MYSQLParser::EqualOrAssign)
      | (1ULL << MYSQLParser::Less)
      | (1ULL << MYSQLParser::LessEqual)
      | (1ULL << MYSQLParser::Greater)
      | (1ULL << MYSQLParser::GreaterEqual)
      | (1ULL << MYSQLParser::NotEqual))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AggregatorContext ------------------------------------------------------------------

MYSQLParser::AggregatorContext::AggregatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MYSQLParser::AggregatorContext::Count() {
  return getToken(MYSQLParser::Count, 0);
}

tree::TerminalNode* MYSQLParser::AggregatorContext::Average() {
  return getToken(MYSQLParser::Average, 0);
}

tree::TerminalNode* MYSQLParser::AggregatorContext::Max() {
  return getToken(MYSQLParser::Max, 0);
}

tree::TerminalNode* MYSQLParser::AggregatorContext::Min() {
  return getToken(MYSQLParser::Min, 0);
}

tree::TerminalNode* MYSQLParser::AggregatorContext::Sum() {
  return getToken(MYSQLParser::Sum, 0);
}


size_t MYSQLParser::AggregatorContext::getRuleIndex() const {
  return MYSQLParser::RuleAggregator;
}

void MYSQLParser::AggregatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAggregator(this);
}

void MYSQLParser::AggregatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MYSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAggregator(this);
}


antlrcpp::Any MYSQLParser::AggregatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MYSQLVisitor*>(visitor))
    return parserVisitor->visitAggregator(this);
  else
    return visitor->visitChildren(this);
}

MYSQLParser::AggregatorContext* MYSQLParser::aggregator() {
  AggregatorContext *_localctx = _tracker.createInstance<AggregatorContext>(_ctx, getState());
  enterRule(_localctx, 44, MYSQLParser::RuleAggregator);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(397);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << MYSQLParser::Count)
      | (1ULL << MYSQLParser::Average)
      | (1ULL << MYSQLParser::Max)
      | (1ULL << MYSQLParser::Min)
      | (1ULL << MYSQLParser::Sum))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> MYSQLParser::_decisionToDFA;
atn::PredictionContextCache MYSQLParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN MYSQLParser::_atn;
std::vector<uint16_t> MYSQLParser::_serializedATN;

std::vector<std::string> MYSQLParser::_ruleNames = {
  "program", "statement", "db_statement", "io_statement", "table_statement", 
  "select_table", "alter_statement", "field_list", "field", "type_", "value_lists", 
  "value_list", "value", "where_and_clause", "where_clause", "column", "expression", 
  "set_clause", "selectors", "selector", "identifiers", "operator_", "aggregator"
};

std::vector<std::string> MYSQLParser::_literalNames = {
  "", "';'", "'CREATE'", "'DATABASE'", "'DROP'", "'SHOW'", "'DATABASES'", 
  "'USE'", "'TABLES'", "'INDEXES'", "'LOAD'", "'FROM'", "'FILE'", "'TO'", 
  "'TABLE'", "'DUMP'", "'('", "')'", "'DESC'", "'INSERT'", "'INTO'", "'VALUES'", 
  "'DELETE'", "'WHERE'", "'UPDATE'", "'SET'", "'SELECT'", "'GROUP'", "'BY'", 
  "'LIMIT'", "'OFFSET'", "'ALTER'", "'ADD'", "'INDEX'", "'PRIMARY'", "'KEY'", 
  "'FOREIGN'", "'CONSTRAINT'", "'REFERENCES'", "'UNIQUE'", "','", "'NOT'", 
  "'DEFAULT'", "'INT'", "'VARCHAR'", "'FLOAT'", "'AND'", "'IS'", "'IN'", 
  "'LIKE'", "'.'", "'*'", "'='", "'<'", "'<='", "'>'", "'>='", "'<>'", "'COUNT'", 
  "'AVG'", "'MAX'", "'MIN'", "'SUM'", "'NULL'"
};

std::vector<std::string> MYSQLParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "EqualOrAssign", 
  "Less", "LessEqual", "Greater", "GreaterEqual", "NotEqual", "Count", "Average", 
  "Max", "Min", "Sum", "Null", "Identifier", "Integer", "String", "Float", 
  "Whitespace", "Annotation"
};

dfa::Vocabulary MYSQLParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> MYSQLParser::_tokenNames;

MYSQLParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x47, 0x192, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x3, 0x2, 0x7, 0x2, 0x32, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x35, 
    0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x49, 0xa, 
    0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x5, 0x4, 0x59, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x69, 0xa, 0x5, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x5, 0x6, 0x89, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x91, 0xa, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x5, 0x7, 0x96, 0xa, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x5, 0x7, 0x9c, 0xa, 0x7, 0x5, 0x7, 0x9e, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0xb9, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x5, 0x8, 0xe8, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 
    0xed, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0xf0, 0xb, 0x9, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0xf6, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 
    0xa, 0xfa, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0xff, 0xa, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x5, 0xa, 0x108, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x113, 0xa, 
    0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 
    0xb, 0x11b, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x120, 
    0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0x123, 0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x7, 0xd, 0x129, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0x12c, 
    0xb, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 
    0x3, 0xf, 0x7, 0xf, 0x135, 0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0x138, 0xb, 
    0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x5, 0x10, 0x147, 0xa, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 
    0x5, 0x10, 0x159, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x161, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0x16a, 
    0xa, 0x13, 0xc, 0x13, 0xe, 0x13, 0x16d, 0xb, 0x13, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 0x173, 0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 
    0x176, 0xb, 0x14, 0x5, 0x14, 0x178, 0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 
    0x15, 0x3, 0x15, 0x5, 0x15, 0x184, 0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x7, 0x16, 0x189, 0xa, 0x16, 0xc, 0x16, 0xe, 0x16, 0x18c, 
    0xb, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x2, 
    0x2, 0x19, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 
    0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 
    0x2, 0x5, 0x4, 0x2, 0x41, 0x41, 0x43, 0x45, 0x3, 0x2, 0x36, 0x3b, 0x3, 
    0x2, 0x3c, 0x40, 0x2, 0x1b0, 0x2, 0x33, 0x3, 0x2, 0x2, 0x2, 0x4, 0x48, 
    0x3, 0x2, 0x2, 0x2, 0x6, 0x58, 0x3, 0x2, 0x2, 0x2, 0x8, 0x68, 0x3, 0x2, 
    0x2, 0x2, 0xa, 0x88, 0x3, 0x2, 0x2, 0x2, 0xc, 0x8a, 0x3, 0x2, 0x2, 0x2, 
    0xe, 0xe7, 0x3, 0x2, 0x2, 0x2, 0x10, 0xe9, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0x112, 0x3, 0x2, 0x2, 0x2, 0x14, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x16, 0x11c, 
    0x3, 0x2, 0x2, 0x2, 0x18, 0x124, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x12f, 0x3, 
    0x2, 0x2, 0x2, 0x1c, 0x131, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x158, 0x3, 0x2, 
    0x2, 0x2, 0x20, 0x15a, 0x3, 0x2, 0x2, 0x2, 0x22, 0x160, 0x3, 0x2, 0x2, 
    0x2, 0x24, 0x162, 0x3, 0x2, 0x2, 0x2, 0x26, 0x177, 0x3, 0x2, 0x2, 0x2, 
    0x28, 0x183, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x185, 0x3, 0x2, 0x2, 0x2, 0x2c, 
    0x18d, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x18f, 0x3, 0x2, 0x2, 0x2, 0x30, 0x32, 
    0x5, 0x4, 0x3, 0x2, 0x31, 0x30, 0x3, 0x2, 0x2, 0x2, 0x32, 0x35, 0x3, 
    0x2, 0x2, 0x2, 0x33, 0x31, 0x3, 0x2, 0x2, 0x2, 0x33, 0x34, 0x3, 0x2, 
    0x2, 0x2, 0x34, 0x36, 0x3, 0x2, 0x2, 0x2, 0x35, 0x33, 0x3, 0x2, 0x2, 
    0x2, 0x36, 0x37, 0x7, 0x2, 0x2, 0x3, 0x37, 0x3, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0x39, 0x5, 0x6, 0x4, 0x2, 0x39, 0x3a, 0x7, 0x3, 0x2, 0x2, 0x3a, 
    0x49, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x3c, 0x5, 0x8, 0x5, 0x2, 0x3c, 0x3d, 
    0x7, 0x3, 0x2, 0x2, 0x3d, 0x49, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3f, 0x5, 
    0xa, 0x6, 0x2, 0x3f, 0x40, 0x7, 0x3, 0x2, 0x2, 0x40, 0x49, 0x3, 0x2, 
    0x2, 0x2, 0x41, 0x42, 0x5, 0xe, 0x8, 0x2, 0x42, 0x43, 0x7, 0x3, 0x2, 
    0x2, 0x43, 0x49, 0x3, 0x2, 0x2, 0x2, 0x44, 0x45, 0x7, 0x47, 0x2, 0x2, 
    0x45, 0x49, 0x7, 0x3, 0x2, 0x2, 0x46, 0x47, 0x7, 0x41, 0x2, 0x2, 0x47, 
    0x49, 0x7, 0x3, 0x2, 0x2, 0x48, 0x38, 0x3, 0x2, 0x2, 0x2, 0x48, 0x3b, 
    0x3, 0x2, 0x2, 0x2, 0x48, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x48, 0x41, 0x3, 
    0x2, 0x2, 0x2, 0x48, 0x44, 0x3, 0x2, 0x2, 0x2, 0x48, 0x46, 0x3, 0x2, 
    0x2, 0x2, 0x49, 0x5, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x7, 0x4, 0x2, 
    0x2, 0x4b, 0x4c, 0x7, 0x5, 0x2, 0x2, 0x4c, 0x59, 0x7, 0x42, 0x2, 0x2, 
    0x4d, 0x4e, 0x7, 0x6, 0x2, 0x2, 0x4e, 0x4f, 0x7, 0x5, 0x2, 0x2, 0x4f, 
    0x59, 0x7, 0x42, 0x2, 0x2, 0x50, 0x51, 0x7, 0x7, 0x2, 0x2, 0x51, 0x59, 
    0x7, 0x8, 0x2, 0x2, 0x52, 0x53, 0x7, 0x9, 0x2, 0x2, 0x53, 0x59, 0x7, 
    0x42, 0x2, 0x2, 0x54, 0x55, 0x7, 0x7, 0x2, 0x2, 0x55, 0x59, 0x7, 0xa, 
    0x2, 0x2, 0x56, 0x57, 0x7, 0x7, 0x2, 0x2, 0x57, 0x59, 0x7, 0xb, 0x2, 
    0x2, 0x58, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x58, 0x4d, 0x3, 0x2, 0x2, 0x2, 
    0x58, 0x50, 0x3, 0x2, 0x2, 0x2, 0x58, 0x52, 0x3, 0x2, 0x2, 0x2, 0x58, 
    0x54, 0x3, 0x2, 0x2, 0x2, 0x58, 0x56, 0x3, 0x2, 0x2, 0x2, 0x59, 0x7, 
    0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x7, 0xc, 0x2, 0x2, 0x5b, 0x5c, 0x7, 
    0xd, 0x2, 0x2, 0x5c, 0x5d, 0x7, 0xe, 0x2, 0x2, 0x5d, 0x5e, 0x7, 0x44, 
    0x2, 0x2, 0x5e, 0x5f, 0x7, 0xf, 0x2, 0x2, 0x5f, 0x60, 0x7, 0x10, 0x2, 
    0x2, 0x60, 0x69, 0x7, 0x42, 0x2, 0x2, 0x61, 0x62, 0x7, 0x11, 0x2, 0x2, 
    0x62, 0x63, 0x7, 0xf, 0x2, 0x2, 0x63, 0x64, 0x7, 0xe, 0x2, 0x2, 0x64, 
    0x65, 0x7, 0x44, 0x2, 0x2, 0x65, 0x66, 0x7, 0xd, 0x2, 0x2, 0x66, 0x67, 
    0x7, 0x10, 0x2, 0x2, 0x67, 0x69, 0x7, 0x42, 0x2, 0x2, 0x68, 0x5a, 0x3, 
    0x2, 0x2, 0x2, 0x68, 0x61, 0x3, 0x2, 0x2, 0x2, 0x69, 0x9, 0x3, 0x2, 
    0x2, 0x2, 0x6a, 0x6b, 0x7, 0x4, 0x2, 0x2, 0x6b, 0x6c, 0x7, 0x10, 0x2, 
    0x2, 0x6c, 0x6d, 0x7, 0x42, 0x2, 0x2, 0x6d, 0x6e, 0x7, 0x12, 0x2, 0x2, 
    0x6e, 0x6f, 0x5, 0x10, 0x9, 0x2, 0x6f, 0x70, 0x7, 0x13, 0x2, 0x2, 0x70, 
    0x89, 0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x7, 0x6, 0x2, 0x2, 0x72, 0x73, 
    0x7, 0x10, 0x2, 0x2, 0x73, 0x89, 0x7, 0x42, 0x2, 0x2, 0x74, 0x75, 0x7, 
    0x14, 0x2, 0x2, 0x75, 0x89, 0x7, 0x42, 0x2, 0x2, 0x76, 0x77, 0x7, 0x15, 
    0x2, 0x2, 0x77, 0x78, 0x7, 0x16, 0x2, 0x2, 0x78, 0x79, 0x7, 0x42, 0x2, 
    0x2, 0x79, 0x7a, 0x7, 0x17, 0x2, 0x2, 0x7a, 0x89, 0x5, 0x16, 0xc, 0x2, 
    0x7b, 0x7c, 0x7, 0x18, 0x2, 0x2, 0x7c, 0x7d, 0x7, 0xd, 0x2, 0x2, 0x7d, 
    0x7e, 0x7, 0x42, 0x2, 0x2, 0x7e, 0x7f, 0x7, 0x19, 0x2, 0x2, 0x7f, 0x89, 
    0x5, 0x1c, 0xf, 0x2, 0x80, 0x81, 0x7, 0x1a, 0x2, 0x2, 0x81, 0x82, 0x7, 
    0x42, 0x2, 0x2, 0x82, 0x83, 0x7, 0x1b, 0x2, 0x2, 0x83, 0x84, 0x5, 0x24, 
    0x13, 0x2, 0x84, 0x85, 0x7, 0x19, 0x2, 0x2, 0x85, 0x86, 0x5, 0x1c, 0xf, 
    0x2, 0x86, 0x89, 0x3, 0x2, 0x2, 0x2, 0x87, 0x89, 0x5, 0xc, 0x7, 0x2, 
    0x88, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x88, 0x71, 0x3, 0x2, 0x2, 0x2, 0x88, 
    0x74, 0x3, 0x2, 0x2, 0x2, 0x88, 0x76, 0x3, 0x2, 0x2, 0x2, 0x88, 0x7b, 
    0x3, 0x2, 0x2, 0x2, 0x88, 0x80, 0x3, 0x2, 0x2, 0x2, 0x88, 0x87, 0x3, 
    0x2, 0x2, 0x2, 0x89, 0xb, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x8b, 0x7, 0x1c, 
    0x2, 0x2, 0x8b, 0x8c, 0x5, 0x26, 0x14, 0x2, 0x8c, 0x8d, 0x7, 0xd, 0x2, 
    0x2, 0x8d, 0x90, 0x5, 0x2a, 0x16, 0x2, 0x8e, 0x8f, 0x7, 0x19, 0x2, 0x2, 
    0x8f, 0x91, 0x5, 0x1c, 0xf, 0x2, 0x90, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x90, 
    0x91, 0x3, 0x2, 0x2, 0x2, 0x91, 0x95, 0x3, 0x2, 0x2, 0x2, 0x92, 0x93, 
    0x7, 0x1d, 0x2, 0x2, 0x93, 0x94, 0x7, 0x1e, 0x2, 0x2, 0x94, 0x96, 0x5, 
    0x20, 0x11, 0x2, 0x95, 0x92, 0x3, 0x2, 0x2, 0x2, 0x95, 0x96, 0x3, 0x2, 
    0x2, 0x2, 0x96, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x97, 0x98, 0x7, 0x1f, 0x2, 
    0x2, 0x98, 0x9b, 0x7, 0x43, 0x2, 0x2, 0x99, 0x9a, 0x7, 0x20, 0x2, 0x2, 
    0x9a, 0x9c, 0x7, 0x43, 0x2, 0x2, 0x9b, 0x99, 0x3, 0x2, 0x2, 0x2, 0x9b, 
    0x9c, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x97, 
    0x3, 0x2, 0x2, 0x2, 0x9d, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x9e, 0xd, 0x3, 
    0x2, 0x2, 0x2, 0x9f, 0xa0, 0x7, 0x21, 0x2, 0x2, 0xa0, 0xa1, 0x7, 0x10, 
    0x2, 0x2, 0xa1, 0xa2, 0x7, 0x42, 0x2, 0x2, 0xa2, 0xa3, 0x7, 0x22, 0x2, 
    0x2, 0xa3, 0xa4, 0x7, 0x23, 0x2, 0x2, 0xa4, 0xa5, 0x7, 0x12, 0x2, 0x2, 
    0xa5, 0xa6, 0x5, 0x2a, 0x16, 0x2, 0xa6, 0xa7, 0x7, 0x13, 0x2, 0x2, 0xa7, 
    0xe8, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa9, 0x7, 0x21, 0x2, 0x2, 0xa9, 0xaa, 
    0x7, 0x10, 0x2, 0x2, 0xaa, 0xab, 0x7, 0x42, 0x2, 0x2, 0xab, 0xac, 0x7, 
    0x6, 0x2, 0x2, 0xac, 0xad, 0x7, 0x23, 0x2, 0x2, 0xad, 0xae, 0x7, 0x12, 
    0x2, 0x2, 0xae, 0xaf, 0x5, 0x2a, 0x16, 0x2, 0xaf, 0xb0, 0x7, 0x13, 0x2, 
    0x2, 0xb0, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xb2, 0x7, 0x21, 0x2, 0x2, 
    0xb2, 0xb3, 0x7, 0x10, 0x2, 0x2, 0xb3, 0xb4, 0x7, 0x42, 0x2, 0x2, 0xb4, 
    0xb5, 0x7, 0x6, 0x2, 0x2, 0xb5, 0xb6, 0x7, 0x24, 0x2, 0x2, 0xb6, 0xb8, 
    0x7, 0x25, 0x2, 0x2, 0xb7, 0xb9, 0x7, 0x42, 0x2, 0x2, 0xb8, 0xb7, 0x3, 
    0x2, 0x2, 0x2, 0xb8, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xe8, 0x3, 0x2, 
    0x2, 0x2, 0xba, 0xbb, 0x7, 0x21, 0x2, 0x2, 0xbb, 0xbc, 0x7, 0x10, 0x2, 
    0x2, 0xbc, 0xbd, 0x7, 0x42, 0x2, 0x2, 0xbd, 0xbe, 0x7, 0x6, 0x2, 0x2, 
    0xbe, 0xbf, 0x7, 0x26, 0x2, 0x2, 0xbf, 0xc0, 0x7, 0x25, 0x2, 0x2, 0xc0, 
    0xe8, 0x7, 0x42, 0x2, 0x2, 0xc1, 0xc2, 0x7, 0x21, 0x2, 0x2, 0xc2, 0xc3, 
    0x7, 0x10, 0x2, 0x2, 0xc3, 0xc4, 0x7, 0x42, 0x2, 0x2, 0xc4, 0xc5, 0x7, 
    0x22, 0x2, 0x2, 0xc5, 0xc6, 0x7, 0x27, 0x2, 0x2, 0xc6, 0xc7, 0x7, 0x42, 
    0x2, 0x2, 0xc7, 0xc8, 0x7, 0x24, 0x2, 0x2, 0xc8, 0xc9, 0x7, 0x25, 0x2, 
    0x2, 0xc9, 0xca, 0x7, 0x12, 0x2, 0x2, 0xca, 0xcb, 0x5, 0x2a, 0x16, 0x2, 
    0xcb, 0xcc, 0x7, 0x13, 0x2, 0x2, 0xcc, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xcd, 
    0xce, 0x7, 0x21, 0x2, 0x2, 0xce, 0xcf, 0x7, 0x10, 0x2, 0x2, 0xcf, 0xd0, 
    0x7, 0x42, 0x2, 0x2, 0xd0, 0xd1, 0x7, 0x22, 0x2, 0x2, 0xd1, 0xd2, 0x7, 
    0x27, 0x2, 0x2, 0xd2, 0xd3, 0x7, 0x42, 0x2, 0x2, 0xd3, 0xd4, 0x7, 0x26, 
    0x2, 0x2, 0xd4, 0xd5, 0x7, 0x25, 0x2, 0x2, 0xd5, 0xd6, 0x7, 0x12, 0x2, 
    0x2, 0xd6, 0xd7, 0x5, 0x2a, 0x16, 0x2, 0xd7, 0xd8, 0x7, 0x13, 0x2, 0x2, 
    0xd8, 0xd9, 0x7, 0x28, 0x2, 0x2, 0xd9, 0xda, 0x7, 0x42, 0x2, 0x2, 0xda, 
    0xdb, 0x7, 0x12, 0x2, 0x2, 0xdb, 0xdc, 0x5, 0x2a, 0x16, 0x2, 0xdc, 0xdd, 
    0x7, 0x13, 0x2, 0x2, 0xdd, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xde, 0xdf, 0x7, 
    0x21, 0x2, 0x2, 0xdf, 0xe0, 0x7, 0x10, 0x2, 0x2, 0xe0, 0xe1, 0x7, 0x42, 
    0x2, 0x2, 0xe1, 0xe2, 0x7, 0x22, 0x2, 0x2, 0xe2, 0xe3, 0x7, 0x29, 0x2, 
    0x2, 0xe3, 0xe4, 0x7, 0x12, 0x2, 0x2, 0xe4, 0xe5, 0x5, 0x2a, 0x16, 0x2, 
    0xe5, 0xe6, 0x7, 0x13, 0x2, 0x2, 0xe6, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xe7, 
    0x9f, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xb1, 
    0x3, 0x2, 0x2, 0x2, 0xe7, 0xba, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xc1, 0x3, 
    0x2, 0x2, 0x2, 0xe7, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xde, 0x3, 0x2, 
    0x2, 0x2, 0xe8, 0xf, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xee, 0x5, 0x12, 0xa, 
    0x2, 0xea, 0xeb, 0x7, 0x2a, 0x2, 0x2, 0xeb, 0xed, 0x5, 0x12, 0xa, 0x2, 
    0xec, 0xea, 0x3, 0x2, 0x2, 0x2, 0xed, 0xf0, 0x3, 0x2, 0x2, 0x2, 0xee, 
    0xec, 0x3, 0x2, 0x2, 0x2, 0xee, 0xef, 0x3, 0x2, 0x2, 0x2, 0xef, 0x11, 
    0x3, 0x2, 0x2, 0x2, 0xf0, 0xee, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xf2, 0x7, 
    0x42, 0x2, 0x2, 0xf2, 0xf5, 0x5, 0x14, 0xb, 0x2, 0xf3, 0xf4, 0x7, 0x2b, 
    0x2, 0x2, 0xf4, 0xf6, 0x7, 0x41, 0x2, 0x2, 0xf5, 0xf3, 0x3, 0x2, 0x2, 
    0x2, 0xf5, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf9, 0x3, 0x2, 0x2, 0x2, 
    0xf7, 0xf8, 0x7, 0x2c, 0x2, 0x2, 0xf8, 0xfa, 0x5, 0x1a, 0xe, 0x2, 0xf9, 
    0xf7, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xfa, 0x113, 
    0x3, 0x2, 0x2, 0x2, 0xfb, 0xfc, 0x7, 0x24, 0x2, 0x2, 0xfc, 0xfe, 0x7, 
    0x25, 0x2, 0x2, 0xfd, 0xff, 0x7, 0x42, 0x2, 0x2, 0xfe, 0xfd, 0x3, 0x2, 
    0x2, 0x2, 0xfe, 0xff, 0x3, 0x2, 0x2, 0x2, 0xff, 0x100, 0x3, 0x2, 0x2, 
    0x2, 0x100, 0x101, 0x7, 0x12, 0x2, 0x2, 0x101, 0x102, 0x5, 0x2a, 0x16, 
    0x2, 0x102, 0x103, 0x7, 0x13, 0x2, 0x2, 0x103, 0x113, 0x3, 0x2, 0x2, 
    0x2, 0x104, 0x105, 0x7, 0x26, 0x2, 0x2, 0x105, 0x107, 0x7, 0x25, 0x2, 
    0x2, 0x106, 0x108, 0x7, 0x42, 0x2, 0x2, 0x107, 0x106, 0x3, 0x2, 0x2, 
    0x2, 0x107, 0x108, 0x3, 0x2, 0x2, 0x2, 0x108, 0x109, 0x3, 0x2, 0x2, 
    0x2, 0x109, 0x10a, 0x7, 0x12, 0x2, 0x2, 0x10a, 0x10b, 0x5, 0x2a, 0x16, 
    0x2, 0x10b, 0x10c, 0x7, 0x13, 0x2, 0x2, 0x10c, 0x10d, 0x7, 0x28, 0x2, 
    0x2, 0x10d, 0x10e, 0x7, 0x42, 0x2, 0x2, 0x10e, 0x10f, 0x7, 0x12, 0x2, 
    0x2, 0x10f, 0x110, 0x5, 0x2a, 0x16, 0x2, 0x110, 0x111, 0x7, 0x13, 0x2, 
    0x2, 0x111, 0x113, 0x3, 0x2, 0x2, 0x2, 0x112, 0xf1, 0x3, 0x2, 0x2, 0x2, 
    0x112, 0xfb, 0x3, 0x2, 0x2, 0x2, 0x112, 0x104, 0x3, 0x2, 0x2, 0x2, 0x113, 
    0x13, 0x3, 0x2, 0x2, 0x2, 0x114, 0x11b, 0x7, 0x2d, 0x2, 0x2, 0x115, 
    0x116, 0x7, 0x2e, 0x2, 0x2, 0x116, 0x117, 0x7, 0x12, 0x2, 0x2, 0x117, 
    0x118, 0x7, 0x43, 0x2, 0x2, 0x118, 0x11b, 0x7, 0x13, 0x2, 0x2, 0x119, 
    0x11b, 0x7, 0x2f, 0x2, 0x2, 0x11a, 0x114, 0x3, 0x2, 0x2, 0x2, 0x11a, 
    0x115, 0x3, 0x2, 0x2, 0x2, 0x11a, 0x119, 0x3, 0x2, 0x2, 0x2, 0x11b, 
    0x15, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x121, 0x5, 0x18, 0xd, 0x2, 0x11d, 
    0x11e, 0x7, 0x2a, 0x2, 0x2, 0x11e, 0x120, 0x5, 0x18, 0xd, 0x2, 0x11f, 
    0x11d, 0x3, 0x2, 0x2, 0x2, 0x120, 0x123, 0x3, 0x2, 0x2, 0x2, 0x121, 
    0x11f, 0x3, 0x2, 0x2, 0x2, 0x121, 0x122, 0x3, 0x2, 0x2, 0x2, 0x122, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x123, 0x121, 0x3, 0x2, 0x2, 0x2, 0x124, 0x125, 
    0x7, 0x12, 0x2, 0x2, 0x125, 0x12a, 0x5, 0x1a, 0xe, 0x2, 0x126, 0x127, 
    0x7, 0x2a, 0x2, 0x2, 0x127, 0x129, 0x5, 0x1a, 0xe, 0x2, 0x128, 0x126, 
    0x3, 0x2, 0x2, 0x2, 0x129, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x128, 
    0x3, 0x2, 0x2, 0x2, 0x12a, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x12b, 0x12d, 
    0x3, 0x2, 0x2, 0x2, 0x12c, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x12e, 
    0x7, 0x13, 0x2, 0x2, 0x12e, 0x19, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x130, 
    0x9, 0x2, 0x2, 0x2, 0x130, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x131, 0x136, 0x5, 
    0x1e, 0x10, 0x2, 0x132, 0x133, 0x7, 0x30, 0x2, 0x2, 0x133, 0x135, 0x5, 
    0x1e, 0x10, 0x2, 0x134, 0x132, 0x3, 0x2, 0x2, 0x2, 0x135, 0x138, 0x3, 
    0x2, 0x2, 0x2, 0x136, 0x134, 0x3, 0x2, 0x2, 0x2, 0x136, 0x137, 0x3, 
    0x2, 0x2, 0x2, 0x137, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x138, 0x136, 0x3, 0x2, 
    0x2, 0x2, 0x139, 0x13a, 0x5, 0x20, 0x11, 0x2, 0x13a, 0x13b, 0x5, 0x2c, 
    0x17, 0x2, 0x13b, 0x13c, 0x5, 0x22, 0x12, 0x2, 0x13c, 0x159, 0x3, 0x2, 
    0x2, 0x2, 0x13d, 0x13e, 0x5, 0x20, 0x11, 0x2, 0x13e, 0x13f, 0x5, 0x2c, 
    0x17, 0x2, 0x13f, 0x140, 0x7, 0x12, 0x2, 0x2, 0x140, 0x141, 0x5, 0xc, 
    0x7, 0x2, 0x141, 0x142, 0x7, 0x13, 0x2, 0x2, 0x142, 0x159, 0x3, 0x2, 
    0x2, 0x2, 0x143, 0x144, 0x5, 0x20, 0x11, 0x2, 0x144, 0x146, 0x7, 0x31, 
    0x2, 0x2, 0x145, 0x147, 0x7, 0x2b, 0x2, 0x2, 0x146, 0x145, 0x3, 0x2, 
    0x2, 0x2, 0x146, 0x147, 0x3, 0x2, 0x2, 0x2, 0x147, 0x148, 0x3, 0x2, 
    0x2, 0x2, 0x148, 0x149, 0x7, 0x41, 0x2, 0x2, 0x149, 0x159, 0x3, 0x2, 
    0x2, 0x2, 0x14a, 0x14b, 0x5, 0x20, 0x11, 0x2, 0x14b, 0x14c, 0x7, 0x32, 
    0x2, 0x2, 0x14c, 0x14d, 0x5, 0x18, 0xd, 0x2, 0x14d, 0x159, 0x3, 0x2, 
    0x2, 0x2, 0x14e, 0x14f, 0x5, 0x20, 0x11, 0x2, 0x14f, 0x150, 0x7, 0x32, 
    0x2, 0x2, 0x150, 0x151, 0x7, 0x12, 0x2, 0x2, 0x151, 0x152, 0x5, 0xc, 
    0x7, 0x2, 0x152, 0x153, 0x7, 0x13, 0x2, 0x2, 0x153, 0x159, 0x3, 0x2, 
    0x2, 0x2, 0x154, 0x155, 0x5, 0x20, 0x11, 0x2, 0x155, 0x156, 0x7, 0x33, 
    0x2, 0x2, 0x156, 0x157, 0x7, 0x44, 0x2, 0x2, 0x157, 0x159, 0x3, 0x2, 
    0x2, 0x2, 0x158, 0x139, 0x3, 0x2, 0x2, 0x2, 0x158, 0x13d, 0x3, 0x2, 
    0x2, 0x2, 0x158, 0x143, 0x3, 0x2, 0x2, 0x2, 0x158, 0x14a, 0x3, 0x2, 
    0x2, 0x2, 0x158, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x158, 0x154, 0x3, 0x2, 
    0x2, 0x2, 0x159, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x15a, 0x15b, 0x7, 0x42, 
    0x2, 0x2, 0x15b, 0x15c, 0x7, 0x34, 0x2, 0x2, 0x15c, 0x15d, 0x7, 0x42, 
    0x2, 0x2, 0x15d, 0x21, 0x3, 0x2, 0x2, 0x2, 0x15e, 0x161, 0x5, 0x1a, 
    0xe, 0x2, 0x15f, 0x161, 0x5, 0x20, 0x11, 0x2, 0x160, 0x15e, 0x3, 0x2, 
    0x2, 0x2, 0x160, 0x15f, 0x3, 0x2, 0x2, 0x2, 0x161, 0x23, 0x3, 0x2, 0x2, 
    0x2, 0x162, 0x163, 0x7, 0x42, 0x2, 0x2, 0x163, 0x164, 0x7, 0x36, 0x2, 
    0x2, 0x164, 0x16b, 0x5, 0x1a, 0xe, 0x2, 0x165, 0x166, 0x7, 0x2a, 0x2, 
    0x2, 0x166, 0x167, 0x7, 0x42, 0x2, 0x2, 0x167, 0x168, 0x7, 0x36, 0x2, 
    0x2, 0x168, 0x16a, 0x5, 0x1a, 0xe, 0x2, 0x169, 0x165, 0x3, 0x2, 0x2, 
    0x2, 0x16a, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x16b, 0x169, 0x3, 0x2, 0x2, 
    0x2, 0x16b, 0x16c, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x25, 0x3, 0x2, 0x2, 0x2, 
    0x16d, 0x16b, 0x3, 0x2, 0x2, 0x2, 0x16e, 0x178, 0x7, 0x35, 0x2, 0x2, 
    0x16f, 0x174, 0x5, 0x28, 0x15, 0x2, 0x170, 0x171, 0x7, 0x2a, 0x2, 0x2, 
    0x171, 0x173, 0x5, 0x28, 0x15, 0x2, 0x172, 0x170, 0x3, 0x2, 0x2, 0x2, 
    0x173, 0x176, 0x3, 0x2, 0x2, 0x2, 0x174, 0x172, 0x3, 0x2, 0x2, 0x2, 
    0x174, 0x175, 0x3, 0x2, 0x2, 0x2, 0x175, 0x178, 0x3, 0x2, 0x2, 0x2, 
    0x176, 0x174, 0x3, 0x2, 0x2, 0x2, 0x177, 0x16e, 0x3, 0x2, 0x2, 0x2, 
    0x177, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x178, 0x27, 0x3, 0x2, 0x2, 0x2, 0x179, 
    0x184, 0x5, 0x20, 0x11, 0x2, 0x17a, 0x17b, 0x5, 0x2e, 0x18, 0x2, 0x17b, 
    0x17c, 0x7, 0x12, 0x2, 0x2, 0x17c, 0x17d, 0x5, 0x20, 0x11, 0x2, 0x17d, 
    0x17e, 0x7, 0x13, 0x2, 0x2, 0x17e, 0x184, 0x3, 0x2, 0x2, 0x2, 0x17f, 
    0x180, 0x7, 0x3c, 0x2, 0x2, 0x180, 0x181, 0x7, 0x12, 0x2, 0x2, 0x181, 
    0x182, 0x7, 0x35, 0x2, 0x2, 0x182, 0x184, 0x7, 0x13, 0x2, 0x2, 0x183, 
    0x179, 0x3, 0x2, 0x2, 0x2, 0x183, 0x17a, 0x3, 0x2, 0x2, 0x2, 0x183, 
    0x17f, 0x3, 0x2, 0x2, 0x2, 0x184, 0x29, 0x3, 0x2, 0x2, 0x2, 0x185, 0x18a, 
    0x7, 0x42, 0x2, 0x2, 0x186, 0x187, 0x7, 0x2a, 0x2, 0x2, 0x187, 0x189, 
    0x7, 0x42, 0x2, 0x2, 0x188, 0x186, 0x3, 0x2, 0x2, 0x2, 0x189, 0x18c, 
    0x3, 0x2, 0x2, 0x2, 0x18a, 0x188, 0x3, 0x2, 0x2, 0x2, 0x18a, 0x18b, 
    0x3, 0x2, 0x2, 0x2, 0x18b, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x18c, 0x18a, 0x3, 
    0x2, 0x2, 0x2, 0x18d, 0x18e, 0x9, 0x3, 0x2, 0x2, 0x18e, 0x2d, 0x3, 0x2, 
    0x2, 0x2, 0x18f, 0x190, 0x9, 0x4, 0x2, 0x2, 0x190, 0x2f, 0x3, 0x2, 0x2, 
    0x2, 0x1f, 0x33, 0x48, 0x58, 0x68, 0x88, 0x90, 0x95, 0x9b, 0x9d, 0xb8, 
    0xe7, 0xee, 0xf5, 0xf9, 0xfe, 0x107, 0x112, 0x11a, 0x121, 0x12a, 0x136, 
    0x146, 0x158, 0x160, 0x16b, 0x174, 0x177, 0x183, 0x18a, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

MYSQLParser::Initializer MYSQLParser::_init;
