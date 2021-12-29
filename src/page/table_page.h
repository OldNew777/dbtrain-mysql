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
  virtual ~TablePage() = default;

  FieldID GetFieldID(const String& sColName) const;

  FieldID GetPos(const String& sCol);
  FieldType GetType(const String& sCol);
  Size GetSize(const String& sCol);

  virtual ManagerPageType GetManagerPageType() const;

 protected:
  friend class Table;
};

}  // namespace dbtrain_mysql

#endif