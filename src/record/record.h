#ifndef DBTRAIN_MYSQL_RECORD_H
#define DBTRAIN_MYSQL_RECORD_H

#include "defines.h"
#include "field/field.h"

namespace dbtrain_mysql {

class Record {
 public:
  Record();
  Record(Size nFieldSize);
  virtual ~Record();

  Field *GetField(FieldID nPos) const;
  virtual void SetField(FieldID nPos, Field *pField);
  /**
   * @brief 获得记录中字段数量
   * @return Size 记录中字段的数量
   */
  Size GetSize() const;

  virtual Size Load(const uint8_t *src) = 0;
  virtual Size Store(uint8_t *dst) const = 0;
  virtual void Build(const std::vector<String> &iRawVec) = 0;
  virtual void Build(const std::vector<Field *> &iValueVec) = 0;
  /**
   * @brief 记录的深拷贝
   */
  virtual Record *Clone() const = 0;

  /**
   * @brief 截取Record的部分字段
   */
  virtual void Sub(const std::vector<Size> &iPos);
  /**
   * @brief 向Record后添加部分字段
   */
  virtual void Add(Record *pRecord);
  /**
   * @brief 删除Record中一个字段
   */
  virtual void Remove(FieldID nPos);
  virtual void Clear();

  virtual String ToString();

  uint32_t Hash(Size fieldIndex) const;

 protected:
  std::vector<Field *> _iFields;
};

}  // namespace dbtrain_mysql

#endif
