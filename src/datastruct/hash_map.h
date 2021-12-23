#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdint.h>

#include <unordered_map>
#include <vector>

#include "hash_mapping.h"
#include "macros.h"

using namespace std;

template <class T>
class HashMap : public HashMapping<T> {
 private:
  unordered_map<uint32_t, vector<T>> data;

 public:
  virtual void Insert(uint32_t hash, const T& t) override {
    hash = hash % BIG_PRIME;
    data[hash].push_back(t);
  };
  virtual void Updata(uint32_t hash, uint32_t index, const T& t) override {
    hash = hash % BIG_PRIME;
    data[hash][index] = t;
  }
  virtual vector<T> Get(uint32_t hash) const override {
    hash = hash % BIG_PRIME;
    auto iter = data.find(hash);
    if (iter == data.end()) return vector<T>();
    return iter->second;
  };
  virtual ~HashMap() = default;
};

#endif