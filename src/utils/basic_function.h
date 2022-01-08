#ifndef DBTRAIN_MYSQL_BASIC_FUNCTION_H
#define DBTRAIN_MYSQL_BASIC_FUNCTION_H

#include <dirent.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#include "defines.h"
#include "field/fields.h"

namespace dbtrain_mysql {

std::vector<String> GetFiles(const String& path);

void PrintPageSlotID(const PageSlotID& nPageSlotID);
bool CmpPageSlotID(const PageSlotID& iA, const PageSlotID& iB);

String toUpper(const String& str);

float floatNext(const float& data);
int intNext(const int& data);
String stringNext(const String& data);

template <class First, class Second>
bool lessCmpBySecond(const std::pair<First, Second>& a,
                     const std::pair<First, Second>& b) {
  return a.second < b.second;
}

String BuildColumnsString(const std::map<String, FieldID>& iColMap);
std::map<String, FieldID> LoadColumnsString(const String& sName);

std::vector<PageSlotID> Intersection(std::vector<PageSlotID> iA,
                                     std::vector<PageSlotID> iB);

Field* BuildField(const String& sRaw, FieldType iTargetFieldType);

bool LeagalDate(int year, int month, int day);

}  // namespace dbtrain_mysql

#endif