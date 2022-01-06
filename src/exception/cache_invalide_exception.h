#ifndef DBTRAIN_MYSQL_CACHE_INVALIDE_EXCEPTION_H
#define DBTRAIN_MYSQL_CACHE_INVALIDE_EXCEPTION_H

#include "defines.h"
#include "exception/exception.h"

namespace dbtrain_mysql {

class CacheInvalideException : public Exception {
 public:
  CacheInvalideException() : Exception() { _className = "CacheInvalideException"; }
};

}  // namespace dbtrain_mysql

#endif