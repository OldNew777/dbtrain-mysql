#ifndef DBTRAIN_MYSQL_MANAGER_PAGE_H
#define DBTRAIN_MYSQL_MANAGER_PAGE_H

#include "defines.h"
#include "field/field.h"
#include "page/page.h"
#include "record/fixed_record.h"

namespace dbtrain_mysql {

class EntityManager;

enum class ManagerPageType {
  DATABASE_PAGE_TYPE = 0,
  TABLE_PAGE_TYPE = 1,
  WHOLE_PAGE_TYPE = 2,
};

class ManagerPage : public Page {
 public:
  ManagerPage();
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
  std::vector<bool> _iNullVec;
  PageID _nHeadID, _nTailID;

  friend class EntityManager;
};

}  // namespace dbtrain_mysql

#endif