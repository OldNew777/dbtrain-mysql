#ifndef DBTRAIN_MYSQL_DATABASE_MANAGER_H
#define DBTRAIN_MYSQL_DATABASE_MANAGER_H

#include "defines.h"
#include "entity/database.h"
#include "macros.h"

namespace dbtrain_mysql {

class DatabaseManager {
 public:
  DatabaseManager();
  ~DatabaseManager();

  Database* GetDatabase(const String& sDatabaseName);
  Database* AddDatabase(const String& sDatabaseName);
  void DropDatabase(const String& sDatabaseName);

  std::vector<String> GetDatabaseNames() const;
  std::vector<String> GetColumnNames(const String& sDatabaseName);

 private:
  std::map<String, Database*> _iDatabaseMap;
  std::map<String, PageID> _iDatabaseIDMap;

  void Store();
  void Load();
};

}  // namespace dbtrain_mysql

#endif