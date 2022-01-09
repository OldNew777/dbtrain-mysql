#include "database.h"

#include "condition/conditions.h"
#include "exception/exceptions.h"
#include "macros.h"
#include "os/os.h"
#include "page/record_page.h"
#include "page/table_page.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

Database::Database(DatabasePage* pDatabasePage) : EntityManager(pDatabasePage) {
  _pIndexManager = new IndexManager(pDatabasePage->GetIndexManagerPageID());
  Init();
}

Database::Database(PageID nDatabasePageID) : EntityManager() {
  DatabasePage* pDatabasePage = new DatabasePage(nDatabasePageID);
  _pManagerPage = pDatabasePage;
  _pIndexManager = new IndexManager(pDatabasePage->GetIndexManagerPageID());
  Init();
}

Database::~Database() { delete _pIndexManager; }

IndexManager* Database::GetIndexManager() const { return _pIndexManager; }

Table* Database::GetTable(const String& sTableName) {
  if (_iEntityMap.find(sTableName) == _iEntityMap.end()) {
    if (_iEntityPageIDMap.find(sTableName) == _iEntityPageIDMap.end()) {
      // no table named as it / not loaded
      return nullptr;
    } else {
      // not cached
      _iEntityMap[sTableName] = new Table(_iEntityPageIDMap[sTableName]);
      return dynamic_cast<Table*>(_iEntityMap[sTableName]);
    }
  }
  // cached
  return dynamic_cast<Table*>(_iEntityMap[sTableName]);
}

