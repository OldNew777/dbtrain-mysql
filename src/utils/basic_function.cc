#include "basic_function.h"

#include <algorithm>
#include <cmath>

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

}  // namespace dbtrain_mysql