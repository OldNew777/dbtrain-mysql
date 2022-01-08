#ifndef DBTRAIN_MYSQL_MACROS_H
#define DBTRAIN_MYSQL_MACROS_H

#include "defines.h"

namespace dbtrain_mysql {

#define DB_DATA_PATH "./data/"
#define DB_BITMAP_NAME "./data/DB_BITMAP"
#define DB_PAGE_NAME "./data/DB_PAGE"

#define BIG_PRIME 100003U

const PageOffset PAGE_SIZE = 4096;
const PageOffset HEADER_SIZE = 64;
const PageOffset DATA_SIZE = PAGE_SIZE - HEADER_SIZE;

const PageID MEM_PAGES = 1U << 12;
const PageID DB_PAGES_MAX = 1U << 24;

const PageID NULL_PAGE = 0xFFFFFFFF;
const SlotID NULL_SLOT = 0xFFFF;

const PageID MYSQL_MANAGER_PAGEID = 0;

const PageOffset DATABASE_NAME_SIZE = 64;
const PageOffset TABLE_NAME_SIZE = 64;
const PageOffset COLUMN_NAME_SIZE = 64;
const PageOffset INDEX_NAME_SIZE = TABLE_NAME_SIZE + 1 + COLUMN_NAME_SIZE;

const Size FIELD_TYPE_BYTES = 1;
const Size FIELD_SIZE_MAX_BYTES = 2;
const Size FIELD_SIZE_MAX = (1 << ((FIELD_SIZE_MAX_BYTES << 3) - 1)) - 1;
const Size COLUMN_NUM_MAX = 32;

const Size COLUMN_STATUS_BYTES = 1;

const uint32_t CACHE_GROUP_NUM = 1 << 14;

const uint32_t FIELD_INT_TYPE_SIZE = 4;
const uint32_t FIELD_FLOAT_TYPE_SIZE = 4;

const Size SHADOW_STATUS_SIZE = 4;
const String SHADOW_STATUS_FOREIGN_KEY = "FORE";
const String SHADOW_STATUS_REFERED_KEY = "REFE";
const String SHADOW_STATUS_NAME = "Status";
const String SHADOW_LOCAL_COLUMN_NAME = "LocalColumnName";
const String SHADOW_FOREIGN_COLUMN_NAME = "ForeignColumnName";
const String SHADOW_FOREIGN_TABLE_NAME = "ForeignTableName";
}  // namespace dbtrain_mysql

#endif
