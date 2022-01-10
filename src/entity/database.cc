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
  _pKeyManager = new KeyManager(pDatabasePage->GetKeyManagerPageID());
  Init();
}

Database::Database(PageID nDatabasePageID) : EntityManager() {
  DatabasePage* pDatabasePage = new DatabasePage(nDatabasePageID);
  _pManagerPage = pDatabasePage;
  _pIndexManager = new IndexManager(pDatabasePage->GetIndexManagerPageID());
  _pKeyManager = new KeyManager(pDatabasePage->GetKeyManagerPageID());
  Init();
}

Database::~Database() { 
  delete _pIndexManager; 
  delete _pKeyManager;
}

IndexManager* Database::GetIndexManager() const { return _pIndexManager; }
KeyManager* Database::GetKeyManager() const { return _pKeyManager; }

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
  
  const Column& iFKPKCol = iSchema.GetColumn(iSchema.GetSize() - 1);
  const std::vector<std::vector<std::vector<String> > >& iFKVec = iFKPKCol.GetFKVec();
  const std::vector<std::vector<String> >& iPKVec = iFKPKCol.GetPKVec();
  const std::vector<String>& iFKNameVec = iFKPKCol.GetFKNameVec();
  const std::vector<String>& iPKNameVec = iFKPKCol.GetPKNameVec();
  // Create table and cache it
  TablePage* pPage = new TablePage(iSchema);
  Table* pTable = new Table(pPage);
  _iEntityMap[sTableName] = pTable;
  _iEntityPageIDMap[sTableName] = pPage->GetPageID();

  // create shadowpage
  // create a shadow table
#ifndef NO_FOREIGN_KEY
  //TODO: check refered key not null
  std::set<std::pair<String, String> > pairSet;
  for(auto& ufk: iFKVec)
    for(auto& fk: ufk)
      pairSet.insert(std::make_pair(fk[1], fk[2]));

  for(auto& rkPair: pairSet){
    if(_CheckHaveNull(rkPair.first, rkPair.second)){
      ForeignKeyException e("refered key (" + rkPair.first + ", " + rkPair.second + 
       ") should not have null");
      printf("%s\n", e.what());
      throw e;
    }
  }
#endif //NO_FOREIGN_KEY
  // insert entity to page
  InsertEntity(sTableName);

#ifndef NO_INDEX
  // insert index
  for (int i = 0; i < iSchema.GetSize(); ++i) {
    const Column& column = iSchema.GetColumn(i);
    if(column.GetName() == "") continue;
    if(iFKPKCol.isPK(column.GetName())) CreateIndex(sTableName, column.GetName());
    // CreateIndex(sTableName, column.GetName());
  }
#endif
  //construct fk
  for(int i = 0; i < iFKNameVec.size(); i ++){
    const std::vector<std::vector<String> >& ufk = iFKVec[i];
    const String& sForeignTableName = ufk[0][1];//任意一个单独外键的第二个元素
    std::vector<String> sLocalColName;
    std::vector<String> sForeignColName;
    for(auto& fk: ufk){
      sLocalColName.push_back(fk[0]);
      sForeignColName.push_back(fk[2]);
    }
#ifndef NO_INDEX
  // insert ref key index
  for (auto& fColNmae: sForeignColName)
    CreateIndex(sForeignTableName, fColNmae);
#endif
    GetKeyManager()->AddForeignKey(sTableName, sForeignTableName, sLocalColName,
        sForeignColName, iFKNameVec[i]);
  }
  //construct pk
  for(int i = 0; i < iPKNameVec.size(); i ++){
#ifndef NO_INDEX
  // insert primary key index
  for(auto& colName: iPKVec[i])
    CreateIndex(sTableName, colName);
#endif
    GetKeyManager()->AddPrimaryKey(sTableName, iPKVec[i], iPKNameVec[i]);
  }

  // GetKeyManager()->ShowPK();

  // GetKeyManager()->ShowFK();

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
  auto iResVec = Search(sTableName, pCond, iIndexCond);
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  // check NOT-NULL / PRIMARY-KEY / UNIQUE KEY
  std::vector<String> iColNameVec = GetColumnNames(sTableName);
#ifndef NO_PRIMARY_KEY
  for (int i = 0; i < iTrans.size(); ++i) {
    const String& sColName = iColNameVec[iTrans[i].GetColPos()];
    if (iTrans[i].GetField()->GetType() == FieldType::NULL_TYPE &&
        (!pTable->GetCanBeNull(sColName) 
        || pTable->GetIsPrimary(sColName))){
      auto e = FieldListException("Column should not be NULL");
      std::cout << e.what() << "\n";
      throw e;
    }
  }
