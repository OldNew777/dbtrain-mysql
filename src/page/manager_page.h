#ifndef DBTRAIN_MYSQL_MANAGER_PAGE_H
#define DBTRAIN_MYSQL_MANAGER_PAGE_H

#include "defines.h"
#include "field/field.h"
#include "page/page.h"
#include "record/fixed_record.h"

namespace dbtrain_mysql {

class Entity;
class Database;

enum class ManagerPageType {
  DATABASE_PAGE_TYPE = 0,
  TABLE_PAGE_TYPE = 1,
};

class ManagerPage : public Page {
 public:
  ManagerPage() = default;
  ManagerPage(PageID nPageID);
  virtual ~ManagerPage();

  PageID GetHeadID() const;
  PageID GetTailID() const;
  void SetHeadID(PageID nHeadID);
  void SetTailID(PageID nTailID);

  Size GetFieldSize() const;
  std::vector<FieldType> GetTypeVec() const;
  std::vector<Size> GetSizeVec() const;
  Size GetTotalSize() const;

  virtual ManagerPageType GetManagerPageType() const = 0;

 protected:
  void Store();
  void Load();
  std::vector<std::pair<PageSlotID, Record*>> GetAllRecords() const;

  std::map<String, FieldID> _iColMap;
  std::vector<FieldType> _iTypeVec;
  std::vector<Size> _iSizeVec;
  PageID _nHeadID, _nTailID;

  friend class Entity;
  friend class Database;
};

}  // namespace dbtrain_mysql

#endif