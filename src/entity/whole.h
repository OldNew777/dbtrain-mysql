#ifndef DBTRAIN_MYSQL_WHOLE_H
#define DBTRAIN_MYSQL_WHOLE_H

#include "defines.h"
#include "entity_manager.h"
#include "page/database_page.h"
#include "table.h"

namespace dbtrain_mysql {

// class Whole : public EntityManager {
//  public:
//   Whole();
//   virtual ~Whole();

//   Database* GetDatabase(const String& sDatabaseName);
//   Database* CreateDatabase(const String& sDatabaseName);
//   void DropDatabase(const String& sDatabaseName);
//   void RenameDatabase(const String& sOldDatabaseName,
//                       const String& sNewDatabaseName);

//   std::vector<String> GetDatabaseNames() const;

//   virtual EntityType GetEntityType() const;

//  protected:
//   virtual void Init() override;
// };

}  // namespace dbtrain_mysql

#endif