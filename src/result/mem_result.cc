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

int MemResult::GetHeaderSize() const{
  return _iHeader.size();
}
String MemResult::GetHeader(int pos) const{
  return _iHeader[pos];
}
int MemResult::GetDataSize() const{
  return _iData.size();
}
String MemResult::GetFieldString(const int& row, const int& col) const{
  return _iData[row]->GetField(col)->ToString();
}
Field* MemResult::GetField(const int& row, const int& col) const{
  return _iData[row]->GetField(col);
}

}  // namespace dbtrain_mysql