void Database::CreateTable(const String& sTableName, const Schema& iSchema) {
  // Table existed before
  if (GetTable(sTableName) != nullptr) {
    auto e = TableExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  #ifdef FRONT_END_DEBUG
  printf("\n%s:\n", sTableName.data());
  printf("name\t\ttype\tcanNull\tpk\tfk\n");
  for(int i = 0; i < iSchema.GetSize(); i ++){
    const Column& column = iSchema.GetColumn(i);
    column.Show();
  }
  #endif //FRONT_END_DEBUG
  const

  #ifndef FRONT_END_DEBUG
  // check foreign key
  // insert foreign key
  const Column& FKPKCol = iSchema.GetColumn(iSchema.GetSize());
  const std::vector<String>& sPKNameVec = FKPKCol.GetPKNameVec();
  const std::vector<String>& sFKNameVec = FKPKCol.GetFKNameVec();
  const std::vector<std::vector<String> >& iPKVec = FKPKCol.GetPKVec();
  const std::vector<std::vector<std::vector<String> > >& 
    iFKVec = FKPKCol.GetFKVec();

  #ifndef NO_FOREIGN_KEY
  for(int i = 0; i < iSchema.GetSize(); ++i) {
    const Column& column = iSchema.GetColumn(i);
    if (column.GetIsForeign()) {
      //TODO: 检查依赖表的相关列有没有null
      // insert local shadow table
    }
    // printf("3\n");
  }
  #endif //NO_FOREIGN_KEY

  // Create table and cache it
  TablePage* pPage = new TablePage(iSchema);
  Table* pTable = new Table(pPage);
  _iEntityMap[sTableName] = pTable;
  _iEntityPageIDMap[sTableName] = pPage->GetPageID();

  #ifndef NO_INDEX
  //insert index
  for (int i = 0; i < iSchema.GetSize(); ++i) {
    const Column& column = iSchema.GetColumn(i);
    if (column.GetIsPrimary()) CreateIndex(sTableName, column.GetName());
  }
  #endif

  for (int i = 0; i < iSchema.GetSize(); ++i) {
    const Column& column = iSchema.GetColumn(i);
    if (column.GetIsForeign()) {
      //TODO: insert foreign key
    }
    // printf("3\n");
  }
  #endif //FRONT_END_DEBUG
}

void Database::DropTable(const String& sTableName) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  _pIndexManager->DropIndex(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  pTable->Clear();
  delete pTable;
  OS::GetOS()->DeletePage(_iEntityPageIDMap[sTableName]);
  _iEntityMap.erase(sTableName);
  _iEntityPageIDMap.erase(sTableName);
  //TODO: 清除key表的对应行
  DeleteEntity(sTableName, _iEntityPageSlotIDMap[sTableName]);
}

void Database::RenameTable(const String& sOldTableName,
                           const String& sNewTableName) {
  Table* pTable = GetTable(sOldTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sOldTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  if (GetTable(sNewTableName) != nullptr) {
    auto e = TableExistException(sNewTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  //TODO: RENAME key表的对应行
  DeleteEntity(sOldTableName, _iEntityPageSlotIDMap[sOldTableName]);
  InsertEntity(sNewTableName);

  _iEntityMap[sNewTableName] = pTable;
  _iEntityPageIDMap[sNewTableName] = _iEntityPageIDMap[sOldTableName];
  _iEntityMap.erase(sOldTableName);
  _iEntityPageIDMap.erase(sOldTableName);
}

std::vector<String> Database::GetTableNames() { return GetEntityNames(); }

std::vector<String> Database::GetColumnNames(const String& sTableName) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  return pTable->GetColumnNames();
}

std::vector<PageSlotID> Database::Search(
    const String& sTableName, Condition* pCond,
    const std::vector<Condition*>& iIndexCond) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  std::vector<PageSlotID> ans;
  if (iIndexCond.size() > 0) {
    int start = 0;
    if (pCond != nullptr) {
      ans = pTable->SearchRecord(pCond);
    } else {
      start = 1;
      IndexCondition* pIndexCond = dynamic_cast<IndexCondition*>(iIndexCond[0]);
      auto iName = pIndexCond->GetIndexName();
      auto iRange = pIndexCond->GetIndexRange();
      ans = _pIndexManager->GetIndex(iName.first, iName.second)
                ->Range(iRange.first, iRange.second);
    }
    for (Size i = start; i < iIndexCond.size(); ++i) {
      IndexCondition* pIndexCond = dynamic_cast<IndexCondition*>(iIndexCond[i]);
      auto iName = pIndexCond->GetIndexName();
      auto iRange = pIndexCond->GetIndexRange();
      ans =
          Intersection(ans, _pIndexManager->GetIndex(iName.first, iName.second)
                                ->Range(iRange.first, iRange.second));
    }
  } else {
    ans = pTable->SearchRecord(pCond);
  }

  return ans;
}

uint32_t Database::Delete(const String& sTableName, Condition* pCond,
                          const std::vector<Condition*>& iIndexCond) {
  //TODO: delete to be finished
  auto iResVec = Search(sTableName, pCond, iIndexCond);
  Table* pTable = GetTable(sTableName);
  bool bHasIndex = _pIndexManager->HasIndex(sTableName);
  for (const auto& iPair : iResVec) {
    // Handle Delete on Index
    if (bHasIndex) {
      Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
      auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
      for (const auto& sCol : iColNames) {
        FieldID nPos = pTable->GetColPos(sCol);
        Field* pKey = pRecord->GetField(nPos);
        _pIndexManager->GetIndex(sTableName, sCol)->Delete(pKey, iPair);
      }
    }

    pTable->DeleteRecord(iPair.first, iPair.second);
  }
  return iResVec.size();
}

uint32_t Database::Update(const String& sTableName, Condition* pCond,
                          const std::vector<Condition*>& iIndexCond,
                          const std::vector<Transform>& iTrans) {
  //TODO: update to be finished
  auto iResVec = Search(sTableName, pCond, iIndexCond);
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  // check NOT-NULL / PRIMARY-KEY / UNIQUE KEY
  std::vector<String> iColNameVec = GetColumnNames(sTableName);
  for (int i = 0; i < iTrans.size(); ++i) {
    const String& sColName = iColNameVec[iTrans[i].GetColPos()];
    if (iTrans[i].GetField()->GetType() == FieldType::NULL_TYPE &&
        (!pTable->GetCanBeNull(sColName) || pTable->GetIsPrimary(sColName))) {
      auto e = FieldListException("Column should not be NULL");
      std::cout << e.what() << "\n";
      throw e;
    }
  }
  bool primaryKeyConflict = false;
  for (int i = 0; i < iTrans.size(); ++i) {
    const String& sColName = iColNameVec[iTrans[i].GetColPos()];
    if (pTable->GetIsPrimary(sColName) || pTable->GetIsUnique(sColName)) {
      primaryKeyConflict = true;
      // check whether primary key conflicts with other records
      std::vector<PageSlotID> iDuplicated =
          _GetDuplicated(sTableName, sColName, iTrans[i].GetField());
#ifdef PRIMARY_KEY_DEBUG
      printf("iResVec.size() = %d\n", iResVec.size());
      printf("iDuplicated.size() = %d\n", iDuplicated.size());
      printf("Intersection(iResVec, iDuplicated).size() = %d\n",
             Intersection(iResVec, iDuplicated).size());
#endif
      if(iDuplicated.size() != 0 && pTable->GetIsUnique(sColName)){
        auto e = Exception("Update fail:Unique Key Exists");
        std::cout << e.what() << "\n";
        throw e;
      }
      if (iResVec.size() + iDuplicated.size() -
              Intersection(iResVec, iDuplicated).size() <=
          1) {
        primaryKeyConflict = false;
        break;
      }
    }
  }
  if (primaryKeyConflict) {
    // add exception here
    auto e = Exception("Update fail:Primary Key Exists");
    std::cout << e.what() << "\n";
    throw e;
  }

  
  #ifndef NO_FOREIGN_KEY
  //check fk
  for (int i = 0; i < iTrans.size(); ++i) {
    const String& sColName = iColNameVec[iTrans[i].GetColPos()];
    if (pTable->GetIsForeign(sColName)) {
      std::vector<std::pair<String, String> > fPairVec =  GetForeignKeys(sTableName, sColName);
      for(auto& iPair: fPairVec){
        const String& fTableName = iPair.first;
        const String& fColName = iPair.second;
        std::vector<PageSlotID> iDuplicated =
          _GetDuplicated(fTableName, fColName, iTrans[i].GetField());
        if(iDuplicated.size() != 0){
          ForeignKeyException e("Update fail: Foreign key not in range");
          printf("%s\n", e.what());
          throw e;
        }
      }
    }
    if(pTable->GetIsRefered(sColName)){
      //check refered key 需要确保改变的那个键的没有对应的依赖值
      std::vector<std::pair<String, String> > rPairVec =  GetForeignKeys(sTableName, sColName);
      for(auto& iPair: rPairVec){
        const String& rTableName = iPair.first;
        const String& rColName = iPair.second;
        MemResult* memRes = new MemResult(pTable->GetColumnNames());
        for(auto& psid: iResVec){
          memRes->PushBack(pTable->GetRecord(psid.first, psid.second));
        }
        for(int j = 0; j < memRes->GetDataSize(); j ++){
          std::vector<PageSlotID> iDuplicated =
          _GetDuplicated(rTableName, rColName, memRes->GetField(j, iTrans[i].GetColPos()));
          if(iDuplicated.size() != 0){
            if(memRes) delete memRes;
            ForeignKeyException e("Update fail: A key has a reference dependence");
            printf("%s\n", e.what());
            throw e;
          }
        }
        if(memRes) delete memRes;
      }
    }
  }
  
  #endif

  bool bHasIndex = _pIndexManager->HasIndex(sTableName);
  for (const auto& iPair : iResVec) {
    // Handle Delete on Index
    if (bHasIndex) {
      Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
      auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
      for (const auto& sCol : iColNames) {
        FieldID nPos = pTable->GetColPos(sCol);
        Field* pKey = pRecord->GetField(nPos);
        _pIndexManager->GetIndex(sTableName, sCol)->Delete(pKey, iPair);
      }
      delete pRecord;
    }

    pTable->UpdateRecord(iPair.first, iPair.second, iTrans);

    // Handle Insert on Index
    if (bHasIndex) {
      Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
      auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
      for (const auto& sCol : iColNames) {
        FieldID nPos = pTable->GetColPos(sCol);
        Field* pKey = pRecord->GetField(nPos);
        _pIndexManager->GetIndex(sTableName, sCol)->Insert(pKey, iPair);
      }
      delete pRecord;
    }
  }
  return iResVec.size();
}

PageSlotID Database::Insert(const String& sTableName,
                            const std::vector<String>& iRawVec) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  std::vector<std::string> iColNameVec = pTable->GetColumnNames();
  if (iColNameVec.size() != iRawVec.size()) {
    auto e = FieldListException("Column num does not correspond");
    std::cout << e.what() << "\n";
    throw e;
  }

  #ifndef NO_INSERT_CHECK;
  // check null
  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    if (iRawVec[i] == "NULL" &&
        (!pTable->GetCanBeNull(sColName) || pTable->GetIsPrimary(sColName))) {
      auto e = FieldListException("Column should not be NULL");
      std::cout << e.what() << "\n";
      throw e;
    }
  }

  Record* pRecord = pTable->EmptyRecord();
  try {
    pRecord->Build(iRawVec);
  } catch (const Exception& e) {
    delete pRecord;
    throw e;
  }

  // check primary key
  std::vector<PageSlotID> duplicatedVec;
  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    
    if (pTable->GetIsPrimary(sColName) || pTable->GetIsUnique(sColName)) {
      // check whether primary key conflicts with other records
      Field* pField = pRecord->GetField(i);
      if(duplicatedVec.size() == 0){
        duplicatedVec = _GetDuplicated(sTableName, sColName, pField);
      }
      else{
        duplicatedVec = Intersection(_GetDuplicated(sTableName, sColName, pField)
                                      , duplicatedVec);
      }
      if (duplicatedVec.size() == 0) {
        break;
      }
      else if(pTable->GetIsUnique(sColName)){
        auto e = Exception("Unique key existed");
        std::cout << e.what() << "\n";
        throw e;
      }
    }
  }
  if (duplicatedVec.size() != 0) {
    // add exception here
    String str = "";
    #ifdef PRIMARY_KEY_DEBUG
    for(auto& row: iRawVec){
      str += row + " ";
    }
    #endif
    auto e = Exception("Primary key existed" + str);
    std::cout << e.what() << "\n";
    throw e;
  }

  // check foreignkey
  bool ForeignKeyCheck = false;
  std::vector<PageSlotID> iDuplicated;
  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    if (pTable->GetIsForeign(sColName)) {
      ForeignKeyCheck = true;
      // check whether primary key conflicts with other records
      Field* pField = pRecord->GetField(i);
      std::vector<std::pair<String, String>> fPairVec =
          GetForeignKeys(sTableName, sColName);
      // printf("FK of %s: %s %s\n", sColName.data(), fPair.first.data(),
      // fPair.second.data());
      std::vector<PageSlotID> tmpDuplicated;
      for (auto& fPair : fPairVec) {
        const String& fTableName = fPair.first;
        const String& fColName = fPair.second;
        #ifdef FOREIGN_KEY_DEBUG
        printf("%s(%s): %s %s\n",sColName.data(), pField->ToString().data(),
          fTableName.data(), fColName.data());
        #endif
        std::vector<PageSlotID> tmp = _GetDuplicated(fTableName, fColName, pField);
        tmpDuplicated.insert(tmpDuplicated.end(), tmp.begin(), tmp.end());
      }
      if(iDuplicated.size() == 0){
        iDuplicated = tmpDuplicated;
      }
      else{
        iDuplicated = Intersection(iDuplicated, tmpDuplicated);
      }
      if(iDuplicated.size() == 0){
        break;
      }
    }
  }
  if(ForeignKeyCheck && iDuplicated.size() == 0){
    ForeignKeyException e("Foreign key out of range");
    printf("%s\n", e.what());
    throw e;
  }
  #endif

  PageSlotID iPair = pTable->InsertRecord(pRecord);
  #ifndef NO_INDEX
  // Handle Insert on Index
  if (_pIndexManager->HasIndex(sTableName)) {
    auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
    for (const auto& sCol : iColNames) {
      FieldID nPos = pTable->GetColPos(sCol);
      Field* pKey = pRecord->GetField(nPos);
      _pIndexManager->GetIndex(sTableName, sCol)->Insert(pKey, iPair);
    }
  }
  #endif

  delete pRecord;
  return iPair;
}

