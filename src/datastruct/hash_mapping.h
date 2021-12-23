#ifndef HASH_MAPPING_H_
#define HASH_MAPPING_H_

#include <stdint.h>

using namespace std;

template <class T>
class HashMapping {
 public:
  virtual void Insert(uint32_t hash, const T& t) = 0;
  virtual void Updata(uint32_t hash, uint32_t index, const T& t) = 0;
  virtual vector<T> Get(uint32_t hash) const = 0;
  virtual ~HashMapping() = default;
};

#endif  // HASH_MAPPING_H_