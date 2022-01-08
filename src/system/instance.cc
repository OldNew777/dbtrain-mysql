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

Instance::~Instance() { delete _pDataManager; }

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
    const std::vector<Condition*>& iIndexCond, int limit, int offset) {
  return _pDataManager->Search(sTableName, pCond, iIndexCond, limit, offset);
}

PageSlotID Instance::Insert(const String& sTableName,
                            const std::vector<Field*>& iValueVec) {
#ifdef RAW2FIELD_BUILD_DEBUG
  printf("\n------------ Insert ------------\n");
  printf("(");
  for (auto pField : iValueVec) {
    std::cout << pField->ToString() << ", ";
  }
  printf(")\n");
  printf("------------- end --------------\n");
#endif
  return _pDataManager->Insert(sTableName, iValueVec);
}

PageSlotID Instance::Insert(const String& sTableName,
                            const std::vector<String>& iRawVec) {
  return _pDataManager->Insert(sTableName, iRawVec);
}

uint32_t Instance::Delete(const String& sTableName, Condition* pCond,
                          const std::vector<Condition*>& iIndexCond) {
  return _pDataManager->Delete(sTableName, pCond, iIndexCond);
}

uint32_t Instance::Update(const String& sTableName, Condition* pCond,
                          const std::vector<Condition*>& iIndexCond,
                          const std::vector<Transform>& iTrans) {
  return _pDataManager->Update(sTableName, pCond, iIndexCond, iTrans);
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
  return _pDataManager->IsIndex(sTableName, sColName);
}

Index* Instance::GetIndex(const String& sTableName,
                          const String& sColName) const {
  return _pDataManager->GetIndex(sTableName, sColName);
}

std::vector<Record*> Instance::GetIndexInfos() const {
  return _pDataManager->GetIndexInfos();
}

void Instance::CreateIndex(const String& sTableName, const String& sColName) {
  _pDataManager->CreateIndex(sTableName, sColName);
}

void Instance::DropIndex(const String& sTableName, const String& sColName) {
  _pDataManager->DropIndex(sTableName, sColName);
}

std::pair<std::vector<String>, std::vector<Record*>> Instance::Join(
    std::map<String, std::vector<PageSlotID>>& iResultMap,
    std::vector<Condition*>& iJoinConds) {
  return _pDataManager->Join(iResultMap, iJoinConds);
}
void Instance::AddPrimaryKey(const String& sTableName, const std::vector<String> sColNameVec){
  _pDataManager->AddPrimaryKey(sTableName, sColNameVec);
}
void Instance::AddForeignKey(const String& lTableName, const String& lColName,
    const String& fTableName, const String& fColName){
  _pDataManager->AddForeignKey(lTableName, lColName, fTableName, fColName);
}
void Instance::AddUniqueKey(const String& sTableName, const String& sColNameVec){
  _pDataManager->AddUniqueKey(sTableName, sColNameVec);
}

void Instance::DropPrimaryKey(const String& sTableName, const String& sColName) {
  _pDataManager->DropPrimaryKey(sTableName, sColName);
}
void Instance::DropForeignKey(const String& sTableName, const String& sColName) {
  _pDataManager->DropForeignKey(sTableName, sColName);
}
}  // namespace dbtrain_mysql
