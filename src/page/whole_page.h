#ifndef DBTRAIN_MYSQL_WHOLE_PAGE_H
#define DBTRAIN_MYSQL_WHOLE_PAGE_H

#include "defines.h"
#include "page/manager_page.h"

namespace dbtrain_mysql {

class Whole;

class WholePage : public ManagerPage {
 public:
  WholePage();
  WholePage(PageID nPageID);
  virtual ~WholePage() = default;

  virtual ManagerPageType GetManagerPageType() const;

 protected:
  friend class Whole;
};

}  // namespace dbtrain_mysql

#endif