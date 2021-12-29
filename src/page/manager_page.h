#ifndef DBTRAIN_MYSQL_MANAGER_PAGE_H
#define DBTRAIN_MYSQL_MANAGER_PAGE_H

#include "defines.h"
#include "field/field.h"
#include "page/page.h"

namespace dbtrain_mysql {

enum class ManagerPageType {
  DATABASE_PAGE_TYPE = 0,
  TABLE_PAGE_TYPE = 1,
};

class ManagerPage : public Page {
 public:
  ManagerPage() = default;
  ManagerPage(PageID nPageID);
  virtual ~ManagerPage();

  virtual PageID GetHeadID() const;
  virtual PageID GetTailID() const;
  virtual void SetHeadID(PageID nHeadID);
  virtual void SetTailID(PageID nTailID);

  virtual Size GetFieldSize() const;
  virtual std::vector<FieldType> GetTypeVec() const;
  virtual std::vector<Size> GetSizeVec() const;
  virtual Size GetTotalSize() const;

  virtual ManagerPageType GetManagerPageType() const = 0;

 protected:
  virtual void Store();
  virtual void Load();

  std::map<String, FieldID> _iColMap;
  std::vector<FieldType> _iTypeVec;
  std::vector<Size> _iSizeVec;
  PageID _nHeadID, _nTailID;
};

}  // namespace dbtrain_mysql

#endif