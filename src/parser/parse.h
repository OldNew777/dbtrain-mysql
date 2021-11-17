#ifndef DBTRAIN_MYSQL_PARSE_H_
#define DBTRAIN_MYSQL_PARSE_H_

#include "MYSQLLexer.h"
#include "ANTLRInputStream.h"
#include "ANTLRFileStream.h"

#include <string.h>
using namespace antlr4;
namespace dbtrain_mysql{
    
    class Parser{
    protected:
        ANTLRFileStream* afs_;
    public:
        void init(const std::string & filename);
        void parse();
    };
}

#endif 
