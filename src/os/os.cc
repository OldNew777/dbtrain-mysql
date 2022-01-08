#include "os/os.h"

#include <cstring>
#include <fstream>

#include "exception/exceptions.h"
#include "macros.h"
#include "os/raw_page.h"

namespace dbtrain_mysql {

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
  std::ifstream fin(DB_PAGE_NAME, std::ios::binary);
  if (!fin) {
    printf("OS::CheckFileExist: DB_Page.dat not exists\n");
    std::ofstream fout(DB_PAGE_NAME, std::ios::binary);
    uint8_t* ptemp = new uint8_t[PAGE_SIZE * MEM_PAGES];
    memset(ptemp, 0, PAGE_SIZE * MEM_PAGES);
    fout.write((char*)ptemp, PAGE_SIZE * MEM_PAGES);
    fout.close();
    delete ptemp;
  } else {
    fin.close();
  }
}

OS::OS() {
  memset(zeros, 0, PAGE_SIZE);
  _pUsed = new Bitmap(MAX_MEM_PAGES);
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
      while (_nClock > _maxSize && _maxSize < MAX_MEM_PAGES) {
        std::fstream fout(DB_PAGE_NAME,
                          std::ios::binary | std::ios::in | std::ios::out);
        fout.seekp(0, std::ios::end);
        for (int i = 0; i < MEM_PAGES; ++i) fout.write((char*)zeros, PAGE_SIZE);
        fout.close();
        _maxSize += MEM_PAGES;
      }
      _pUsed->Set(_nClock);
      // printf("\nnewpage: %d\n", _nClock);
      return _nClock;
    } else {
      _nClock += 1;
      _nClock %= MAX_MEM_PAGES;
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
  uint8_t pTemp[MAX_MEM_PAGES / 8];
  fin.read((char*)pTemp, MAX_MEM_PAGES / 8);
  fin.close();
  _pUsed->Load(pTemp);
}

void OS::StoreBitmap() {
  std::ofstream fout(DB_BITMAP_NAME, std::ios::binary);
  if (!fout) return;
  uint8_t pTemp[MAX_MEM_PAGES / 8];
  _pUsed->Store(pTemp);
  fout.write((char*)pTemp, MAX_MEM_PAGES / 8);
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
  std::ifstream fin(DB_PAGE_NAME, std::ios::binary);
  if (fin) {
    // printf("OS::initDBPage: DB_Page.dat exists\n");
    fin.seekg(0, fin.end);
    Size size = fin.tellg();
    if (size % PAGE_SIZE != 0) {
      auto e = CacheInvalideException("size should be divisible by pagesize");
      std::cout << e.what() << "\n";
      throw e;
    }
    _maxSize = size / PAGE_SIZE;
    fin.close();
  } else {
    // printf("OS::initDBPage: DB_Page.dat not exists\n");
    std::ofstream fout(DB_PAGE_NAME, std::ios::binary);
    for (int i = 0; i < MEM_PAGES; ++i) fout.write((char*)zeros, PAGE_SIZE);
    fout.close();
    _maxSize = MEM_PAGES;
  }
  return;
}

}  // namespace dbtrain_mysql
