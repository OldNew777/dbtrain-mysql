#include "manager/index_manager.h"

#include <algorithm>

#include "assert.h"
#include "exception/index_exception.h"
#include "macros.h"
#include "os/os.h"
#include "page/record_page.h"
#include "record/fixed_record.h"
#include "settings.h"

namespace dbtrain_mysql {

String GetIndexName(const String &sTableName, const String &sColName) {
  return sTableName + " " + sColName;
}

std::pair<String, String> SplitIndexName(const String &sName) {
  auto nPos = sName.find(' ');
  assert(nPos != String::npos);
  return {sName.substr(0, nPos), sName.substr(nPos + 1)};
}

IndexManager::IndexManager() {
  _nPageID = NULL_PAGE;
  Load();
  Init();
}

IndexManager::IndexManager(PageID nPageID) {
  _nPageID = nPageID;
  Load();
  Init();
}

IndexManager::~IndexManager() {
  Store();
  for (const auto &iPair : _iIndexMap)
    if (iPair.second) {
      delete iPair.second;
    }
}

PageID IndexManager::GetPageID() const { return _nPageID; }

Index *IndexManager::GetIndex(const String &sTableName,
                              const String &sColName) {
  String sIndexName = GetIndexName(sTableName, sColName);
  if (_iIndexMap.find(sIndexName) == _iIndexMap.end()) {
    if (_iIndexIDMap.find(sIndexName) == _iIndexIDMap.end())
      return nullptr;
    else {
      _iIndexMap[sIndexName] = new Index(_iIndexIDMap[sIndexName]);
      return _iIndexMap[sIndexName];
    }
  }
  return _iIndexMap[sIndexName];
}

Index *IndexManager::AddIndex(const String &sTableName, const String &sColName,
                              FieldType iType, Size nSize) {
  if (IsIndex(sTableName, sColName)) {
    auto e = IndexException("Index not exist");
    std::cout << e.what() << "\n";
    throw e;
  }
  String sIndexName = GetIndexName(sTableName, sColName);
  Index *pIndex = new Index(iType, nSize);
  PageID nRoot = pIndex->GetRootID();
  delete pIndex;
  pIndex = new Index(nRoot);
  _iIndexIDMap[sIndexName] = nRoot;
  _iIndexMap[sIndexName] = pIndex;
  if (_iTableIndexes.find(sTableName) == _iTableIndexes.end()) {
    _iTableIndexes[sTableName] = std::vector<String>{sColName};
  } else {
    _iTableIndexes[sTableName].push_back(sColName);
  }
  return pIndex;
}

void IndexManager::DropIndex(const String &sTableName, const String &sColName) {
  if (!IsIndex(sTableName, sColName)) {
    auto e = IndexException("Index not exist");
    std::cout << e.what() << "\n";
    throw e;
  }
  String sIndexName = GetIndexName(sTableName, sColName);
  Index *pIndex = GetIndex(sTableName, sColName);
  pIndex->Clear();
  delete pIndex;
  _iIndexIDMap.erase(sIndexName);
  _iIndexMap.erase(sIndexName);
  assert(_iTableIndexes.find(sTableName) != _iTableIndexes.end());
  _iTableIndexes[sTableName].erase(std::find(_iTableIndexes[sTableName].begin(),
                                             _iTableIndexes[sTableName].end(),
                                             sColName));
  if (_iTableIndexes[sTableName].size() == 0) _iTableIndexes.erase(sTableName);
}

void IndexManager::DropIndex(const String &sTableName) {
  if (!HasIndex(sTableName)) return;
  for (const auto &sColName : GetTableIndexes(sTableName)) {
    String sIndexName = GetIndexName(sTableName, sColName);
    Index *pIndex = GetIndex(sTableName, sColName);
    pIndex->Clear();
    delete pIndex;
    _iIndexIDMap.erase(sIndexName);
    _iIndexMap.erase(sIndexName);
  }
  assert(_iTableIndexes.find(sTableName) != _iTableIndexes.end());
  if (_iTableIndexes[sTableName].size() == 0) _iTableIndexes.erase(sTableName);
}

std::vector<String> IndexManager::GetTableIndexes(
    const String &sTableName) const {
  if (_iTableIndexes.find(sTableName) == _iTableIndexes.end()) return {};
  return _iTableIndexes.find(sTableName)->second;
}

bool IndexManager::IsIndex(const String &sTableName, const String &sColName) {
  String sIndexName = GetIndexName(sTableName, sColName);
  return _iIndexIDMap.find(sIndexName) != _iIndexIDMap.end();
}

bool IndexManager::HasIndex(const String &sTableName) const {
  if (_iTableIndexes.find(sTableName) == _iTableIndexes.end()) return false;
  return _iTableIndexes.find(sTableName)->second.size() > 0;
}

void IndexManager::Store() {
  if (_bCleared) return;

  // Update Index Root
  for (const auto &iPair : _iIndexMap)
    _iIndexIDMap[iPair.first] = iPair.second->GetRootID();
  RecordPage *pPage = new RecordPage(_nPageID);
  PageID nNowPageID = _nPageID;
  auto iter = _iIndexIDMap.begin();
  FixedRecord *pRecord = new FixedRecord(
      2, {FieldType::CHAR_TYPE, FieldType::INT_TYPE}, {INDEX_NAME_SIZE, 4});
  while (iter != _iIndexIDMap.end()) {
    pPage->Clear();
    for (int i = 0; i < pPage->GetCap(), iter != _iIndexIDMap.end(); ++i) {
      const auto &iPair = *iter;
      CharField *pString = new CharField(iPair.first);
      IntField *pInt = new IntField(iPair.second);
      pRecord->SetField(0, pString);
      pRecord->SetField(1, pInt);
      uint8_t pData[INDEX_NAME_SIZE + 4 + 1];
      pRecord->Store(pData);
      pPage->InsertRecord(pData);
      ++iter;
    }
    if (iter == _iIndexIDMap.end()) break;
    nNowPageID = pPage->GetNextID();
    if (nNowPageID == NULL_PAGE) {
      RecordPage *pNewPage = new RecordPage(INDEX_NAME_SIZE + 4 + 1, true);
      pPage->PushBack(pNewPage);
      delete pPage;
      pPage = pNewPage;
      nNowPageID = pPage->GetPageID();
    } else {
      delete pPage;
      pPage = new RecordPage(nNowPageID);
    }
  }
  while (pPage->GetNextID() != NULL_PAGE) {
    pPage->PopBack();
  }
  delete pRecord;
  delete pPage;
}

void IndexManager::Load() {
  RecordPage *pPage;
  if (_nPageID == NULL_PAGE) {
    pPage = new RecordPage(INDEX_NAME_SIZE + 4 + 1, true);
    _nPageID = pPage->GetPageID();
  } else {
    pPage = new RecordPage(_nPageID);
  }
  PageID nNowPageID = _nPageID;
  FixedRecord *pRecord = new FixedRecord(
      2, {FieldType::CHAR_TYPE, FieldType::INT_TYPE}, {INDEX_NAME_SIZE, 4});
  while (true) {
    for (Size i = 0, num = 0; i < pPage->GetCap() && num < pPage->GetUsed();
         ++i) {
      if (!pPage->HasRecord(i)) continue;
      ++num;
      uint8_t *pData = pPage->GetRecord(i);
      pRecord->Load(pData);
      CharField *pString = dynamic_cast<CharField *>(pRecord->GetField(0));
      IntField *pInt = dynamic_cast<IntField *>(pRecord->GetField(1));
      _iIndexIDMap[pString->GetString()] = pInt->GetIntData();
      delete[] pData;
    }
    nNowPageID = pPage->GetNextID();
    if (nNowPageID == NULL_PAGE) break;
    delete pPage;
    pPage = new RecordPage(nNowPageID);
  }
  delete pRecord;
  delete pPage;
}

void IndexManager::Init() {
  for (const auto &it : _iIndexIDMap) {
    auto iPair = SplitIndexName(it.first);
    if (_iTableIndexes.find(iPair.first) == _iTableIndexes.end()) {
      _iTableIndexes[iPair.first] = std::vector<String>{iPair.second};
    } else {
      _iTableIndexes[iPair.first].push_back(iPair.second);
    }
  }
}

void IndexManager::Clear() {
  _bCleared = true;
  LinkedPage pLinkedPage(_nPageID);
  pLinkedPage.ReleaseListAll();
}

std::vector<std::pair<String, String>> IndexManager::GetIndexInfos() const {
  std::vector<std::pair<String, String>> iInfos{};
  for (const auto &it : _iIndexIDMap)
    iInfos.push_back(SplitIndexName(it.first));
  return iInfos;
}

}  // namespace dbtrain_mysql
