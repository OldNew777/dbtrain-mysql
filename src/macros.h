#ifndef DBTRAIN_MYSQL_MACROS_H
#define DBTRAIN_MYSQL_MACROS_H

#include "defines.h"

namespace dbtrain_mysql {

#define DB_BITMAP_NAME "DB_BITMAP.dat"
#define DB_PAGE_NAME "DB_PAGE.dat"

#define BIG_PRIME 100003U

const PageOffset PAGE_SIZE = 4096;
const PageOffset HEADER_SIZE = 64;
const PageOffset DATA_SIZE = PAGE_SIZE - HEADER_SIZE;

const PageID MEM_PAGES = 1U << 18;
const PageID DB_PAGES = 1U << 28;

const PageID NULL_PAGE = 0xFFFFFFFF;
const SlotID NULL_SLOT = 0xFFFF;

const PageID MYSQL_MANAGER_PAGEID = 0;

const PageOffset DATABASE_NAME_SIZE = 64;
const PageOffset TABLE_NAME_SIZE = 64;
const PageOffset COLUMN_NAME_SIZE = 64;
const PageOffset INDEX_NAME_SIZE = TABLE_NAME_SIZE + 1 + COLUMN_NAME_SIZE;

const Size FIELD_TYPE_BYTES = 1;
const Size FIELD_SIZE_MAX_BYTES = 2;
const Size COLUMN_NUM_MAX = 32;

const uint32_t CACHE_ASSOCIATIVE = 16;
const uint32_t CACHE_GROUP_NUM = 1024;

}  // namespace dbtrain_mysql

#endif
