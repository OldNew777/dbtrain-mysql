#include "result/mem_result.h"

#include <iomanip>
#include <iostream>
#include "exception/exceptions.h"

namespace dbtrain_mysql {

MemResult::MemResult(const std::vector<String>& iHeader) : Result(iHeader) {}

MemResult::~MemResult() {
  for (const auto& pRecord : _iData)
    if (pRecord) delete pRecord;
}

void MemResult::PushBack(Record* pRecord) { _iData.push_back(pRecord); }

Record* MemResult::GetRecord(Size nPos) const { return _iData[nPos]; }

Size MemResult::GetSize() const { return _iData.size(); }

String MemResult::ToString() const {
  String result;
  for (const auto& record : _iData) {
    for (uint32_t i = 0; i < record->GetSize(); i++) {
      result += record->GetField(i)->ToString();
      if (i != record->GetSize() - 1) {
        result += ",";
      }
    }
    result += "\n";
  }
  return result;
}

String MemResult::Dump() const{
  String result;
  for (const auto& record : _iData) {
    for (uint32_t i = 0; i < record->GetSize(); i++) {
      if(record->GetField(i)->GetType()==FieldType::CHAR_TYPE){
        result += "\'" + record->GetField(i)->ToString() + "\'";
      }
      else{
        result += record->GetField(i)->ToString();
      }
      if (i != record->GetSize() - 1) {
        result += ",";
      }
    }
    result += "\n";
  }
  return result;
}

std::vector<String> MemResult::ToVector() const {
  std::vector<String> results;
  for (const auto& record : _iData) {
    String result;
    for (uint32_t i = 0; i < record->GetSize(); i++) {
      result += record->GetField(i)->ToString();
      if (i != record->GetSize() - 1) {
        result += ",";
      }
    }
    results.push_back(result);
  }
  return results;
}

void MemResult::Display() const {
  std::vector<Size> widths(_iHeader.size(), 0);
  String line_sep = "+";
  String sep = " | ";
  for (uint32_t i = 0; i < _iHeader.size(); i++) {
    if (_iHeader[i].size() > widths[i]) {
      widths[i] = _iHeader[i].size();
    }
  }
  for (const auto& record : _iData) {
    for (uint32_t i = 0; i < record->GetSize(); i++) {
      if (record->GetField(i)->ToString().size() > widths[i])
        widths[i] = record->GetField(i)->ToString().size();
    }
  }
  String line = " " + line_sep;
  for (auto width : widths) {
    line += String(width + 2, '-') + line_sep;
  }
  line += "\n";
  std::cout << line;
  for (uint32_t i = 0; i < _iHeader.size(); i++) {
    std::cout << sep << std::setw(widths[i]) << _iHeader[i];
  }
  std::cout << sep << "\n";
  std::cout << line;
  for (const auto& record : _iData) {
    for (uint32_t i = 0; i < record->GetSize(); i++) {
      std::cout << sep << std::setw(widths[i])
                << record->GetField(i)->ToString();
    }
    std::cout << sep << std::endl;
  }
  std::cout << line;
  std::cout << '(' << _iData.size() << " rows )\n";
}
bool MemResult::CheckHaveNullPK(const std::vector<String>& sColNameVec){
  std::map<String, int> iColPosMap;
  for(int i = 0; i < sColNameVec.size(); i ++){
    bool flag = false;
    for(int j = 0; j < this->_iHeader.size(); i ++){
      if(sColNameVec[i] == _iHeader[j]){
        flag = true;
        iColPosMap[sColNameVec[i]] = j;
        break;
      }
    }
    if(!flag){
      printf("the column name used to alter table PK should be a exist column name\n");
      throw Exception();
    }
  }
  
  for (const auto& record : _iData) {
    for (uint32_t i = 0; i < sColNameVec.size(); i++) {
      if(record->GetField(iColPosMap[sColNameVec[i]])->ToString() == "NULL"){
        return true;
      }
    }
  }
  return false;
}
bool MemResult::CheckHaveDuplicatePK(const std::vector<String>& sColNameVec){
  std::map<String, int> iColPosMap;
  for(int i = 0; i < sColNameVec.size(); i ++){
    bool flag = false;
    for(int j = 0; j < this->_iHeader.size(); j ++){
      if(_iHeader[j] == sColNameVec[i]){
        flag = true;
        iColPosMap[sColNameVec[i]] = j;
        break;
      }
    }
    if(!flag){
      printf("the column name used to alter table PK should be a exist column name\n");
      throw Exception();
    }
  }
  
  for (uint32_t i = 0; i < _iData.size() - 1; i ++) {
    printf("%s\n",sColNameVec[0].data());
    for(uint32_t j = i + 1; j < _iData.size(); j ++){
      bool duplicate = true;
      for(const String& colName: sColNameVec){
        if(_iData[i]->GetField(iColPosMap[colName])->ToString() !=
            _iData[j]->GetField(iColPosMap[colName])->ToString()){
              duplicate = false;
              break;
        }
      }
      if(duplicate) return true;
    }
  }
  return false;
}
}  // namespace dbtrain_mysql
