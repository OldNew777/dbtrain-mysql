#ifndef DBTRAIN_MYSQL_TABLE_PAGE_H
#define DBTRAIN_MYSQL_TABLE_PAGE_H

#include "defines.h"
#include "entity/schema.h"
#include "field/field.h"
#include "page/manager_page.h"

namespace dbtrain_mysql {

class Table;

class TablePage : public ManagerPage {
 public:
  TablePage(const Schema& iSchema);
  TablePage(PageID nPageID);
  ~TablePage();

  FieldID GetColPos(const String& sCol);
  FieldType GetType(const String& sCol);
  bool GetIsNull(const String& sCol);
  bool GetIsPrimary(const String& sCol);
  Size GetSize(const String& sCol);

  // PageID GetIndexPageID(const String& sCol);
  // void DeleteIndex(const String& sCol);
  // void AddIndex(const String& sCol, PageID nPageID);

  virtual ManagerPageType GetManagerPageType() const;

 protected:
  friend class Table;
  std::vector<uint8_t> _iStatusVec;
  
  // std::vector<PageID> _iIndexPageIDVec;
};

}  // namespace dbtrain_mysql

#endif