#ifndef DBTRAIN_MYSQL_INDEX_MANAGER_H
#define DBTRAIN_MYSQL_INDEX_MANAGER_H

#include "defines.h"
#include "index/index.h"

namespace dbtrain_mysql {

class IndexManager {
 public:
  IndexManager();
  ~IndexManager();

  Index *GetIndex(const String &sTableName, const String &sColName);
  Index *AddIndex(const String &sTableName, const String &sColName,
                  FieldType iType);
  void DropIndex(const String &sTableName, const String &sColName);
  bool IsIndex(const String &sTableName, const String &sColName);

  std::vector<std::pair<String, String>> GetIndexInfos() const;
  std::vector<String> GetTableIndexes(const String &sTableName) const;
  bool HasIndex(const String &sTableName) const;

 private:
  std::map<String, Index *> _iIndexMap;
  std::map<String, PageID> _iIndexIDMap;
  std::map<String, std::vector<String>> _iTableIndexes;

  void Store();
  void Load();
  void Init();
};

}  // namespace dbtrain_mysql

#endif