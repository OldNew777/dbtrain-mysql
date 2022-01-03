#include "system/instance.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>

#include "condition/conditions.h"
#include "exception/exceptions.h"
#include "macros.h"
#include "os/os.h"
#include "record/fixed_record.h"
#include "settings.h"
#include "utils/basic_function.h"

namespace dbtrain_mysql {

Instance::Instance() { _pDataManager = new DataManager(); }

Instance::~Instance() {
  delete _pDataManager;
  OS::WriteBack();
}

void Instance::UseDatabase(const String& sDatabaseName) {
  _pDataManager->UseDatabase(sDatabaseName);
}

void Instance::CreateDatabase(const String& sDatabaseName) {
  _pDataManager->CreateDatabase(sDatabaseName);
}

void Instance::DropDatabase(const String& sDatabaseName) {
  _pDataManager->DropDatabase(sDatabaseName);
}

void Instance::RenameDatabase(const String& sOldDatabaseName,
                              const String& sNewDatabaseName) {
  _pDataManager->RenameDatabase(sOldDatabaseName, sNewDatabaseName);
}

std::vector<String> Instance::GetDatabaseNames() const {
  return _pDataManager->GetDatabaseNames();
}

Table* Instance::GetTable(const String& sTableName) const {
  return _pDataManager->GetTable(sTableName);
}

void Instance::CreateTable(const String& sTableName, const Schema& iSchema) {
  _pDataManager->CreateTable(sTableName, iSchema);
}

void Instance::DropTable(const String& sTableName) {
  for (const auto& sColName :
       _pDataManager->_pDatabase->GetIndexManager()->GetTableIndexes(
           sTableName))
    _pDataManager->_pDatabase->GetIndexManager()->DropIndex(sTableName,
                                                            sColName);
  _pDataManager->DropTable(sTableName);
}

void Instance::RenameTable(const String& sOldTableName,
                           const String& sNewTableName) {
  _pDataManager->RenameTable(sOldTableName, sNewTableName);
}

FieldID Instance::GetColID(const String& sTableName,
                           const String& sColName) const {
  return _pDataManager->GetColID(sTableName, sColName);
}

FieldType Instance::GetColType(const String& sTableName,
                               const String& sColName) const {
  return _pDataManager->GetColType(sTableName, sColName);
}

Size Instance::GetColSize(const String& sTableName,
                          const String& sColName) const {
  return _pDataManager->GetColSize(sTableName, sColName);
}

std::vector<PageSlotID> Instance::Search(
    const String& sTableName, Condition* pCond,
    const std::vector<Condition*>& iIndexCond) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) throw TableNotExistException(sTableName);
  std::vector<PageSlotID> ans;
  if (iIndexCond.size() > 0) {
    IndexCondition* pIndexCond = dynamic_cast<IndexCondition*>(iIndexCond[0]);
    assert(pIndexCond != nullptr);
    auto iName = pIndexCond->GetIndexName();
    auto iRange = pIndexCond->GetIndexRange();
    std::vector<PageSlotID> iRes =
        GetIndex(iName.first, iName.second)->Range(iRange.first, iRange.second);
    for (Size i = 1; i < iIndexCond.size(); ++i) {
      IndexCondition* pIndexCond = dynamic_cast<IndexCondition*>(iIndexCond[i]);
      auto iName = pIndexCond->GetIndexName();
      auto iRange = pIndexCond->GetIndexRange();
      iRes = Intersection(iRes, GetIndex(iName.first, iName.second)
                                    ->Range(iRange.first, iRange.second));
    }
    ans = iRes;
  } else
    ans = pTable->SearchRecord(pCond);

  return ans;
}

PageSlotID Instance::Insert(const String& sTableName,
                            const std::vector<String>& iRawVec) {
  Table* pTable = GetTable(sTableName);
  if (pTable == nullptr) throw TableNotExistException(sTableName);

  Record* pRecord = pTable->EmptyRecord();

  try {
    pRecord->Build(iRawVec);
  } catch (const std::exception& e) {
    delete pRecord;
    throw e;
  }

  PageSlotID iPair = pTable->InsertRecord(pRecord);

  // Handle Insert on Index
  if (_pDataManager->_pDatabase->GetIndexManager()->HasIndex(sTableName)) {
    auto iColNames =
        _pDataManager->_pDatabase->GetIndexManager()->GetTableIndexes(
            sTableName);
    for (const auto& sCol : iColNames) {
      FieldID nPos = pTable->GetColPos(sCol);
      Field* pKey = pRecord->GetField(nPos);
      _pDataManager->_pDatabase->GetIndexManager()
          ->GetIndex(sTableName, sCol)
          ->Insert(pKey, iPair);
    }
  }

  delete pRecord;
  return iPair;
}

uint32_t Instance::Delete(const String& sTableName, Condition* pCond,
                          const std::vector<Condition*>& iIndexCond) {
  auto iResVec = Search(sTableName, pCond, iIndexCond);
  Table* pTable = GetTable(sTableName);
  bool bHasIndex =
      _pDataManager->_pDatabase->GetIndexManager()->HasIndex(sTableName);
  for (const auto& iPair : iResVec) {
    // Handle Delete on Index
    if (bHasIndex) {
      Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
      auto iColNames =
          _pDataManager->_pDatabase->GetIndexManager()->GetTableIndexes(
              sTableName);
      for (const auto& sCol : iColNames) {
        FieldID nPos = pTable->GetColPos(sCol);
        Field* pKey = pRecord->GetField(nPos);
        _pDataManager->_pDatabase->GetIndexManager()
            ->GetIndex(sTableName, sCol)
            ->Delete(pKey, iPair);
      }
    }

    pTable->DeleteRecord(iPair.first, iPair.second);
  }
  return iResVec.size();
}

