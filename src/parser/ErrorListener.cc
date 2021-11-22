#include "ErrorListener.h"

#include "exception/exceptions.h"

namespace antlr4 {

void SyntaxErrorListener::syntaxError(Recognizer *recognizer,
                                      Token *offendingSymbol, size_t line,
                                      size_t charPositionInLine,
                                      const std::string &msg,
                                      std::exception_ptr e) {
  throw dbtrain_mysql::ParserException(msg);
}

}  // namespace antlr4