PageSlotID Database::Insert(const String& sTableName,
                            const std::vector<Field*>& iValueVec) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  std::vector<std::string> iColNameVec = pTable->GetColumnNames();
  if (iColNameVec.size() != iValueVec.size()) {
    auto e = FieldListException("Column num does not correspond");
    std::cout << e.what() << "\n";
    throw e;
  }

  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    if (iValueVec[i]->GetType() == FieldType::NULL_TYPE &&
        (!pTable->GetCanBeNull(sColName) || pTable->GetIsPrimary(sColName))) {
      auto e = FieldListException("Column should not be NULL");
      std::cout << e.what() << "\n";
      throw e;
    }
  }

  Record* pRecord = pTable->EmptyRecord();
  try {
    pRecord->Build(iValueVec);
  } catch (const Exception& e) {
    delete pRecord;
    throw e;
  }

#ifndef NO_INSERT_CHECK
// check primary key
  std::vector<PageSlotID> duplicatedVec;
  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    
    if (pTable->GetIsPrimary(sColName) || pTable->GetIsUnique(sColName)) {
      // check whether primary key conflicts with other records
      Field* pField = pRecord->GetField(i);
      if(duplicatedVec.size() == 0){
        duplicatedVec = _GetDuplicated(sTableName, sColName, pField);
      }
      else{
        duplicatedVec = Intersection(_GetDuplicated(sTableName, sColName, pField)
                                      , duplicatedVec);
      }
      if (duplicatedVec.size() == 0) {
        break;
      }
      else if(pTable->GetIsUnique(sColName)){
        auto e = Exception("Unique key existed");
        std::cout << e.what() << "\n";
        throw e;
      }
    }
  }
  if (duplicatedVec.size() != 0) {
    // add exception here
    String str = "";
    #ifdef PRIMARY_KEY_DEBUG
    for(auto& row: iValueVec){
      str += row->ToString() + " ";
    }
    #endif
    auto e = Exception("Primary key existed" + str);
    std::cout << e.what() << "\n";
    throw e;
  }

  // check foreignkey
  bool ForeignKeyCheck = false;
  std::vector<PageSlotID> iDuplicated;
  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    if (pTable->GetIsForeign(sColName)) {
      ForeignKeyCheck = true;
      // check whether primary key conflicts with other records
      Field* pField = pRecord->GetField(i);
      std::vector<std::pair<String, String>> fPairVec =
          GetForeignKeys(sTableName, sColName);
      // printf("FK of %s: %s %s\n", sColName.data(), fPair.first.data(),
      // fPair.second.data());
      std::vector<PageSlotID> tmpDuplicated;
      for (auto& fPair : fPairVec) {
        const String& fTableName = fPair.first;
        const String& fColName = fPair.second;
        #ifdef FOREIGN_KEY_DEBUG
        printf("%s(%s): %s %s\n",sColName.data(), pField->ToString().data(),
          fTableName.data(), fColName.data());
        #endif
        std::vector<PageSlotID> tmp = _GetDuplicated(fTableName, fColName, pField);
        tmpDuplicated.insert(tmpDuplicated.end(), tmp.begin(), tmp.end());
      }
      if(iDuplicated.size() == 0){
        iDuplicated = tmpDuplicated;
      }
      else{
        iDuplicated = Intersection(iDuplicated, tmpDuplicated);
      }
      if(iDuplicated.size() == 0){
        break;
      }
    }
  }
  if(ForeignKeyCheck && iDuplicated.size() == 0){
    ForeignKeyException e("Foreign key out of range");
    printf("%s\n", e.what());
    throw e;
  }
  #endif

  PageSlotID iPair = pTable->InsertRecord(pRecord);
  #ifndef NO_INDEX
  // Handle Insert on Index
  if (_pIndexManager->HasIndex(sTableName)) {
    auto iColNames = _pIndexManager->GetTableIndexes(sTableName);
    for (const auto& sCol : iColNames) {
      FieldID nPos = pTable->GetColPos(sCol);
      Field* pKey = pRecord->GetField(nPos);
      _pIndexManager->GetIndex(sTableName, sCol)->Insert(pKey, iPair);
    }
  }
  #endif

  delete pRecord;
  return iPair;
}

