#include "parse.h"
#include "MYSQLBaseVisitor.h"

using namespace antlr4;

namespace dbtrain_mysql{
    void Parser::init(const std::string & filename){
        this->afs_ = new ANTLRFileStream(filename);
    }

    void Parser::parse(){
        MYSQLLexer* lexer = new MYSQLLexer(this->afs_);
        CommonTokenStream* tokens = new CommonTokenStream(lexer);
        MYSQLParser* parser = new MYSQLParser(tokens);
        MYSQLParser::ProgramContext* tree = parser->program();

        MYSQLBaseVisitor* visitor = new MYSQLBaseVisitor();

        visitor->visit(tree);

        delete lexer;
        delete tokens;
        delete parser;
        delete tree;
        delete visitor;
    }
}