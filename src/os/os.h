#ifndef DBTRAIN_MYSQL_OS_H
#define DBTRAIN_MYSQL_OS_H

#include "defines.h"
#include "cache.h"
#include "os/raw_page.h"
#include "utils/bitmap.h"
#include <filesystem>

namespace dbtrain_mysql {

class Page;
class Bitmap;

class OS {
 public:
  static OS* GetOS();
  static void WriteBack();
  static void CheckFileExist();

  PageID NewPage();
  void DeletePage(PageID pid);
  /**
   * @brief read a page 
   *
   * @param pid page id
   * @param dst destination buffer 
   * @param nSize the length of read
   * @param nOffset the start palace of read
   */
  void ReadPage(PageID pid, uint8_t* dst, PageOffset nSize,
                PageOffset nOffset = 0);
  /**
   * @brief write a page 
   *
   * @param pid page id
   * @param src source buffer 
   * @param nSize the length of read
   * @param nOffset the start place of read
   */
  void WritePage(PageID pid, const uint8_t* src, PageOffset nSize,
                 PageOffset nOffset = 0);
  Size GetUsedSize() const;

 private:
  OS();
  ~OS();

  void LoadBitmap();
  void StoreBitmap();
  void initDBPage();

  CacheGroup* _getCacheGroup(PageID pid){
    return _cache[pid % CACHE_ASSOCIATIVE];
  }

  Bitmap* _pUsed;
  CacheGroup** _cache;
  Size _nClock;
  Size _maxSize;

  static OS* os;
};

}  // namespace dbtrain_mysql

#endif  // DBTRAIN_MYSQL_OS_H
