#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <stdint.h>

#include <map>
#include <vector>

#include "hash_mapping.h"
#include "macros.h"

using namespace std;

template <class T>
class HashTable : public HashMapping<T> {
 private:
  uint32_t bucket_num;
  vector<T>* data;

 public:
  HashTable() {
    data = new vector<T>[BIG_PRIME];
    this->bucket_num = BIG_PRIME;
  }
  HashTable(uint32_t bucket_num) {
    data = new vector<T>[bucket_num];
    this->bucket_num = bucket_num;
  }
  ~HashTable() { delete[] data; }

  void Insert(uint32_t hash, const T& t) override {
    hash = hash % bucket_num;
    data[hash].push_back(t);
  };
  void Updata(uint32_t hash, uint32_t index, const T& t) override {
    hash = hash % bucket_num;
    data[hash][index] = t;
  }
  vector<T> Get(uint32_t hash) const override {
    hash = hash % bucket_num;
    return data[hash];
  };
};

#endif  // HASH_TABLE_H_