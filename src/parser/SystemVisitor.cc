#include "SystemVisitor.h"

#include <float.h>

namespace dbtrain_mysql {

SystemVisitor::SystemVisitor(Instance *pDB) : _pDB{pDB} { assert(_pDB); }

}  // namespace dbtrain_mysql