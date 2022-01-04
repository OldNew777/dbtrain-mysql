#ifndef DBTRAIN_MYSQL_CACHE_H
#define DBTRAIN_MYSQL_CACHE_H

#include "defines.h"
#include "macros.h"
#include "exception/exceptions.h"
#include "os/raw_page.h"
#include "utils/bitmap.h"
#include <fstream>
#include <list>

namespace dbtrain_mysql
{
    class CacheLine {
    private:
        bool _dirty = false;
        bool _valid = false;
        RawPage* _rawPage = nullptr;
        PageID _pid;
        void _writeBack();
    public:
        bool getDirty(){return _dirty;}
        bool getValid(){return _valid;}
        PageID getPageID(){return _pid;}
        void Read(uint8_t* dst, PageOffset nSize, PageOffset nOffset = 0);
        void Write(const uint8_t* src, PageOffset nSize, PageOffset nOffset = 0);
        void Evict();

        CacheLine(PageID pid);
        ~CacheLine();
    };



    
    class CacheGroup{
    private:
        std::list<CacheLine*> _cacheGroup;
        CacheLine* _getPage(PageID pid);

    public:
        CacheGroup();
        ~CacheGroup();
        void DeletePage(PageID pid);
        void ReadPage(PageID pid, uint8_t* dst, PageOffset nSize,
                        PageOffset nOffset = 0);
        void WritePage(PageID pid, const uint8_t* src, PageOffset nSize,
                        PageOffset nOffset = 0);
        // void Evict(PageID pid);
        void NewPage(PageID pid);

    };
} // namespace dbtrain_mysql


#endif //DBTRAIN_MYSQL_CACHE_H