std::vector<PageSlotID> Database::_GetDuplicated(const String& sTableName,
                                                 const String& sColName,
                                                 Field* pField) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  FieldID colPos = pTable->GetColPos(sColName);
  Field *pLow = pField->Clone(), *pHigh = pField->Clone();
  pHigh->Add();
  Condition* pCond = nullptr;
  std::vector<Condition*> iIndexCond{};
  #ifndef NO_INDEX
  if (IsIndex(sTableName, sColName)) {
    iIndexCond.push_back(new IndexCondition(sTableName, sColName, pLow, pHigh));
  } else {
  #endif

    pCond = new RangeCondition(colPos, pLow, pHigh);

  #ifndef NO_INDEX
  }
  #endif
  std::vector<PageSlotID> iPageSlotIDVec =
      Search(sTableName, pCond, iIndexCond);

#ifdef PRIMARY_KEY_DEBUG
  printf("\n%s.%s\n", sTableName.c_str(), sColName.c_str());
  printf("[%s, %s)\n", pLow->ToString().c_str(), pHigh->ToString().c_str());
  printf("Size = %d\n\n", int(iPageSlotIDVec.size()));
#endif

  if (pCond) delete pCond;
  for (auto pCond : iIndexCond) delete pCond;

  return iPageSlotIDVec;
}

