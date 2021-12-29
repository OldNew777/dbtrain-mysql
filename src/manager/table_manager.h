#ifndef DBTRAIN_MYSQL_TABLE_MANAGER_H
#define DBTRAIN_MYSQL_TABLE_MANAGER_H

#include "defines.h"
#include "entity/schema.h"
#include "entity/table.h"
#include "macros.h"

namespace dbtrain_mysql {

class TableManager {
 public:
  TableManager();
  ~TableManager();

  Table* GetTable(const String& sTableName);
  Table* AddTable(const String& sTableName, const Schema& iSchema);
  void DropTable(const String& sTableName);

  std::vector<String> GetTableNames() const;
  std::vector<String> GetColumnNames(const String& sTableName);

 private:
  std::map<String, Table*> _iTableMap;
  std::map<String, PageID> _iTableIDMap;

  void Store() const;
  void Load();
};

}  // namespace dbtrain_mysql

#endif