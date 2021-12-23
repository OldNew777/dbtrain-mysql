#include "backend/backend.h"

#include <fstream>

#include "antlr4-runtime.h"
#include "exception/exceptions.h"
#include "macros.h"
#include "os/os.h"
#include "page/record_page.h"
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

  RecordPage* pNotUsed1 = new RecordPage(256, true);
  RecordPage* pNotUsed2 = new RecordPage(256, true);
  RecordPage* pTableManagerPage = new RecordPage(TABLE_NAME_SIZE + 4 + 1, true);
  RecordPage* pIndexManagerPage = new RecordPage(INDEX_NAME_SIZE + 4 + 1, true);
  RecordPage* pRecoveryManagerPage = new RecordPage(4 + 4 + 1, true);

  printf("Build Finish.\n");

  delete pNotUsed1;
  delete pNotUsed2;
  delete pTableManagerPage;
  delete pIndexManagerPage;
  delete pRecoveryManagerPage;

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
