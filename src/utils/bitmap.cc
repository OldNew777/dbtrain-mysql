#include "utils/bitmap.h"

#include <cstring>

namespace dbtrain_mysql {

Bitmap::Bitmap(Size size) {
  _pBits = new uint8_t[(size + 7) >> 3];
  memset(_pBits, 0, (size + 7) >> 3);
  _nSize = size;
  _nUsed = 0;
}

Bitmap::~Bitmap() { delete[] _pBits; }

inline void Bitmap::Set(Size pos) {
  if (!Get(pos)) {
    _pBits[pos >> 3] |= (1 << (pos & 7));
    ++_nUsed;
  }
}

inline void Bitmap::Unset(Size pos) {
  if (Get(pos)) {
    _pBits[pos >> 3] &= ~(1 << (pos & 7));
    --_nUsed;
  }
}

inline bool Bitmap::Get(Size pos) const {
  return _pBits[pos >> 3] & (1 << (pos & 7));
}

inline Size Bitmap::GetSize() const { return _nSize; }

inline Size Bitmap::GetUsed() const { return _nUsed; }

inline bool Bitmap::Empty() const { return _nUsed == 0; }

inline bool Bitmap::Full() const { return _nUsed == _nSize; }

void Bitmap::Load(const uint8_t* pBits) {
  memcpy(_pBits, pBits, (_nSize + 7) >> 3);
  for (Size i = 0; i < _nSize; ++i)
    if (Get(i)) ++_nUsed;
}

void Bitmap::Store(uint8_t* pBits) { memcpy(pBits, _pBits, (_nSize + 7) >> 3); }

}  // namespace dbtrain_mysql
