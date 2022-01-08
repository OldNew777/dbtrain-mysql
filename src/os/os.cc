#include "os/os.h"

#include <cstring>
#include <fstream>

#include "exception/exceptions.h"
#include "macros.h"
#include "os/raw_page.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

uint8_t zeros[PAGE_SIZE] = {0};

OS* OS::os = nullptr;

OS* OS::GetOS() {
  if (os == nullptr) os = new OS();
  return os;
}

void OS::WriteBack() {
  // printf("write_back\n");
  if (os != nullptr) {
    delete os;
    os = nullptr;
  }
}

void OS::CheckFileExist() {
  if (GetFiles(DB_DATA_PATH).size() <= 1) {
    printf("OS::CheckFileExist: DB_Page.dat not exists\n");
    std::ofstream fout(String(DB_PAGE_NAME) + "0", std::ios::binary);
    for (int i = 0; i < MEM_PAGES; ++i) fout.write((char*)zeros, PAGE_SIZE);
  }
}

OS::OS() {
  _pUsed = new Bitmap(DB_PAGES_MAX);
  _nClock = 0;
  LoadBitmap();
  initDBPage();
  // printf("pUsed num:%d\n", _pUsed->GetUsed());
  printf("OS()\n");
}

OS::~OS() {
  // printf("pUsed num:%d\n", _pUsed->GetUsed());
  printf("~OS()\n");
  StoreBitmap();
  delete _pUsed;
}

PageID OS::NewPage() {
  Size tmp = _nClock;
  do {
    if (!_pUsed->Get(_nClock)) {
      while (_nClock > _maxSize && _maxSize < DB_PAGES_MAX) {
        std::fstream fout(
            String(DB_PAGE_NAME) + std::to_string(_maxSize / MEM_PAGES),
            std::ios::binary | std::ios::in | std::ios::out);
        fout.seekp(0, std::ios::end);
        for (int i = 0; i < MEM_PAGES; ++i) fout.write((char*)zeros, PAGE_SIZE);
        fout.close();
        _maxSize += MEM_PAGES;
      }
      _pUsed->Set(_nClock);
      return _nClock;
    } else {
      ++_nClock;
      if (_nClock == DB_PAGES_MAX) _nClock = 0;
    }
  } while (_nClock != tmp);
  auto e = NewPageException();
  std::cout << e.what() << "\n";
  throw e;
}

void OS::DeletePage(PageID pid) {
  if (!_pUsed->Get(pid)) {
    auto e = PageNotInitException(pid);
    std::cout << e.what() << "\n";
    throw e;
  }
  _cache.DeletePage(pid);
  _pUsed->Unset(pid);
}

void OS::ReadPage(PageID pid, uint8_t* dst, PageOffset nSize,
                  PageOffset nOffset) {
  if (!_pUsed->Get(pid)) {
    auto e = PageNotInitException(pid);
    std::cout << e.what() << "\n";
    throw e;
  }
  _cache.ReadPage(pid, dst, nSize, nOffset);
}

void OS::WritePage(PageID pid, const uint8_t* src, PageOffset nSize,
                   PageOffset nOffset) {
  if (!_pUsed->Get(pid)) {
    auto e = PageNotInitException(pid);
    std::cout << e.what() << "\n";
    throw e;
  }
  // printf("write page\n");
  _cache.WritePage(pid, src, nSize, nOffset);
}

void OS::LoadBitmap() {
  std::ifstream fin(DB_BITMAP_NAME, std::ios::binary);
  if (!fin) return;
  uint8_t pTemp[DB_PAGES_MAX / 8];
  fin.read((char*)pTemp, DB_PAGES_MAX / 8);
  fin.close();
  _pUsed->Load(pTemp);
}

void OS::StoreBitmap() {
  std::ofstream fout(DB_BITMAP_NAME, std::ios::binary);
  if (!fout) return;
  uint8_t pTemp[DB_PAGES_MAX / 8];
  _pUsed->Store(pTemp);
  fout.write((char*)pTemp, DB_PAGES_MAX / 8);
  fout.close();
}

Size OS::GetUsedSize() const {
  if (!_pUsed) {
    auto e = OsException();
    std::cout << e.what() << "\n";
    throw e;
  }
  return _pUsed->GetSize();
}

void OS::initDBPage() {
  std::vector<String> files = GetFiles(DB_DATA_PATH);
  if (files.size() > 1) {
    // printf("OS::initDBPage: DB_Page.dat exists\n");
    _maxSize = MEM_PAGES * (files.size() - 1);
  } else {
    // printf("OS::initDBPage: DB_Page.dat not exists\n");
    std::ofstream fout(String(DB_PAGE_NAME) + "0", std::ios::binary);
    for (int i = 0; i < MEM_PAGES; ++i) fout.write((char*)zeros, PAGE_SIZE);
    fout.close();
    _maxSize = MEM_PAGES;
  }
  return;
}

}  // namespace dbtrain_mysql
