#include "parse.h"
#include "MyVisitor.h"

using namespace antlr4;

namespace dbtrain_mysql{
    void Parser::init(const std::string & filename){
        this->afs_ = new ANTLRFileStream(filename);
        printf("init done\n");
        
    }

    void Parser::parse(){
        MYSQLLexer* lexer = new MYSQLLexer(this->afs_);
        CommonTokenStream* tokens = new CommonTokenStream(lexer);
        MYSQLParser* parser = new MYSQLParser(tokens);
        MYSQLParser::ProgramContext* tree = parser->program();
        dbtrain_mysql::MyVisitor* visitor = new dbtrain_mysql::MyVisitor();


        printf("start visit\n");
        if(visitor){
            visitor->init();
            visitor->visit(tree);
        }
            

        delete lexer;
        delete tokens;
        delete parser;
        // delete tree;
        delete visitor;
    }
}