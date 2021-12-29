#ifndef DBTRAIN_MYSQL_BASIC_FUNCTION_H
#define DBTRAIN_MYSQL_BASIC_FUNCTION_H

#include <iostream>

#include "defines.h"

namespace dbtrain_mysql {

void PrintPageSlotID(const PageSlotID& nPageSlotID);

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

}  // namespace dbtrain_mysql

#endif