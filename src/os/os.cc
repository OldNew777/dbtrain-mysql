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

void OS::CheckFileExist(){
  std::ifstream fin(DB_PAGE_NAME, std::ios::binary);
  if(!fin) {
    printf("OS::CheckFileExist: DB_Page.dat not exists\n");
    std::ofstream fout(DB_PAGE_NAME, std::ios::binary);
    uint8_t* ptemp = new uint8_t[PAGE_SIZE * MEM_PAGES];
    memset(ptemp, 0, PAGE_SIZE * MEM_PAGES);
    fout.write((char*)ptemp, PAGE_SIZE * MEM_PAGES);
    fout.close();
    delete ptemp;
  }
  else{
    fin.close();
  }
}

OS::OS() {
  printf("OS()\n");
  _pUsed = new Bitmap(MAX_MEM_PAGES);
  _cache = new CacheGroup*[CACHE_ASSOCIATIVE];
  for (int i = 0; i < CACHE_ASSOCIATIVE; i++) {
    _cache[i] = new CacheGroup();
  }
  _nClock = 0;
  LoadBitmap();
  initDBPage();
  // printf("pUsed num:%d\n", _pUsed->GetUsed());
}

OS::~OS() {
  // printf("pUsed num:%d\n", _pUsed->GetUsed());
  printf("~OS()\n");
  StoreBitmap();
  for (int i = 0; i < CACHE_ASSOCIATIVE; i++) {
    delete _cache[i];
  }
  delete[] _cache;
  delete _pUsed;
}

PageID OS::NewPage() {
  Size tmp = _nClock;
  do {
    if (!_pUsed->Get(_nClock)) {
      while(_nClock > _maxSize  && _maxSize < MAX_MEM_PAGES){
        printf("1\n");
        std::fstream fout(DB_PAGE_NAME, std::ios::binary | std::ios::in | std::ios::out);
        uint8_t* ptemp = new uint8_t[PAGE_SIZE * MEM_PAGES];
        memset(ptemp, 0, PAGE_SIZE * MEM_PAGES);
        fout.seekp(0, std::ios::end);
        fout.write((char*) ptemp, PAGE_SIZE * MEM_PAGES);
        fout.close();
        delete ptemp;
        _maxSize += MEM_PAGES;
      }
      _getCacheGroup(_nClock)->NewPage(_nClock);
      _pUsed->Set(_nClock);
      // printf("\nnewpage: %d\n", _nClock);
      return _nClock;
    } else {
      _nClock += 1;
      _nClock %= MAX_MEM_PAGES;
    }
  } while (_nClock != tmp);
  throw NewPageException();
}

void OS::DeletePage(PageID pid) {
  if (!_pUsed->Get(pid)) throw PageNotInitException(pid);
  _getCacheGroup(pid)->DeletePage(pid);
  _pUsed->Unset(pid);
}

void OS::ReadPage(PageID pid, uint8_t* dst, PageOffset nSize,
                  PageOffset nOffset) {
  if (!_pUsed->Get(pid)) throw PageNotInitException(pid);
  _getCacheGroup(pid)->ReadPage(pid, dst, nSize, nOffset);
}

void OS::WritePage(PageID pid, const uint8_t* src, PageOffset nSize,
                   PageOffset nOffset) {
  if (!_pUsed->Get(pid)) throw PageNotInitException(pid);
  // printf("write page\n");
  _getCacheGroup(pid)->WritePage(pid, src, nSize, nOffset);
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
  if (!_pUsed) throw OsException();
  return _pUsed->GetSize();
}

void OS::initDBPage() {

  std::ifstream fin(DB_PAGE_NAME, std::ios::binary);
  if(fin) {
    // printf("OS::initDBPage: DB_Page.dat exists\n");
    fin.seekg(0, fin.end);  
    Size size = fin.tellg(); 
    if(size % PAGE_SIZE != 0) {
      printf("size should be divisible by pagesize");
      throw CacheInvalideException();
    }
    _maxSize = size / PAGE_SIZE;
    fin.close();
  }
  else{
    // printf("OS::initDBPage: DB_Page.dat not exists\n");
    std::ofstream fout(DB_PAGE_NAME, std::ios::binary);
    uint8_t* ptemp = new uint8_t[PAGE_SIZE * MEM_PAGES];
    memset(ptemp, 0, PAGE_SIZE * MEM_PAGES);
    fout.write((char*)ptemp, PAGE_SIZE * MEM_PAGES);
    fout.close();
    delete ptemp;
    _maxSize = MEM_PAGES;
  }
  return;
}

}  // namespace dbtrain_mysql
