#include "cache.h"
namespace dbtrain_mysql {

uint8_t pTemp[PAGE_SIZE];

////// CacheLine //////
CacheLine::CacheLine(PageID pid) {
  _pid = pid;

  std::ifstream fin(String(DB_PAGE_NAME) + std::to_string(_pid / MEM_PAGES),
                    std::ios::binary);
  fin.seekg(pid % PAGE_SIZE, std::ios::beg);
  fin.read((char*)pTemp, PAGE_SIZE);
  _rawPage = new RawPage();
  _rawPage->Write(pTemp, PAGE_SIZE);
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
  std::fstream fout(String(DB_PAGE_NAME) + std::to_string(_pid / MEM_PAGES),
                    std::ios::binary | std::ios::out | std::ios::in);
  _rawPage->Read(pTemp, PAGE_SIZE);
  fout.seekp(_pid % PAGE_SIZE, std::ios::beg);
  fout.write((char*)pTemp, PAGE_SIZE);
  fout.close();
}

void CacheLine::Read(uint8_t* dst, PageOffset nSize, PageOffset nOffset) {
  _rawPage->Read(dst, nSize, nOffset);
}

void CacheLine::Write(const uint8_t* src, PageOffset nSize,
                      PageOffset nOffset) {
  _rawPage->Write(src, nSize, nOffset);
  _dirty = true;
}

////// CacheGroup //////

CacheGroup::CacheGroup() {
  _nClock = 0;
  _cacheGroup = new CacheLine*[CACHE_GROUP_NUM];
}

CacheGroup::~CacheGroup() {
  for (int i = 0; i < CACHE_GROUP_NUM; ++i) {
    if (_cacheGroup[i]) delete _cacheGroup[i];
  }
}

CacheLine* CacheGroup::_getPage(PageID pid) {
  std::unordered_map<dbtrain_mysql::PageID, int>::iterator iter;
  if ((iter = _cacheIndex.find(pid)) != _cacheIndex.end()) {
    // hit
    return _cacheGroup[iter->second];
  } else {
    // not hit
    if (_cacheIndex.size() == CACHE_GROUP_NUM) {
      _cacheIndex.erase(_cacheGroup[_nClock]->getPageID());
      delete _cacheGroup[_nClock];
    } else {
      while (_cacheGroup[_nClock] != nullptr) {
        if (++_nClock == CACHE_GROUP_NUM) _nClock = 0;
      }
    }
    CacheLine* pCacheLine = new CacheLine(pid);
    _cacheGroup[_nClock] = pCacheLine;
    _cacheIndex.insert({pid, _nClock});
    if (++_nClock == CACHE_GROUP_NUM) _nClock = 0;
    return pCacheLine;
  }
}

void CacheGroup::ReadPage(PageID pid, uint8_t* dst, PageOffset nSize,
                          PageOffset nOffset) {
  _getPage(pid)->Read(dst, nSize, nOffset);
}

void CacheGroup::WritePage(PageID pid, const uint8_t* src, PageOffset nSize,
                           PageOffset nOffset) {
  _getPage(pid)->Write(src, nSize, nOffset);
}

void CacheGroup::DeletePage(PageID pid) {
  std::unordered_map<dbtrain_mysql::PageID, int>::iterator iter;
  if ((iter = _cacheIndex.find(pid)) != _cacheIndex.end()) {
    // exist in cache
    delete _cacheGroup[iter->second];
    _cacheGroup[iter->second] = nullptr;
    _cacheIndex.erase(pid);
  }
}

}  // namespace dbtrain_mysql