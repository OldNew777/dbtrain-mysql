#ifndef DBTRAIN_MYSQL_DATABASE_PAGE_H
#define DBTRAIN_MYSQL_DATABASE_PAGE_H

#include "defines.h"
#include "field/field.h"
#include "page/manager_page.h"

namespace dbtrain_mysql {

class Database;

class DatabasePage : public ManagerPage {
 public:
  DatabasePage();
  DatabasePage(PageID nPageID);
  virtual ~DatabasePage() = default;

  virtual ManagerPageType GetManagerPageType() const;

 protected:
  friend class Database;
};

}  // namespace dbtrain_mysql

#endif