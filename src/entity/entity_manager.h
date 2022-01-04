#ifndef DBTRAIN_MYSQL_ENTITY_MANAGER_H
#define DBTRAIN_MYSQL_ENTITY_MANAGER_H

#include <map>

#include "defines.h"
#include "entity.h"
#include "page/manager_page.h"

namespace dbtrain_mysql {

class EntityManager : public Entity {
 public:
  EntityManager(ManagerPage* pManagerPage);
  EntityManager();
  virtual ~EntityManager();

  std::vector<String> GetEntityNames() const;
  void Clear();

 protected:
  std::map<String, Entity*> _iEntityMap;
  std::map<String, PageID> _iEntityPageIDMap;
  std::map<String, PageSlotID> _iEntityPageSlotIDMap;

  void InsertEntity(const String& sEntityName);
  void DeleteEntity(const String& sEntityName, PageSlotID nPageSlotID);

  virtual void Init() override;
};

}  // namespace dbtrain_mysql

#endif
