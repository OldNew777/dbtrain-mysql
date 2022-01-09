#ifndef DBTRAIN_MYSQL_KEY_MANAGER_H
#define DBTRAIN_MYSQL_KEY_MANAGER_H

#include <unordered_map>
#include <vector>

#include "defines.h"
#include "index/index.h"

namespace dbtrain_mysql {

enum class KeyType {
  PRIMARY_KEY_TYPE = 0,
  FOREIGN_KEY_TYPE = 1,
};

// PRIMARY KEY
// | Constraint Name | Table Name | Column Name |

// FOREIGN KEY
// | Constraint Name | Local Table Name | Local Column Name
// | Foreign Table Name | Foreign Column Name
struct Key {
  KeyType iType;
  String sLocalTableName, sForeignTableName;
  std::vector<String> sLocalColName, sForeignColName;
};

class KeyManager {
 public:
  KeyManager();
  KeyManager(PageID nPageID);
  ~KeyManager();

  PageID GetPageID() const;

  void Clear();

 protected:
  PageID _nPageID;
  bool _bCleared = false;
  Size _iDefaultKeyIndex;
  std::unordered_map<String, Key> _iKeyMap;

  void Store();
  void Load();
};

}  // namespace dbtrain_mysql

#endif