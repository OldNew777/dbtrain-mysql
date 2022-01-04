#include "cache.h"
namespace dbtrain_mysql{
    ////// CacheLine //////
    CacheLine::CacheLine(PageID pid){
        std::ifstream fin(DB_PAGE_NAME, std::ios::binary);

        uint8_t pTemp[PAGE_SIZE];
        fin.seekg(pid * PAGE_SIZE, std::ios::beg);
        fin.read((char*)pTemp, PAGE_SIZE);
        _rawPage = new RawPage();
        _rawPage->Write(pTemp, PAGE_SIZE);
        _valid = true;
         fin.close();
    }

    CacheLine::~CacheLine(){
        if(_dirty){//write_back
            _writeBack();
            delete _rawPage;
        }
    }
    void CacheLine::_writeBack(){
        std::fstream fout(DB_PAGE_NAME, std::ios::binary | std::ios::out | std::ios::in);
        uint8_t pTemp[PAGE_SIZE];
        _rawPage->Read(pTemp, PAGE_SIZE);
        fout.seekp(_pid * PAGE_SIZE, std::ios::beg);
        printf("write back to %d\n", _pid);
        // printf("buffer:\n");
        // for(auto num: pTemp){
        //     printf("%x ", num);
        // }
        // printf("\n");
        fout.write((char*) pTemp, PAGE_SIZE);
        fout.close();
    }
    void CacheLine::Read(uint8_t* dst, PageOffset nSize, PageOffset nOffset){
        if(_rawPage == nullptr){
            throw CacheInvalideException();
        }
        _rawPage->Read(dst, nSize, nOffset);
    }
    void CacheLine::Write(const uint8_t* src, PageOffset nSize, PageOffset nOffset){
        if(_rawPage == nullptr){
            throw CacheInvalideException();
        }
        _rawPage->Write(src, nSize, nOffset);
        _dirty = true;
        
    }
    void CacheLine::Evict(){
        _writeBack();
        _valid = false;
        _dirty = false;
    }


    ////// CacheGroup //////

    CacheGroup::CacheGroup(){
        
    }
    CacheGroup::~CacheGroup(){
        for(auto it = _cacheGroup.begin(); it != _cacheGroup.end(); it ++){
            delete *it;
        }
    }
    CacheLine* CacheGroup::_getPage(PageID pid){
        for(auto it = _cacheGroup.begin(); it != _cacheGroup.end(); it ++){
            if(*it == nullptr){
                throw CacheInvalideException();
            }
            if((*it)->getPageID() == pid){//hit
                _cacheGroup.push_front(*it); //LRU
                CacheLine* tmp = *it;
                _cacheGroup.erase(it);
                return tmp;
            }
        }
        //not hit
        _cacheGroup.push_front(new CacheLine(pid));// get a new page
        if(++_size > CACHE_GROUP_NUM){//LRU
            if(_cacheGroup.back() == nullptr){throw CacheInvalideException();}
            delete _cacheGroup.back();
            _cacheGroup.pop_back();
        }
        return _cacheGroup.front();
    }

    void CacheGroup::ReadPage(PageID pid, uint8_t* dst, PageOffset nSize, PageOffset nOffset){
        // printf("read page: %d\n",pid);
        _getPage(pid)->Read(dst, nSize, nOffset);
    }
    void CacheGroup::WritePage(PageID pid, const uint8_t* src, PageOffset nSize, PageOffset nOffset){
        // printf("write page: %d\n",pid);
        _getPage(pid)->Write(src, nSize, nOffset);
    }
    void CacheGroup::DeletePage(PageID pid){
        for(auto it = _cacheGroup.begin(); it != _cacheGroup.end(); it ++){
            if(*it == nullptr){
                throw CacheInvalideException();
            }
            if((*it)->getPageID() == pid){//hit
                delete (*it);
                _cacheGroup.erase(it);
                return;
            }
        }
    }
    void CacheGroup::NewPage(PageID pid){
        _cacheGroup.push_front(new CacheLine(pid));// get a new page
        if(++_size > CACHE_GROUP_NUM){//LRU
            if(_cacheGroup.back() == nullptr){throw CacheInvalideException();}
            delete _cacheGroup.back();
            _cacheGroup.pop_back();
        }
    }
    void CacheGroup::Clear(){
        for(auto it = _cacheGroup.begin(); it != _cacheGroup.end(); it ++){
            if(*it == nullptr){
                throw CacheInvalideException();
            }
            delete (*it);
        }
        _cacheGroup.clear();
    }
}