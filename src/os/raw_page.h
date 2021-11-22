#ifndef DBTRAIN_MYSQL_MINIOS_PAGE_H
#define DBTRAIN_MYSQL_MINIOS_PAGE_H

#include "defines.h"

namespace dbtrain_mysql {

class RawPage {
 public:
  RawPage();
  ~RawPage();

  void Read(uint8_t* dst, PageOffset nSize, PageOffset nOffset = 0);
  void Write(const uint8_t* src, PageOffset nSize, PageOffset nOffset = 0);

 private:
  uint8_t* _pData;
};

}  // namespace dbtrain_mysql

#endif  // DBTRAIN_MYSQL_MINIOS_PAGE_H
