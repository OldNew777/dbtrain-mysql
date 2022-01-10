#ifndef DBTRAIN_MYSQL_MANAGER_PAGE_H
#define DBTRAIN_MYSQL_MANAGER_PAGE_H

#include "defines.h"
#include "field/field.h"
#include "macros.h"
#include "page/page.h"
#include "record/fixed_record.h"

namespace dbtrain_mysql {

const PageOffset HEAD_PAGE_OFFSET = 16;
const PageOffset TAIL_PAGE_OFFSET = 20;
const PageOffset COLUMN_LEN_OFFSET = 24;
const PageOffset COLUMN_NAME_LEN_OFFSET = 28;

const PageOffset COLUMN_TYPE_OFFSET = 0;
const PageOffset COLUMN_SIZE_OFFSET =
    COLUMN_TYPE_OFFSET + COLUMN_NUM_MAX * FIELD_TYPE_BYTES;
const PageOffset COLUMN_NAME_OFFSET =
    COLUMN_SIZE_OFFSET + COLUMN_NUM_MAX * FIELD_SIZE_MAX_BYTES;
const PageOffset COLUMN_STATUS_OFFSET =
    COLUMN_NAME_OFFSET + COLUMN_NUM_MAX * COLUMN_NUM_MAX;

class EntityManager;

enum class ManagerPageType {
  DATABASE_PAGE_TYPE = 0,
  TABLE_PAGE_TYPE = 1,
  WHOLE_PAGE_TYPE = 2,
  KEY_PAGE_TYPE = 3,
};

class ManagerPage : public Page {
 public:
  ManagerPage();
  ManagerPage(PageID nPageID);
  virtual ~ManagerPage();

  PageID GetHeadID() const;
  PageID GetTailID() const;
  void SetHeadID(PageID nHeadID);
  void SetTailID(PageID nTailID);

  Size GetFieldSize() const;
  std::vector<FieldType> GetTypeVec() const;
  std::vector<Size> GetSizeVec() const;
  Size GetTotalSize() const;

  virtual ManagerPageType GetManagerPageType() const = 0;

 protected:
  std::map<String, FieldID> _iColMap;
  std::vector<FieldType> _iTypeVec;
  std::vector<Size> _iSizeVec;
  PageID _nHeadID, _nTailID;

  void Store();
  void Load();
  std::vector<std::pair<PageSlotID, Record*>> GetAllRecords() const;

  friend class EntityManager;
};

}  // namespace dbtrain_mysql

#endif