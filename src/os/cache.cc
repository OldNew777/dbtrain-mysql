#include "cache.h"
namespace dbtrain_mysql {
////// CacheLine //////
CacheLine::CacheLine(PageID pid) {
  _pid = pid;

  std::ifstream fin(DB_PAGE_NAME, std::ios::binary);
  if (!fin) {
    auto e =
        CacheInvalideException("CacheLine::CacheLine: DB_Page.dat not exist");
    std::cout << e.what() << "\n";
    throw e;
  }
  uint8_t pTemp[PAGE_SIZE];
  fin.seekg(pid * PAGE_SIZE, std::ios::beg);
  fin.read((char*)pTemp, PAGE_SIZE);
  _rawPage = new RawPage();
  _rawPage->Write(pTemp, PAGE_SIZE);
  _valid = true;
  _dirty = false;
  fin.close();
}

CacheLine::~CacheLine() {
  if (_dirty) {  // write_back
    _writeBack();
  }
  delete _rawPage;
}
void CacheLine::_writeBack() {
  std::fstream fout(DB_PAGE_NAME,
                    std::ios::binary | std::ios::out | std::ios::in);
  if (!fout) {
    auto e = CacheInvalideException(
        "CacheLine::_writeBack(): DB_Page.dat not exist");
    std::cout << e.what() << "\n";
    throw e;
  }
  uint8_t pTemp[PAGE_SIZE];
  _rawPage->Read(pTemp, PAGE_SIZE);
  fout.seekp(_pid * PAGE_SIZE, std::ios::beg);
  fout.write((char*)pTemp, PAGE_SIZE);
  fout.close();
}
void CacheLine::Read(uint8_t* dst, PageOffset nSize, PageOffset nOffset) {
  if (_rawPage == nullptr) {
    auto e = CacheInvalideException("CacheLine::Read: _rawPage == nullptr");
    std::cout << e.what() << "\n";
    throw e;
  }
  _rawPage->Read(dst, nSize, nOffset);
}
void CacheLine::Write(const uint8_t* src, PageOffset nSize,
                      PageOffset nOffset) {
  if (_rawPage == nullptr) {
    auto e = CacheInvalideException("CacheLine::Write: _rawPage == nullptr");
    std::cout << e.what() << "\n";
    throw e;
  }
  _rawPage->Write(src, nSize, nOffset);
  _dirty = true;
}
void CacheLine::Evict() {
  if (_dirty) _writeBack();

  _valid = false;
  _dirty = false;
}

////// CacheGroup //////

CacheGroup::CacheGroup() {}
CacheGroup::~CacheGroup() {
  for (auto it = _cacheGroup.begin(); it != _cacheGroup.end(); it++) {
    delete *it;
  }
}
CacheLine* CacheGroup::_getPage(PageID pid) {
  // printf("cache:\n");
  for (auto it = _cacheGroup.begin(); it != _cacheGroup.end(); it++) {
    if (*it == nullptr) {
      auto e =
          CacheInvalideException("CacheGroup::_getPage: Cacheline not exist");
      std::cout << e.what() << "\n";
      throw e;
    }
    // printf("pid: %d\n", (*it)->getPageID());
    if ((*it)->getPageID() == pid) {                             // hit
      _cacheGroup.splice(_cacheGroup.begin(), _cacheGroup, it);  // LRU
      return _cacheGroup.front();
    }
  }
  // not hit
  // printf("new cache line: %d\n", pid);
  _cacheGroup.push_front(new CacheLine(pid));  // get a new page
  if (_cacheGroup.size() > CACHE_GROUP_NUM) {  // LRU
    if (_cacheGroup.back() == nullptr) {
      auto e =
          CacheInvalideException("CacheGroup::_getPage: Cacheline not exist");
      std::cout << e.what() << "\n";
      throw e;
    }
    delete _cacheGroup.back();
    _cacheGroup.pop_back();
  }
  return _cacheGroup.front();
}

void CacheGroup::ReadPage(PageID pid, uint8_t* dst, PageOffset nSize,
                          PageOffset nOffset) {
  // printf("read page: %d\n",pid);
  _getPage(pid)->Read(dst, nSize, nOffset);
}
void CacheGroup::WritePage(PageID pid, const uint8_t* src, PageOffset nSize,
                           PageOffset nOffset) {
  // printf("write page: %d\n",pid);
  _getPage(pid)->Write(src, nSize, nOffset);
}
void CacheGroup::DeletePage(PageID pid) {
  // printf("delete page %d \n", pid);
  for (auto it = _cacheGroup.begin(); it != _cacheGroup.end(); it++) {
    if (*it == nullptr) {
      auto e = CacheInvalideException();
      std::cout << e.what() << "\n";
      throw e;
    }
    if ((*it)->getPageID() == pid) {  // hit
      delete (*it);
      _cacheGroup.erase(it);
      return;
    }
  }
  auto e = CacheInvalideException();
  std::cout << e.what() << "\n";
  throw e;
}
void CacheGroup::NewPage(PageID pid) {
  _cacheGroup.push_front(new CacheLine(pid));  // get a new page
  if (_cacheGroup.size() > CACHE_GROUP_NUM) {  // LRU
    if (_cacheGroup.back() == nullptr) {
      auto e =
          CacheInvalideException("CacheGroup::NewPage: Cacheline not exist");
      std::cout << e.what() << "\n";
      throw e;
    }
    delete _cacheGroup.back();
    _cacheGroup.pop_back();
  }
}
}  // namespace dbtrain_mysql