void Database::CreateIndex(const String& sTableName, const String& sColName) {
  auto iAll = Search(sTableName, nullptr, {});
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  FieldType iType = pTable->GetType(sColName);
  _pIndexManager->AddIndex(sTableName, sColName, iType);
  // Handle Exists Data
  for (const auto& iPair : iAll) {
    FieldID nPos = pTable->GetColPos(sColName);
    Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
    Field* pKey = pRecord->GetField(nPos);
    _pIndexManager->GetIndex(sTableName, sColName)->Insert(pKey, iPair);
    delete pRecord;
  }
}

void Database::DropIndex(const String& sTableName, const String& sColName) {
  auto iAll = Search(sTableName, nullptr, {});
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  for (const auto& iPair : iAll) {
    FieldID nPos = pTable->GetColPos(sColName);
    Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
    Field* pKey = pRecord->GetField(nPos);
    _pIndexManager->GetIndex(sTableName, sColName)->Delete(pKey, iPair);
    delete pRecord;
  }
  _pIndexManager->DropIndex(sTableName, sColName);
}

bool Database::IsIndex(const String& sTableName, const String& sColName) {
  return _pIndexManager->IsIndex(sTableName, sColName);
}

Index* Database::GetIndex(const String& sTableName, const String& sColName) {
  return _pIndexManager->GetIndex(sTableName, sColName);
}