#else 
  for (int i = 0; i < iTrans.size(); ++i) {
    const String& sColName = iColNameVec[iTrans[i].GetColPos()];
    if (iTrans[i].GetField()->GetType() == FieldType::NULL_TYPE &&
        (!pTable->GetCanBeNull(sColName) )){
      auto e = FieldListException("Column should not be NULL");
      std::cout << e.what() << "\n";
      throw e;
    }
  }
#endif
#ifndef NO_PRIMARY_KEY
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
      if (iDuplicated.size() != 0 && pTable->GetIsUnique(sColName)) {
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
#endif //NO_PRIMARY_KEY
#ifndef NO_FOREIGN_KEY
  // check fk
  for (int i = 0; i < iTrans.size(); ++i) {
    const String& sColName = iColNameVec[iTrans[i].GetColPos()];
    if (pTable->GetIsForeign(sColName)) {
      std::vector<std::pair<String, String>> fPairVec =
          GetForeignKey(sTableName, sColName);
      for (auto& iPair : fPairVec) {
        const String& fTableName = iPair.first;
        const String& fColName = iPair.second;
        std::vector<PageSlotID> iDuplicated =
            _GetDuplicated(fTableName, fColName, iTrans[i].GetField());
        if (iDuplicated.size() != 0) {
          ForeignKeyException e("Update fail: Foreign key not in range");
          printf("%s\n", e.what());
          throw e;
        }
      }
    }
    if (pTable->GetIsRefered(sColName)) {
      // check refered key 需要确保改变的那个键的没有对应的依赖值
      std::vector<std::pair<String, String>> rPairVec =
          GetForeignKey(sTableName, sColName);
      for (auto& iPair : rPairVec) {
        const String& rTableName = iPair.first;
        const String& rColName = iPair.second;
        MemResult* memRes = new MemResult(pTable->GetColumnNames());
        for (auto& psid : iResVec) {
          memRes->PushBack(pTable->GetRecord(psid.first, psid.second));
        }
        for (int j = 0; j < memRes->GetDataSize(); j++) {
          std::vector<PageSlotID> iDuplicated = _GetDuplicated(
              rTableName, rColName, memRes->GetField(j, iTrans[i].GetColPos()));
          if (iDuplicated.size() != 0) {
            if (memRes) delete memRes;
            ForeignKeyException e(
                "Update fail: A key has a reference dependence");
            printf("%s\n", e.what());
            throw e;
          }
        }
        if (memRes) delete memRes;
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
  Record* pRecord = pTable->EmptyRecord();
  try {
    pRecord->Build(iRawVec);
  } catch (const Exception& e) {
    delete pRecord;
    throw e;
  }

#ifndef NO_INSERT_CHECK;

#ifndef NO_PRIMARY_KEY
  // check null
  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    if (iRawVec[i] == "NULL" &&
        (!pTable->GetCanBeNull(sColName) || 
          GetKeyManager()->IsPrimary(sTableName, sColName))) {
      auto e = FieldListException("Column should not be NULL");
      std::cout << e.what() << "\n";
      throw e;
    }
  }
#else
  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    if (iRawVec[i] == "NULL" &&
        (!pTable->GetCanBeNull(sColName))) {
      auto e = FieldListException("Column should not be NULL");
      std::cout << e.what() << "\n";
      throw e;
    }
  }
#endif //NOPRIMARY_KEY

#ifndef NO_PRIMARY_KEY
  // check primary key
  const std::vector<Key>& uPKVec = GetKeyManager()->GetPrimaryKey(sTableName);
  for(auto& upk: uPKVec){
    std::vector<PageSlotID> duplicatedVec;
    for (int i = 0; i < upk.sLocalColName.size(); i++) {
      const String& sColName = upk.sLocalColName[i];
      // check whether primary key conflicts with other records
      Field* pField = pRecord->GetField(pTable->GetColPos(sColName));
      if (duplicatedVec.size() == 0) {
        duplicatedVec = _GetDuplicated(sTableName, sColName, pField);
      } else {
        duplicatedVec = Intersection(
            _GetDuplicated(sTableName, sColName, pField), duplicatedVec);
      }
      if (duplicatedVec.size() == 0) {
        break;
      } else if (pTable->GetIsUnique(sColName)) {
        auto e = Exception("Unique key existed");
        std::cout << e.what() << "\n";
        throw e;
      }
    }
    if (duplicatedVec.size() != 0) {
      // add exception here
      auto e = Exception("Primary key existed");
      std::cout << e.what() << "\n";
      throw e;
    }
  }
  
#endif //NO_PRIMARY_KEY
#ifndef NO_FOREIGN_KEY
  // check foreignkey
  const std::vector<Key>& uFKVec = GetKeyManager()->GetForeignKey(sTableName);
  for(auto& ufk: uFKVec){
    std::vector<PageSlotID> iDuplicated;
    for (int i = 0; i < ufk.sLocalColName.size(); i++) {
      const String& lColName = ufk.sLocalColName[i];
      const String& fTableName = ufk.sForeignTableName;
      const String& fColName = ufk.sForeignColName[i];
      // check whether primary key conflicts with other records
      Field* pField = pRecord->GetField(pTable->GetColPos(lColName));
      // printf("FK of %s: %s %s\n", sColName.data(), fPair.first.data(),
      if(iDuplicated.size() == 0){
        iDuplicated = _GetDuplicated(fTableName, fColName, pField);
      }else{
        iDuplicated = Intersection(iDuplicated,  _GetDuplicated(fTableName, fColName, pField));
      }
      if(iDuplicated.size() == 0){
        break;
      }
    }
    if(iDuplicated.size() == 0){
      ForeignKeyException e("fk insert fail: not in refered key");
      printf("%s\n", e.what());
      throw e;
    }
  }
  
#endif //NO_FOREIGN_KEY
#endif //NO_INSERT_CHECK

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
  Record* pRecord = pTable->EmptyRecord();
  try {
    pRecord->Build(iValueVec);
  } catch (const Exception& e) {
    delete pRecord;
    throw e;
  }
#ifndef NO_INSERT_CHECK;
#ifndef NO_PRIMARY_KEY
  // check primary key
  const std::vector<Key>& uPKVec = GetKeyManager()->GetPrimaryKey(sTableName);
  for(auto& upk: uPKVec){
    std::vector<PageSlotID> duplicatedVec;
    for (int i = 0; i < upk.sLocalColName.size(); i++) {
      const String& sColName = upk.sLocalColName[i];
      // check whether primary key conflicts with other records
      Field* pField = pRecord->GetField(pTable->GetColPos(sColName));
      if (duplicatedVec.size() == 0) {
        duplicatedVec = _GetDuplicated(sTableName, sColName, pField);
      } else {
        duplicatedVec = Intersection(
            _GetDuplicated(sTableName, sColName, pField), duplicatedVec);
      }
      if (duplicatedVec.size() == 0) {
        break;
      } else if (pTable->GetIsUnique(sColName)) {
        auto e = Exception("Unique key existed");
        std::cout << e.what() << "\n";
        throw e;
      }
    }
    if (duplicatedVec.size() != 0) {
      // add exception here
      auto e = Exception("Primary key existed");
      std::cout << e.what() << "\n";
      throw e;
    }
  }
  
#endif //NO_PRIMARY_KEY
#ifndef NO_FOREIGN_KEY
  // check foreignkey
  const std::vector<Key>& uFKVec = GetKeyManager()->GetForeignKey(sTableName);
  for(auto& ufk: uFKVec){
    std::vector<PageSlotID> iDuplicated;
    for (int i = 0; i < ufk.sLocalColName.size(); i++) {
      const String& lColName = ufk.sLocalColName[i];
      const String& fTableName = ufk.sForeignTableName;
      const String& fColName = ufk.sForeignColName[i];
      // check whether primary key conflicts with other records
      Field* pField = pRecord->GetField(pTable->GetColPos(lColName));
      // printf("FK of %s: %s %s\n", sColName.data(), fPair.first.data(),
      if(iDuplicated.size() == 0){
        iDuplicated = _GetDuplicated(fTableName, fColName, pField);
      }else{
        iDuplicated = Intersection(iDuplicated,  _GetDuplicated(fTableName, fColName, pField));
      }
      if(iDuplicated.size() == 0){
        break;
      }
    }
    if(iDuplicated.size() == 0){
      ForeignKeyException e("fk insert fail: not in refered key");
      printf("%s\n", e.what());
      throw e;
    }
  }
  
#endif //NO_PRIMARY_KEY
#ifndef NO_FOREIGN_KEY
  // check foreignkey
  const std::vector<Key>& uFKVec = GetKeyManager()->GetForeignKey(sTableName);
  bool ForeignKeyCheck = false;
  for(auto& ufk: uFKVec){
    std::vector<PageSlotID> iDuplicated;
    for (int i = 0; i < ufk.sLocalColName.size(); i++) {
      const String& lColName = ufk.sLocalColName[i];
      const String& fTableName = ufk.sForeignTableName;
      const String& fColName = ufk.sForeignColName[i];
      ForeignKeyCheck = true;
      // check whether primary key conflicts with other records
      Field* pField = pRecord->GetField(pTable->GetColPos(ufk.sLocalColName[i]));
      // printf("FK of %s: %s %s\n", sColName.data(), fPair.first.data(),
      // fPair.second.data());
      std::vector<PageSlotID> tmpDuplicated;
      if(iDuplicated.size() == 0){
        iDuplicated = _GetDuplicated(fTableName, fColName, pField);
      }else{
        iDuplicated = Intersection(iDuplicated,  _GetDuplicated(fTableName, fColName, pField));
      }
      if(iDuplicated.size() == 0){
        break;
      }
    }
    if(iDuplicated.size() == 0){
      ForeignKeyException e("fk insert fail: not in refered key");
      printf("%s\n", e.what());
      throw e;
    }
  }
#endif //NO_PRIMARY_KEY
#ifndef NO_FOREIGN_KEY
  // check foreignkey
  for (int i = 0; i < iColNameVec.size(); i++) {
    const String& sColName = iColNameVec[i];
    if (pTable->GetIsForeign(sColName)) {
      // check whether primary key conflicts with other records
      Field* pField = pRecord->GetField(i);
      std::vector<std::pair<String, String>> fPairVec =
          GetForeignKey(sTableName, sColName);
      // printf("FK of %s: %s %s\n", sColName.data(), fPair.first.data(),
      // fPair.second.data());
      for (auto& fPair : fPairVec) {
        // printf("%s %s\n", fPair.first.data(), fPair.second.data());
        if (!_CheckForeignKey(fPair.first, fPair.second, pField)) {
          printf("key out of range:%s\n", pField->ToString().data());
          ForeignKeyException e("key out of range:" + pField->ToString());
          throw e;
        }
      }
    }
  }
#endif //NO_FOREIGN_KEY
#endif //NO_INSERT_CHECK

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
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  FieldType iType = pTable->GetType(sColName);
  Size nSize = pTable->GetSize(sColName);
  FieldID nPos = pTable->GetColPos(sColName);
  _pIndexManager->AddIndex(sTableName, sColName, iType, nSize);
  Index* pIndex = _pIndexManager->GetIndex(sTableName, sColName);
  // Handle Exists Data
  auto iAll = Search(sTableName, nullptr, {});
  for (const auto& iPair : iAll) {
    Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
    Field* pKey = pRecord->GetField(nPos);
    pIndex->Insert(pKey, iPair);
    delete pRecord;
  }
}

void Database::DropIndex(const String& sTableName, const String& sColName) {
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
                     const std::vector<String> sColName,
                     const String& sConstraintName) {
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
  if (needCheckDuplication) {
    int errorTimes = 0;
    for (auto& colName : sColNameVec) {
      if (_CheckDuplicate(sTableName, colName)) {
        errorTimes++;
      }
    }
    if (errorTimes == sColName.size()) {
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

  if (!fTable->GetCanBeNull(fColName) || 
    GetKeyManager()->IsPrimary(fTableName, fColName)) {
    return false;
  }
  // printf("into\n");
  FieldID colPos = fTable->GetColPos(fColName);
  Field* pLow = new NullField();
  Field* pHigh = pLow->Clone();
  pHigh->Add();
  Condition* pCond = nullptr;
  pCond = new RangeCondition(colPos, pLow, pHigh);
  std::vector<PageSlotID> iPageSlotIDVec = Search(fTableName, pCond, {});
  return (iPageSlotIDVec.size() != 0);
}

bool Database::_CheckDuplicate(const String& sTableName,
                               const String& sColName) {
  Table* fTable = GetTable(sTableName);
  std::vector<PageSlotID> fpsidVec = fTable->SearchRecord(nullptr);
  MemResult* result = new MemResult(fTable->GetColumnNames());
  for (auto& psid : fpsidVec)
    result->PushBack(fTable->GetRecord(psid.first, psid.second));
  FieldID colPos = fTable->GetColPos(sColName);
  std::set<String> pSet;
  for (int i = 0; i < result->GetDataSize(); i++) {
    // TODO: 这么写可能会重复遍历
    if (pSet.count(result->GetFieldString(i, colPos)) != 0) {
      if (result) delete result;
      return true;
    }
    pSet.insert(result->GetFieldString(i, colPos));
  }
  if (result) delete result;
  return false;
}

std::vector<std::pair<String, String>> Database::GetReferedKey(
    const String& sTableName, const String& sColName) {
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
std::vector<std::pair<String, String>> Database::GetForeignKey(
    const String& sTableName, const String& sColName) {
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
    //   res->GetFieldString(i, 1).data());
    if (res->GetFieldString(i, 0) != SHADOW_STATUS_FOREIGN_KEY ||
        res->GetFieldString(i, 1) != sColName)
      continue;
    retVec.push_back(
        std::make_pair(res->GetFieldString(i, 2), res->GetFieldString(i, 3)));
  }
  // if (retVec.size() == 0) {
  //   printf("there should be a foreign key in shadow table\n");
  //   throw ForeignKeyException();
  // }
  return retVec;
}

std::vector<std::vector<String>> Database::GetTableReferedKeys(
    const String& sTableName) {  //
  Table* pTable = GetTable("@" + sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  std::vector<std::vector<String>> referedKeyVec;
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
    if (res->GetFieldString(i, 0) != SHADOW_STATUS_REFERED_KEY) continue;
    referedKeyVec.push_back(std::vector<String>());
    referedKeyVec.back().push_back(res->GetFieldString(i, 1));
    referedKeyVec.back().push_back(res->GetFieldString(i, 2));
    referedKeyVec.back().push_back(res->GetFieldString(i, 3));
  }
  return referedKeyVec;
}
std::vector<std::vector<String>> Database::GetTableForeignKeys(
    const String& sTableName) {  //
  Table* pTable = GetTable("@" + sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  std::vector<std::vector<String>> foreignKeyVec;
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
    if (res->GetFieldString(i, 0) != SHADOW_STATUS_FOREIGN_KEY) continue;
    foreignKeyVec.push_back(std::vector<String>());
    foreignKeyVec.back().push_back(res->GetFieldString(i, 1));
    foreignKeyVec.back().push_back(res->GetFieldString(i, 2));
    foreignKeyVec.back().push_back(res->GetFieldString(i, 3));
  }
  return foreignKeyVec;
}

bool Database::_CheckForeignKey(const String& fTableName,
                                const String& fColName,
                                Field* pField) {  // false-wrong true-corrct
  // printf("%s %s on %s\n", fTableName.data(), fColName.data(),
  // pField->ToString().data());
  if (pField->ToString() == "NULL") {  //外键可为null
    return true;
  }

  return (_GetDuplicated(fTableName, fColName, pField).size() != 0);
}


void Database::AddForeignKey(const String& lTableName, const std::vector<String>& lColName,
                     const String& fTableName, const std::vector<String>& fColNameVec,
                     const String& sConstraintName) {
  // TODO: ADD FOREIGNKEY
  // Table* lTable = GetTable(lTableName);
  // Table* fTable = GetTable(fTableName);
  // if (lTable == nullptr) {
  //   auto e = TableNotExistException(lTableName);
  //   std::cout << e.what() << "\n";
  //   throw e;
  // }
  // if (fTable == nullptr) {
  //   auto e = TableNotExistException(fTableName);
  //   std::cout << e.what() << "\n";
  //   throw e;
  // }
  // // check fk validation
  // for (auto& fColName : fColNameVec) {
  //   std::vector<PageSlotID> psidVec = lTable->SearchRecord(nullptr);
  //   MemResult* lRes = new MemResult(lTable->GetColumnNames());
  //   for (auto& psid : psidVec)
  //     lRes->PushBack(lTable->GetRecord(psid.first, psid.second));
  //   FieldID colPos = lTable->GetColPos(lColName);
  //   for (int i = 0; i < lRes->GetDataSize(); i++) {
  //     if (!_CheckForeignKey(fTableName, fColName, lRes->GetField(i, colPos))) {
  //       if (lRes) delete lRes;
  //       printf("Foreign key should be in range of refernce key\n");
  //       throw ForeignKeyException(
  //           "Foreign key should be in range of refernce key");
  //     }
  //   }
  //   if (lRes) delete lRes;
  //   // check type
  //   if (lTable->GetType(lColName) != fTable->GetType(fColName)) {
  //     printf("foreign key should have same type\n");
  //     throw ForeignKeyException("foreign key should have same type");
  //   }
  //   // check reference not null
  //   if (_CheckHaveNull(fTableName, fColName)) {
  //     printf("reference key cannot be null\n");
  //     throw ForeignKeyException("reference key cannot be null");
  //   }

  //   // add this table foreign key
  //   std::vector<Field*> LocalVec;
  //   LocalVec.push_back(new CharField(SHADOW_STATUS_FOREIGN_KEY));
  //   LocalVec.push_back(new CharField(lColName));
  //   LocalVec.push_back(new CharField(fTableName));
  //   LocalVec.push_back(new CharField(fColName));
  //   Insert("@" + lTableName, LocalVec);
  //   // insert reference shadow table
  //   std::vector<Field*> ForeignVec;
  //   ForeignVec.push_back(new CharField(SHADOW_STATUS_REFERED_KEY));
  //   ForeignVec.push_back(new CharField(fColName));
  //   ForeignVec.push_back(new CharField(lTableName));
  //   ForeignVec.push_back(new CharField(lColName));
  //   // printf("2\n");
  //   Insert("@" + fTableName, ForeignVec);
  //   lTable->SetForeignKey(lColName);
  //   _UpdateReferedKey(fTableName, fColName);
  // }
}
void Database::DropForeignKey(const String& sTableName,
                              const String& sColName) {

}
void Database::DropTableForeignKey(const String& sTableName) {
  // std::vector<std::vector<String>> refPairVec = GetTableReferedKeys(sTableName);
  // std::vector<std::vector<String>> forPairVec = GetTableForeignKeys(sTableName);

  // std::map<String, int> tmpMap;
  // for (auto& tVec : refPairVec) {
  //   _DropShadowTableKey(tVec[1], SHADOW_STATUS_REFERED_KEY, tVec[2], sTableName,
  //                       tVec[0]);
  //   _UpdateReferedKey(tVec[1], tVec[2]);
  // }

  // for (auto& tVec : forPairVec) {
  //   _DropShadowTableKey(tVec[1], SHADOW_STATUS_FOREIGN_KEY, tVec[2], sTableName,
  //                       tVec[0]);
  //   _UpdateReferedKey(tVec[1], tVec[2]);
  // }
}

void Database::DropUniqueKey(const String& sTableName, const String& sColName) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  pTable->DropUniqueKey(sColName);
}

void Database::_UpdateReferedKey(const String& fTableName,
                                 const String& fColname) {
  Table* fTable = GetTable("@" + fTableName);
  Table* sTable = GetTable(fTableName);
  if (fTable == nullptr) {
    auto e = TableNotExistException("@" + fTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  if (sTable == nullptr) {
    auto e = TableNotExistException(fTableName);
    std::cout << e.what() << "\n";
    throw e;
  }

  // printf("into\n");
  std::vector<String> colNames = sTable->GetColumnNames();
  std::map<String, bool> sMap;
  for (auto& col : colNames) {
    sMap[col] = false;
  }
  std::vector<PageSlotID> fpsidVec = fTable->SearchRecord(nullptr);
  MemResult* result = new MemResult(fTable->GetColumnNames());
  for (auto& psid : fpsidVec)
    result->PushBack(fTable->GetRecord(psid.first, psid.second));
  for (int j = 0; j < result->GetDataSize(); j++) {
    if (result->GetFieldString(j, 0) != SHADOW_STATUS_REFERED_KEY) continue;
    sMap[result->GetFieldString(j, 1)] = true;
  }
  for (auto& iPair : sMap) {
    if (iPair.second) {
      sTable->AddReferedKey(iPair.first);
    } else {
      sTable->DropReferedKey(iPair.first);
    }
  }

  if (result) delete result;
}

void Database::AddUniqueKey(const String& sTableName, const String& sColName) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) {
    auto e = TableNotExistException(sTableName);
    std::cout << e.what() << "\n";
    throw e;
  }
  if (_CheckDuplicate(sTableName, sColName)) {
    throw AlterException("the new Unique Key column cannot be duplicated");
  }
  pTable->AddUniqueKey(sColName);

  if (!IsIndex(sTableName, sColName)) CreateIndex(sTableName, sColName);
}

}  // namespace dbtrain_mysql