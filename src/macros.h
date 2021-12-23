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
const Size TABLE_CAPTION = 128;

const PageID SYSTEM_PAGES = 32;
const PageID TABLE_MANAGER_PAGEID = 2;
const PageID INDEX_MANAGER_PAGEID = 3;
const PageID RECOVERY_MANAGER_PAGEID = 4;

const PageOffset TABLE_NAME_SIZE = 60;
const PageOffset INDEX_NAME_SIZE = 124;
const PageOffset COLUMN_NAME_SIZE = 60;

}  // namespace dbtrain_mysql

#endif
