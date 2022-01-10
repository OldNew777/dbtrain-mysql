#include "key_manager.h"

#include <algorithm>

#include "assert.h"
#include "exception/exceptions.h"
#include "macros.h"
#include "os/os.h"
#include "page/record_page.h"
#include "record/fixed_record.h"
#include "settings.h"

namespace dbtrain_mysql {

const PageOffset DEFAULT_KEY_INDEX_OFFSET = 20;

KeyManager::KeyManager() { 
  _nPageID = NULL_PAGE;
  Load(); 
  Init();
}

KeyManager::KeyManager(PageID nPageID) {
  _nPageID = nPageID;
  Load();
  Init();
}

KeyManager::~KeyManager() { 
  Store(); 
}

PageID KeyManager::GetPageID() const { return _nPageID; }

void KeyManager::Clear() {
  _bCleared = true;
  LinkedPage pLinkedPage(_nPageID);
  pLinkedPage.ReleaseListAll();
}
void KeyManager::Init(){
  for(auto& tKeyPair: _iKeyMap){
    if(tKeyPair.second.iType == KeyType::PRIMARY_KEY_TYPE){
      if(_iTablePKMap.find(tKeyPair.second.sLocalTableName) == _iTablePKMap.end()){
        _iTablePKMap[tKeyPair.second.sLocalTableName] = {};
      }
      _iTablePKMap[tKeyPair.second.sLocalTableName].push_back(tKeyPair.second);
    }
    else{
      if(_iTableFKMap.find(tKeyPair.second.sLocalTableName) == _iTableFKMap.end()){
        _iTableFKMap[tKeyPair.second.sLocalTableName] = {};
      }
      _iTableFKMap[tKeyPair.second.sLocalTableName].push_back(tKeyPair.second);
    }
    
  }
}

void KeyManager::Store() {
  if (_bCleared) return;
  FixedRecord *pRecord = new FixedRecord(
      5,
      {FieldType::CHAR_TYPE, FieldType::CHAR_TYPE, FieldType::CHAR_TYPE,
       FieldType::CHAR_TYPE, FieldType::CHAR_TYPE},
      {CONSTRAINT_NAME_SIZE, TABLE_NAME_SIZE, COLUMN_NAME_SIZE, TABLE_NAME_SIZE,
       COLUMN_NAME_SIZE});
  RecordPage *pPage = new RecordPage(_nPageID);
  PageID nNowPageID = _nPageID;

  // header
  pPage->SetHeader((uint8_t *)&_iDefaultKeyIndex, 4, DEFAULT_KEY_INDEX_OFFSET);

  // data
  auto iter = _iKeyMap.begin();
  int index = 0;
  int i = 0;
  while (iter != _iKeyMap.end()) {
    pPage->Clear();
    CharField *pConstraintName, *pLocalTableName, *pForeignTableName,
        *pLocalColName, *pForeignColName;
    for (int i = 0; i < pPage->GetCap(), iter != _iKeyMap.end(); ++i) {
      const auto &key = iter->second;
      pConstraintName = new CharField(iter->first);
      pLocalTableName = new CharField(iter->second.sLocalTableName);
      pLocalColName = new CharField(iter->second.sLocalColName[index]);
      if (key.iType == KeyType::FOREIGN_KEY_TYPE) {
        pForeignTableName = new CharField(iter->second.sForeignTableName);
        pForeignColName = new CharField(iter->second.sForeignColName[index]);
      } else if (key.iType == KeyType::PRIMARY_KEY_TYPE) {
        pForeignTableName = new CharField();
        pForeignColName = new CharField();
      } else {

        delete pPage;
        delete pRecord;
        delete pConstraintName;
        delete pLocalTableName;
        delete pLocalColName;
        throw Exception("Constraint type error");
      }

      pRecord->SetField(0, pConstraintName);
      pRecord->SetField(1, pLocalTableName);
      pRecord->SetField(2, pLocalColName);
      pRecord->SetField(3, pForeignTableName);
      pRecord->SetField(4, pForeignColName);
      uint8_t pData[CONSTRAINT_NAME_SIZE +
                    2 * (TABLE_NAME_SIZE + COLUMN_NAME_SIZE) + 1];
      pRecord->Store(pData);
      pPage->InsertRecord(pData);
      if (++index >= iter->second.sLocalColName.size()) {
        ++iter;
        index = 0;
      }
    }

    // insert new page
    if (iter == _iKeyMap.end()) break;
    nNowPageID = pPage->GetNextID();
    if (nNowPageID == NULL_PAGE) {
      RecordPage *pNewPage = new RecordPage(
          CONSTRAINT_NAME_SIZE + 2 * (TABLE_NAME_SIZE + COLUMN_NAME_SIZE) + 1,
          true);
      pPage->PushBack(pNewPage);
      delete pPage;
      pPage = pNewPage;
      nNowPageID = pPage->GetPageID();
    } else {
      delete pPage;
      pPage = new RecordPage(nNowPageID);
    }
  }

  // delete empty page
  while (pPage->GetNextID() != NULL_PAGE) {
    pPage->PopBack();
  }

  delete pPage;
  delete pRecord;
}

void KeyManager::Load() {
  FixedRecord *pRecord = new FixedRecord(
      5,
      {FieldType::CHAR_TYPE, FieldType::CHAR_TYPE, FieldType::CHAR_TYPE,
       FieldType::CHAR_TYPE, FieldType::CHAR_TYPE},
      {CONSTRAINT_NAME_SIZE, TABLE_NAME_SIZE, COLUMN_NAME_SIZE, TABLE_NAME_SIZE,
       COLUMN_NAME_SIZE});

  RecordPage *pPage;
  if (_nPageID == NULL_PAGE) {
    pPage = new RecordPage(
        CONSTRAINT_NAME_SIZE + 2 * (TABLE_NAME_SIZE + COLUMN_NAME_SIZE) + 1,
        true);
    _nPageID = pPage->GetPageID();
    _iDefaultKeyIndex = 0;
  } else {
    pPage = new RecordPage(_nPageID);
    // header
    pPage->GetHeader((uint8_t *)&_iDefaultKeyIndex, 4,
                     DEFAULT_KEY_INDEX_OFFSET);
  }
  PageID nNowPageID = _nPageID;

  // data
  while (true) {
    for (Size i = 0, num = 0; i < pPage->GetCap() && num < pPage->GetUsed();
         ++i) {
      if (!pPage->HasRecord(i)) continue;
      ++num;
      uint8_t *pData = pPage->GetRecord(i);
      pRecord->Load(pData);
      String sConstraintName = pRecord->GetField(0)->ToString();
      String sLocalTableName = pRecord->GetField(1)->ToString();
      String sLocalColName = pRecord->GetField(2)->ToString();
      Key &key = _iKeyMap[sConstraintName];
      key.sLocalTableName = sLocalTableName;
      key.sLocalColName.push_back(sLocalColName);
      if (sConstraintName.substr(0, 7) == "PRIMARY") {
        key.iType = KeyType::PRIMARY_KEY_TYPE;
      } else if (sConstraintName.substr(0, 7) == "FOREIGN") {
        key.iType = KeyType::FOREIGN_KEY_TYPE;
        String sForeignTableName = pRecord->GetField(3)->ToString();
        String sForeignColName = pRecord->GetField(4)->ToString();
        key.sForeignTableName = sForeignTableName;
        key.sForeignColName.push_back(sForeignColName);
      } else {
        delete[] pData;
        delete pPage;
        delete pRecord;
        throw Exception("Constraint type error");
      }
      delete[] pData;
    }
    nNowPageID = pPage->GetNextID();
    if (nNowPageID == NULL_PAGE) break;
    delete pPage;
    pPage = new RecordPage(nNowPageID);
  }

  delete pPage;
  delete pRecord;
}

String KeyManager::_GetDefaultKeyIndex(){
  return std::to_string(_iDefaultKeyIndex++);
}
void KeyManager::AddPrimaryKey(const String& sLocalTableName,
                     const std::vector<String>& sLocalColName,
                     const String& sConstraintName){
  String cName = sConstraintName;
  if(sConstraintName == ""){
    cName = "PRIMARY" + _GetDefaultKeyIndex();
  }
  if(_iKeyMap.find(cName) != _iKeyMap.end()){
    Exception e("name duplicated: " + cName);
    printf("%s\n", e.what());
    throw e;
  }
  Key key;
  key.iType = KeyType::PRIMARY_KEY_TYPE;
  key.sLocalColName = sLocalColName;
  key.sLocalTableName = sLocalTableName;
  //add key map
  _iKeyMap[cName] = key;
  //add table map
  if(_iTablePKMap.find(sLocalTableName) == _iTablePKMap.end()){
    _iTablePKMap[sLocalTableName] = {};
  }
  _iTablePKMap[sLocalTableName].push_back(key);
}

void KeyManager::DropPrimaryKey(const String& sLocalTableName,
                      const std::vector<String>& sLocalColName){
  std::set<String> tmpSet;
  for(auto& str: sLocalColName){
    tmpSet.insert(str);
  }
  auto it = _iKeyMap.begin();
  Key tmpKey;
  while(it != _iKeyMap.end()){
    if(tmpSet.size() == it->second.sLocalColName.size()){
      bool flag = true;
      for(auto& colName : it->second.sLocalColName){
        if (tmpSet.find(colName) == tmpSet.end()){
          flag = false;
          break;
        }
      }
      if(flag){ //delete
        tmpKey = it->second;
        it = _iKeyMap.erase(it);
        break;
      } 
    }
    else{
      it ++;
    }
  }
  if(tmpKey.sLocalColName.size() == 0){
    Exception e("drop pk fail: no such key");
    printf("%s\n", e.what());
    throw e;
  }
  Init();//傻逼写法 能跑就行
}
void KeyManager::AddForeignKey(const String& sLocalTableName,
                     const String& sForeignTableName,
                     const std::vector<String>& sLocalColName,
                     const std::vector<String>& sForeignColName,
                     const String& sConstraintName){
  String cName = sConstraintName;
  if(sConstraintName == ""){
    cName = "FOREIGN" + _GetDefaultKeyIndex();
  }
  if(_iKeyMap.find(cName) != _iKeyMap.end()){
    Exception e("name duplicated: " + cName);
    printf("%s\n", e.what());
    throw e;
  }
  Key key;
  key.iType = KeyType::PRIMARY_KEY_TYPE;
  key.sLocalColName = sLocalColName;
  key.sLocalTableName = sLocalTableName;
  key.sForeignTableName = sForeignTableName;
  key.sForeignColName = sForeignColName;
  //add key map
  _iKeyMap[cName] = key;
  //add table map
  if(_iTableFKMap.find(sLocalTableName) == _iTableFKMap.end()){
    _iTableFKMap[sLocalTableName] = {};
  }
  _iTableFKMap[sLocalTableName].push_back(key);
}

void KeyManager::DropForeignKey(const String& sLocalTableName,
                      const String& sConstraintName){
  if(_iKeyMap.find(sConstraintName) == _iKeyMap.end()){
    Exception e("drop fk fail: no such key" + sConstraintName);
    printf("%s\n", e.what());
    throw e;
  }
  Key tmpkey = _iKeyMap[sConstraintName];
  _iKeyMap.erase(sConstraintName);
  Init();//傻逼写法，能跑就行
}
std::vector<Key> KeyManager::GetForeignKey(const String& sLocalTableName) {
  return _iTableFKMap[sLocalTableName];
}
std::vector<Key> KeyManager::GetPrimaryKey(const String& sLocalTableName) {
  return _iTablePKMap[sLocalTableName];
}
bool KeyManager::IsPrimary(const String& sTableName, const String& sColName){
  for(auto& pk: _iTablePKMap[sTableName]){
    for(auto& colName: pk.sLocalColName){
      if (colName == sColName){
        return true;
      }
    }
  }
  false;
}
void KeyManager::ShowPK(){
  printf("ShowPK:\n");
  for(auto& sPair: _iTablePKMap){
    printf("\n%s\n{\n", sPair.first.data());
    for(auto& pk: sPair.second){
      printf("\t{ ");
      for(auto& colName: pk.sLocalColName)
        printf("%s ", colName.data());
      printf(" }\n");
    }
    printf("}\n");
  }
}
}  // namespace dbtrain_mysql