std::vector<Record*> Database::GetIndexInfos() {
  std::vector<Record*> iVec{};
  for (const auto& iPair : _pIndexManager->GetIndexInfos()) {
    FixedRecord* pInfo =
        new FixedRecord(4,
                        {FieldType::CHAR_TYPE, FieldType::CHAR_TYPE,
                         FieldType::CHAR_TYPE, FieldType::INT_TYPE},
                        {TABLE_NAME_SIZE, COLUMN_NAME_SIZE, 10, 4});
    pInfo->SetField(0, new CharField(iPair.first));
    pInfo->SetField(1, new CharField(iPair.second));
    pInfo->SetField(
        2,
        new CharField(toString(GetTable(iPair.first)->GetType(iPair.second))));
    pInfo->SetField(3,
                    new IntField(GetTable(iPair.first)->GetSize(iPair.second)));

    iVec.push_back(pInfo);
  }
  return iVec;
}

void Database::Clear() {
  _pIndexManager->Clear();
  // load tables to delete pages later
  for (auto iter : _iEntityPageIDMap)
    if (_iEntityMap.find(iter.first) == _iEntityMap.end() ||
        _iEntityMap[iter.first] == nullptr) {
      _iEntityMap[iter.first] = new Table(iter.second);
    }
  EntityManager::Clear();
}

EntityType Database::GetEntityType() const { return EntityType::DATABASE_TYPE; }

void Database::AddPrimaryKey(const String& sTableName,
                             const std::vector<String> sColName) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  //因为现有pk的信息是正确的，所以只需要检查现有信息
  //获取所有需要检查的新增列的信息
  std::vector<String> sColNameVec;
  for (int i = 0; i < sColName.size(); i++) {
    if (!pTable->GetIsPrimary(sColName[i])) sColNameVec.push_back(sColName[i]);
  }
  if (sColNameVec.size() == 0) return;
  std::vector<PageSlotID> psidVec = pTable->SearchRecord(nullptr);
  Result* result = new MemResult(pTable->GetColumnNames());
  for (auto& psid : psidVec) {
    result->PushBack(pTable->GetRecord(psid.first, psid.second));
  }
  //如果已经有其他外键，那么一定不需要检查新外键的重复性
  bool needCheckDuplication = true;
  std::vector<std::string> iColNameVec = pTable->GetColumnNames();
  for (int i = 0; i < iColNameVec.size(); i++) {
    if (pTable->GetIsPrimary(iColNameVec[i])) {
      needCheckDuplication = false;
      break;
    }
  }
  //检查重复性和null性
  if(needCheckDuplication){
    int errorTimes = 0;
    for(auto& colName: sColNameVec){
      if(_CheckDuplicate(sTableName, colName)){
        errorTimes ++;
      }
    }
    if(errorTimes == sColName.size()){
      printf("the new Primary Key column cannot be duplicated\n");
      throw AlterException("the new Primary Key column cannot be duplicated");
    }
  }
  for (auto& colName : sColName) {
    if (_CheckHaveNull(sTableName, colName)) {
      throw AlterException("the new Primary Key column cannot be Null");
    }
  }
  pTable->AddPrimaryKey(sColNameVec);
  // TODO: a space bug
  // if(result != nullptr) delete result;
  return;
}

