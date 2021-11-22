#ifndef DBTRAIN_MYSQL_OS_H
#define DBTRAIN_MYSQL_OS_H

#include "defines.h"
#include "os/raw_page.h"
#include "utils/bitmap.h"

namespace dbtrain_mysql {

class Page;
class Bitmap;

class OS {
 public:
  static OS* GetOS();
  static void WriteBack();

  PageID NewPage();
  void DeletePage(PageID pid);
  void ReadPage(PageID pid, uint8_t* dst, PageOffset nSize,
                PageOffset nOffset = 0);
  void WritePage(PageID pid, const uint8_t* src, PageOffset nSize,
                 PageOffset nOffset = 0);
  Size GetUsedSize() const;

 private:
  OS();
  ~OS();

  void LoadBitmap();
  void LoadPages();

  void StoreBitmap();
  void StorePages();

  RawPage** _pMemory;
  Bitmap* _pUsed;
  Size _nClock;

  static OS* os;
};

}  // namespace dbtrain_mysql

#endif  // DBTRAIN_MYSQL_OS_H
