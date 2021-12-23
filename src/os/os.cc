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
  if (os != nullptr) {
    delete os;
    os = nullptr;
  }
}

OS::OS() {
  _pMemory = new RawPage*[MEM_PAGES];
  _pUsed = new Bitmap(MEM_PAGES);
  memset(_pMemory, 0, MEM_PAGES);
  _nClock = 0;
  LoadBitmap();
  LoadPages();
}

OS::~OS() {
  StoreBitmap();
  StorePages();
  for (size_t i = 0; i < MEM_PAGES; ++i)
    if (_pMemory[i]) delete _pMemory[i];
  delete[] _pMemory;
  delete _pUsed;
}

PageID OS::NewPage() {
  Size tmp = _nClock;
  do {
    if (!_pUsed->Get(_nClock)) {
      _pMemory[_nClock] = new RawPage();
      _pUsed->Set(_nClock);
      return _nClock;
    } else {
      _nClock += 1;
      _nClock %= MEM_PAGES;
    }
  } while (_nClock != tmp);
  throw NewPageException();
}

void OS::DeletePage(PageID pid) {
  if (!_pUsed->Get(pid)) throw PageNotInitException(pid);
  delete _pMemory[pid];
  _pMemory[pid] = 0;
  _pUsed->Unset(pid);
}

void OS::ReadPage(PageID pid, uint8_t* dst, PageOffset nSize,
                  PageOffset nOffset) {
  if (!_pUsed->Get(pid)) throw PageNotInitException(pid);
  _pMemory[pid]->Read(dst, nSize, nOffset);
}

void OS::WritePage(PageID pid, const uint8_t* src, PageOffset nSize,
                   PageOffset nOffset) {
  if (!_pUsed->Get(pid)) throw PageNotInitException(pid);
  _pMemory[pid]->Write(src, nSize, nOffset);
}

void OS::LoadBitmap() {
  std::ifstream fin(DB_BITMAP_NAME, std::ios::binary);
  if (!fin) return;
  uint8_t pTemp[MEM_PAGES / 8];
  fin.read((char*)pTemp, MEM_PAGES / 8);
  fin.close();
  _pUsed->Load(pTemp);
}

void OS::LoadPages() {
  std::ifstream fin(DB_PAGE_NAME, std::ios::binary);
  if (!fin) return;
  uint8_t pTemp[PAGE_SIZE];
  for (uint32_t i = 0; i < MEM_PAGES; ++i) {
    if (_pUsed->Get(i)) {
      fin.read((char*)pTemp, PAGE_SIZE);
      _pMemory[i] = new RawPage();
      _pMemory[i]->Write(pTemp, PAGE_SIZE);
    }
  }
  fin.close();
}

void OS::StoreBitmap() {
  std::ofstream fout(DB_BITMAP_NAME, std::ios::binary);
  if (!fout) return;
  uint8_t pTemp[MEM_PAGES / 8];
  _pUsed->Store(pTemp);
  fout.write((char*)pTemp, MEM_PAGES / 8);
  fout.close();
}

void OS::StorePages() {
  std::ofstream fout(DB_PAGE_NAME, std::ios::binary);
  if (!fout) return;
  uint8_t pTemp[PAGE_SIZE];
  for (uint32_t i = 0; i < MEM_PAGES; ++i) {
    if (_pUsed->Get(i)) {
      _pMemory[i]->Read(pTemp, PAGE_SIZE);
      fout.write((char*)pTemp, PAGE_SIZE);
    }
  }
  fout.close();
}

Size OS::GetUsedSize() const {
  if (!_pUsed) throw OsException();
  return _pUsed->GetSize();
}

}  // namespace dbtrain_mysql
