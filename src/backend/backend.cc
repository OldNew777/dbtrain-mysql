#include "backend/backend.h"

#include <fstream>

#include "antlr4-runtime.h"
#include "exception/exceptions.h"
#include "macros.h"
#include "os/os.h"
#include "page/record_page.h"
#include "page/whole_page.h"
#include "parser/ErrorListener.h"
#include "parser/MYSQLLexer.h"
#include "parser/MYSQLParser.h"
#include "parser/SystemVisitor.h"

namespace dbtrain_mysql {

using namespace antlr4;

bool Exists() {
  std::ifstream fin(DB_BITMAP_NAME);
  if (fin)
    return true;
  else
    return false;
}

void Init() {
  if (Exists()) return;
  printf("Database Init.\n");

  WholePage* pDataManagerPage = new WholePage();

  printf("Build Finish.\n");

  delete pDataManagerPage;

  OS::WriteBack();
}

void Clear() {
  if (!Exists()) return;
  std::remove(DB_BITMAP_NAME);
  std::remove(DB_PAGE_NAME);
}

void Close() { OS::WriteBack(); }

std::vector<Result*> Execute(Instance* pDB, const String& sSQL) {
  ANTLRInputStream sInputStream(sSQL);
  MYSQLLexer iLexer(&sInputStream);
  CommonTokenStream sTokenStream(&iLexer);
  MYSQLParser iParser(&sTokenStream);
  iParser.removeErrorListeners();
  SyntaxErrorListener* pListener = new SyntaxErrorListener();
  iParser.addErrorListener(pListener);
  auto iTree = iParser.program();
  delete pListener;
  SystemVisitor iVisitor{pDB};
  return iVisitor.visit(iTree);
}

}  // namespace dbtrain_mysql
