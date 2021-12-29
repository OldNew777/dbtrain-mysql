#include "database.h"

#include "macros.h"
#include "os/os.h"
#include "page/record_page.h"
#include "record/fixed_record.h"

namespace dbtrain_mysql {

Database::Database(PageID nDatabaseID) {
  pDatabase = new DatabasePage(nDatabaseID);

  _nHeadID = pDatabase->GetHeadID();
  _nTailID = pDatabase->GetTailID();
  _nNotFull = _nHeadID;
  FindNextNotFull();
}

Database::~Database() { delete pDatabase; }

PageID Database::GetTable(const String& sTableName) {}

PageID Database::InsertTable(const String& sTableName) {}

void Database::DeleteTable(const String& sTableName) {}

void Database::RenameTable(const String& sOldTableName,
                           const String& sNewTableName) {}

void Database::Clear() { _iTableMap.clear(); }

std::vector<String> Database::GetColumnNames() {}

Record* Database::EmptyRecord() const {
  return new FixedRecord(pDatabase->GetFieldSize(), pDatabase->GetTypeVec(),
                         pDatabase->GetSizeVec());
}

void Database::FindNextNotFull() {}

bool Database::NextNotFullUntil(PageID target) {}

}  // namespace dbtrain_mysql