uint32_t Instance::Update(const String& sTableName, Condition* pCond,
                          const std::vector<Condition*>& iIndexCond,
                          const std::vector<Transform>& iTrans) {
  auto iResVec = Search(sTableName, pCond, iIndexCond);
  Table* pTable = GetTable(sTableName);
  bool bHasIndex =
      _pDataManager->_pDatabase->GetIndexManager()->HasIndex(sTableName);
  for (const auto& iPair : iResVec) {
    // Handle Delete on Index
    if (bHasIndex) {
      Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
      auto iColNames =
          _pDataManager->_pDatabase->GetIndexManager()->GetTableIndexes(
              sTableName);
      for (const auto& sCol : iColNames) {
        FieldID nPos = pTable->GetColPos(sCol);
        Field* pKey = pRecord->GetField(nPos);
        _pDataManager->_pDatabase->GetIndexManager()
            ->GetIndex(sTableName, sCol)
            ->Delete(pKey, iPair);
      }
      delete pRecord;
    }

    pTable->UpdateRecord(iPair.first, iPair.second, iTrans);

    // Handle Insert on Index
    if (bHasIndex) {
      Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
      auto iColNames =
          _pDataManager->_pDatabase->GetIndexManager()->GetTableIndexes(
              sTableName);
      for (const auto& sCol : iColNames) {
        FieldID nPos = pTable->GetColPos(sCol);
        Field* pKey = pRecord->GetField(nPos);
        _pDataManager->_pDatabase->GetIndexManager()
            ->GetIndex(sTableName, sCol)
            ->Insert(pKey, iPair);
      }
      delete pRecord;
    }
  }
  return iResVec.size();
}

Record* Instance::GetRecord(const String& sTableName,
                            const PageSlotID& nPageSlotID) const {
  return _pDataManager->GetRecord(sTableName, nPageSlotID);
}

std::vector<Record*> Instance::GetTableInfos(const String& sTableName) const {
  return _pDataManager->GetTableInfos(sTableName);
}
std::vector<String> Instance::GetTableNames() const {
  return _pDataManager->GetTableNames();
}
std::vector<String> Instance::GetColumnNames(const String& sTableName) const {
  return _pDataManager->GetColumnNames(sTableName);
}

bool Instance::IsIndex(const String& sTableName, const String& sColName) const {
  return _pDataManager->_pDatabase->GetIndexManager()->IsIndex(sTableName,
                                                               sColName);
}

Index* Instance::GetIndex(const String& sTableName,
                          const String& sColName) const {
  return _pDataManager->_pDatabase->GetIndexManager()->GetIndex(sTableName,
                                                                sColName);
}

std::vector<Record*> Instance::GetIndexInfos() const {
  std::vector<Record*> iVec{};
  for (const auto& iPair :
       _pDataManager->_pDatabase->GetIndexManager()->GetIndexInfos()) {
    FixedRecord* pInfo =
        new FixedRecord(4,
                        {FieldType::CHAR_TYPE, FieldType::CHAR_TYPE,
                         FieldType::CHAR_TYPE, FieldType::INT_TYPE},
                        {TABLE_NAME_SIZE, COLUMN_NAME_SIZE, 10, 4});
    pInfo->SetField(0, new CharField(iPair.first));
    pInfo->SetField(1, new CharField(iPair.second));
    pInfo->SetField(
        2, new CharField(toString(GetColType(iPair.first, iPair.second))));
    pInfo->SetField(3, new IntField(GetColSize(iPair.first, iPair.second)));
    iVec.push_back(pInfo);
  }
  return iVec;
}

void Instance::CreateIndex(const String& sTableName, const String& sColName,
                           FieldType iType) {
  auto iAll = Search(sTableName, nullptr, {});
  _pDataManager->_pDatabase->GetIndexManager()->AddIndex(sTableName, sColName,
                                                         iType);
  Table* pTable = GetTable(sTableName);
  // Handle Exists Data
  for (const auto& iPair : iAll) {
    FieldID nPos = pTable->GetColPos(sColName);
    Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
    Field* pKey = pRecord->GetField(nPos);
    _pDataManager->_pDatabase->GetIndexManager()
        ->GetIndex(sTableName, sColName)
        ->Insert(pKey, iPair);
    delete pRecord;
  }
}

void Instance::DropIndex(const String& sTableName, const String& sColName) {
  auto iAll = Search(sTableName, nullptr, {});
  Table* pTable = GetTable(sTableName);
  for (const auto& iPair : iAll) {
    FieldID nPos = pTable->GetColPos(sColName);
    Record* pRecord = pTable->GetRecord(iPair.first, iPair.second);
    Field* pKey = pRecord->GetField(nPos);
    _pDataManager->_pDatabase->GetIndexManager()
        ->GetIndex(sTableName, sColName)
        ->Delete(pKey, iPair);
    delete pRecord;
  }
  _pDataManager->_pDatabase->GetIndexManager()->DropIndex(sTableName, sColName);
}

std::pair<std::vector<String>, std::vector<Record*>> Instance::Join(
    std::map<String, std::vector<PageSlotID>>& iResultMap,
    std::vector<Condition*>& iJoinConds) {
  return _pDataManager->Join(iResultMap, iJoinConds);
}

}  // namespace dbtrain_mysql
