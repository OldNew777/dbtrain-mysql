#ifndef DBTRAIN_MYSQL_CACHE_H
#define DBTRAIN_MYSQL_CACHE_H

#include <fstream>
#include <unordered_map>

#include "defines.h"
#include "exception/exceptions.h"
#include "macros.h"
#include "os/raw_page.h"
#include "utils/bitmap.h"

namespace dbtrain_mysql {
class CacheLine {
 private:
  bool _dirty = false;
  RawPage* _rawPage = nullptr;
  PageID _pid;
  void _writeBack();

 public:
  bool getDirty() { return _dirty; }
  PageID getPageID() { return _pid; }
  void Read(uint8_t* dst, PageOffset nSize, PageOffset nOffset = 0);
  void Write(const uint8_t* src, PageOffset nSize, PageOffset nOffset = 0);

  CacheLine(PageID pid);
  ~CacheLine();
};

class CacheGroup {
 private:
  std::unordered_map<PageID, int> _cacheIndex;
  CacheLine** _cacheGroup;
  CacheLine* _getPage(PageID pid);
  int _nClock;

 public:
  CacheGroup();
  ~CacheGroup();
  void DeletePage(PageID pid);
  void ReadPage(PageID pid, uint8_t* dst, PageOffset nSize,
                PageOffset nOffset = 0);
  void WritePage(PageID pid, const uint8_t* src, PageOffset nSize,
                 PageOffset nOffset = 0);
};
}  // namespace dbtrain_mysql

#endif  // DBTRAIN_MYSQL_CACHE_H