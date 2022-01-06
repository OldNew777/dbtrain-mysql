#include "basic_function.h"

#include <algorithm>
#include <cmath>
#include <unordered_set>

#include "exception/exceptions.h"

namespace dbtrain_mysql {

void PrintPageSlotID(const PageSlotID& nPageSlotID) {
  std::cout << '(' << nPageSlotID.first << ", " << nPageSlotID.second << ')';
}

bool CmpPageSlotID(const PageSlotID& iA, const PageSlotID& iB) {
  if (iA.first == iB.first) return iA.second < iB.second;
  return iA.first < iB.first;
}

String toUpper(const String& str) {
  String ans = str;
  std::transform(str.begin(), str.end(), ans.begin(), ::toupper);
  return ans;
}

float floatNext(const float& data) {
  // TODO : whether should here divided by 2?
  if (fabs(data) < __FLT_MIN__ / __FLT_EPSILON__)
    return data + __FLT_MIN__;
  else
    return data + fabs(data) * __FLT_EPSILON__;
}
int intNext(const int& data) {
  if (data != INT32_MAX)
    return data + 1;
  else
    // TODO : how to deal with INT32_MAX?
    return INT32_MAX;
}
String stringNext(const String& data) {
  // visiable char problem?
  String ans = data;
  if (data.length() == 0 || data[data.length() - 1] >= 126)
    ans += ' ';
  else
    ans[data.length() - 1] += 1;
  return ans;
}

String BuildColumnsString(const std::map<String, FieldID>& iColMap) {
  if (iColMap.size() == 0) return "";
  std::vector<std::pair<String, FieldID>> iTempVec{iColMap.begin(),
                                                   iColMap.end()};
  std::sort(iTempVec.begin(), iTempVec.end(), lessCmpBySecond<String, FieldID>);
  String sColumnsName = "";
  for (const auto& iPair : iTempVec) {
    sColumnsName += iPair.first;
    sColumnsName += "%";
  }
  return sColumnsName.substr(0, sColumnsName.size());
}

std::map<String, FieldID> LoadColumnsString(const String& sName) {
  std::map<String, FieldID> iColMap;
  size_t nBegin = 0, nEnd = 0;
  Size nPos = 0;
  nEnd = sName.find('%', nBegin);
  while (nEnd != std::string::npos) {
    String sKey = sName.substr(nBegin, nEnd - nBegin);
    iColMap[sKey] = nPos++;
    nBegin = nEnd + 1;
    nEnd = sName.find('%', nBegin);
  }
  return iColMap;
}

std::vector<PageSlotID> Intersection(std::vector<PageSlotID> iA,
                                     std::vector<PageSlotID> iB) {
  std::sort(iA.begin(), iA.end(), CmpPageSlotID);
  std::sort(iB.begin(), iB.end(), CmpPageSlotID);
  std::vector<PageSlotID> iRes{};
  std::set_intersection(iA.begin(), iA.end(), iB.begin(), iB.end(),
                        std::back_inserter(iRes));
  return iRes;
}

Field* BuildField(const String& sRaw, FieldType iTargetFieldType) {
  Field* pField = nullptr;
  if (toUpper(sRaw) == "NULL") {
    pField = new NullField();
  } else {
    if (iTargetFieldType == FieldType::NULL_TYPE) {
      pField = new NullField();
    } else if (iTargetFieldType == FieldType::INT_TYPE) {
      if (sRaw.find(".") != String::npos) {
        auto e = RecordTypeException("RecordTypeException");
        std::cout << e.what() << "\n";
        throw e;
      }
      try {
        int nVal = std::stoi(sRaw);
        pField = new IntField(nVal);
      } catch (const std::invalid_argument& e) {
        printf("INT format error %s\n");
        throw e;
      } catch (const std::out_of_range& e) {
        printf("INT out of range\n");
        throw e;
      }
    } else if (iTargetFieldType == FieldType::FLOAT_TYPE) {
      try {
        float fVal = std::stof(sRaw);
        pField = new FloatField(fVal);
      } catch (const std::invalid_argument& e) {
        printf("FLOAT format error\n");
        throw e;
      } catch (const std::out_of_range& e) {
        printf("FLOAT out of range\n");
        throw e;
      }
    } else if (iTargetFieldType == FieldType::CHAR_TYPE) {
      // erase \' and \"
      pField = new CharField(sRaw.substr(1, sRaw.size() - 2));
    } else {
      auto e = RecordTypeException();
      std::cout << e.what() << "\n";
      throw e;
    }
  }
  return pField;
}

bool LeagalDate(uint16_t year, uint8_t month, uint8_t day) {
  static std::unordered_set<uint8_t> smallMonth = {4, 6, 9, 11};
  if (year < 1000 || year >= 10000) return false;
  if (month == 0 || month > 12) return false;
  uint8_t dayMax = 31;
  if (smallMonth.find(dayMax) != smallMonth.end())
    dayMax = 30;
  else if (month == 2) {
    if (year % 400 == 0)
      dayMax == 29;
    else if (year % 100 == 0)
      dayMax = 28;
    else if (year & 4 == 0)
      dayMax = 29;
    else
      dayMax = 28;
  }
  if (day == 0 || day > dayMax) return false;
  return true;
}

}  // namespace dbtrain_mysql