void Database::DropPrimaryKey(const String& sTableName,
                              const String& sColName) {
  Table* pTable = GetTable(sTableName);
  pTable->DropPrimaryKey(sColName);
}
bool Database::_CheckHaveNull(const String& fTableName,
                              const String& fColName) {
  Table* fTable = GetTable(fTableName);
  if (fTable == nullptr) {
    auto e = TableNotExistException(fTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  if (!fTable->GetCanBeNull(fColName) || fTable->GetIsPrimary(fColName)) {
    return false;
  }
  // printf("into\n");
  FieldID colPos = fTable->GetColPos(fColName);
  Field *pLow = new NullField();
  Field *pHigh = pLow->Clone();
  pHigh->Add();
  Condition* pCond = nullptr;
  pCond = new RangeCondition(colPos, pLow, pHigh);
  std::vector<PageSlotID> iPageSlotIDVec = Search(fTableName, pCond, {});
  return (iPageSlotIDVec.size() != 0);
}

bool Database::_CheckDuplicate(const String& sTableName, const String& sColName){
  Table* fTable = GetTable(sTableName);
  std::vector<PageSlotID> fpsidVec = fTable->SearchRecord(nullptr);
  MemResult* result = new MemResult(fTable->GetColumnNames());
  for(auto& psid: fpsidVec)
    result->PushBack(fTable->GetRecord(psid.first, psid.second));
  FieldID colPos = fTable->GetColPos(sColName);
  std::set<String> pSet;
  for (int i = 0; i < result->GetDataSize(); i ++) {
    //TODO: 这么写可能会重复遍历
    if(pSet.count(result->GetFieldString(i, colPos)) != 0){
      if(result) delete result;
      return true;
    }
    pSet.insert(result->GetFieldString(i, colPos));
  }
  if(result) delete result;
  return false;
}

std::vector<std::pair<String, String>> Database::GetReferedKeys(const String& sTableName, const String& sColName){
  Table* pTable = GetTable("@" + sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  std::vector<std::pair<String, String>> retVec;
  FieldID colPos = pTable->GetColPos(SHADOW_LOCAL_COLUMN_NAME);
  std::vector<PageSlotID> iPageSlotIDVec = pTable->SearchRecord(nullptr);
  MemResult* res =
      new MemResult({SHADOW_STATUS_NAME, SHADOW_LOCAL_COLUMN_NAME,
                     SHADOW_FOREIGN_TABLE_NAME, SHADOW_FOREIGN_COLUMN_NAME});
  for (auto& psid : iPageSlotIDVec) {
    res->PushBack(pTable->GetRecord(psid.first, psid.second));
  }
  for (int i = 0; i < res->GetDataSize(); i++) {
    // printf("%s %s\n", res->GetFieldString(i, 0).data(),
    // res->GetFieldString(i, 1).data());
    if (res->GetFieldString(i, 0) != SHADOW_STATUS_REFERED_KEY ||
        res->GetFieldString(i, 1) != sColName)
      continue;
    retVec.push_back(
        std::make_pair(res->GetFieldString(i, 2), res->GetFieldString(i, 3)));
  }
  // if (retVec.size() == 0) {
  //   printf("there should be a refered key in shadow table\n");
  //   throw ForeignKeyException();
  // }
}
std::vector<std::pair<String, String>> Database::GetForeignKeys(
    const String& sTableName, const String& sColName) {
  
}

void Database::DropFroeignKey(const String& sTableName, const String& sColName) {
  //TODO: Drop FK to be done
}


void Database::AddUniqueKey(const String& sTableName, const String& sColName){
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  if(_CheckDuplicate(sTableName, sColName)){
    throw AlterException("the new Unique Key column cannot be duplicated");
  }
  pTable->AddUniqueKey(sColName);
}
}  // namespace dbtrain_mysql