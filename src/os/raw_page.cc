#include "os/raw_page.h"

#include <cstring>

#include "exception/exceptions.h"
#include "macros.h"

namespace dbtrain_mysql {

RawPage::RawPage() {
  _pData = new uint8_t[PAGE_SIZE];
  memset(_pData, 0, PAGE_SIZE);
}

RawPage::~RawPage() { delete[] _pData; }

void RawPage::Read(uint8_t* dst, PageOffset nSize, PageOffset nOffset) {
  if ((nSize + nOffset) > PAGE_SIZE)
    throw PageOutOfSizeException(nSize + nOffset);
  memcpy(dst, _pData + nOffset, nSize);
}

void RawPage::Write(const uint8_t* src, PageOffset nSize, PageOffset nOffset) {
  if ((nSize + nOffset) > PAGE_SIZE)
    throw PageOutOfSizeException(nSize + nOffset);
  memcpy(_pData + nOffset, src, nSize);
}

}  // namespace dbtrain_mysql
