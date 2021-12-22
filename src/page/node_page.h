#ifndef DBTRAIN_MYSQL_NODE_PAGE_H
#define DBTRAIN_MYSQL_NODE_PAGE_H

#include "defines.h"
#include "field/field.h"
#include "page/linked_page.h"

namespace dbtrain_mysql {

class Index;

class NodePage : public LinkedPage {
 private:
  /**
   * @brief 页面对应结点是否为叶结点
   */
  bool _bLeaf;
  /**
   * @brief 结点页面一个Key占用的空间
   */
  Size _nKeyLen;
  /**
   * @brief 结点页面能存储的最大KeyValuePair容量
   */
  Size _nCap;
  /**
   * @brief 结点页面Key的类型
   */
  FieldType _iKeyType;

  /**
   * @brief Key数组，用于存储类型为Field*的Key
   */
  std::vector<Field *> _iKeyVec;
  /**
   * @brief Value数组，用于存储类型为PageSlotID的Value
   */
  std::vector<PageSlotID> _iChildVec;
  friend class Index;

 public:
  /**
   * @brief 初始化结点页面
   * @param nKeyLen Key长度
   * @param iKeyType Key类型
   * @param bLeaf 是否为叶结点
   */
  NodePage(Size nKeyLen, FieldType iKeyType, bool bLeaf);
  /**
   * @brief 构建一个包含一定数量子结点的结点页面
   *
   * @param nKeyLen Key长度
   * @param iKeyType Key类型
   * @param bLeaf 是否为叶结点
   * @param iKeyVec 子结点的Key值
   * @param iChildVec 子结点的Value值（PageSlotID数组）
   */
  NodePage(Size nKeyLen, FieldType iKeyType, bool bLeaf,
           const std::vector<Field *> &iKeyVec,
           const std::vector<PageSlotID> &iChildVec);
  /**
   * @brief 导入一个已经存在的页面结点。
   *
   * @param nPageID 页面结点的页编号
   */
  NodePage(PageID nPageID);
  ~NodePage();

  /**
   * @brief 插入一条Key Value Pair
   * @param pKey 插入的Key
   * @param iPair 插入的Value
   * @return true 插入成功
   * @return false 插入失败
   */
  bool Insert(Field *pKey, const PageSlotID &iPair);
  /**
   * @brief 删除某个Key下所有的Key Value Pair
   * @param pKey 删除的Key
   * @return Size 删除的键值数量
   */
  Size Delete(Field *pKey);
  /**
   * @brief 删除某个Key Value Pair
   * @param pKey 删除的Key
   * @param iPair 删除的Value
   * @return true 删除成功
   * @return false 删除失败
   */
  bool Delete(Field *pKey, const PageSlotID &iPair);
  /**
   * @brief 更新某个Key Value Pair到新的Value
   * @param pKey 更新的Key
   * @param iOld 原始的Value
   * @param iNew 要更新成的新Value
   * @return true 更新成功
   * @return false 更新失败
   */
  bool Update(Field *pKey, const PageSlotID &iOld, const PageSlotID &iNew);
  /**
   * @brief 使用索引进行范围查找，左闭右开区间[pLow, pHigh)
   *
   * @param pLow
   * @param pHigh
   * @return std::vector<PageSlotID> 所有符合范围条件的Value数组
   */
  std::vector<PageSlotID> Range(Field *pLow, Field *pHigh);
  /**
   * @brief 清空当前结点和所有子结点所占用的所有空间
   */
  void Clear();

  /**
   * @brief 判断结点是否超过最大容量
   */
  bool Overflow() const;
  /**
   * @brief 判断结点是否为满结点
   */
  bool Full() const;
  /**
   * @brief 判断结点是否 > _nCap / 2
   */
  bool MoreThanHalf() const;
  /**
   * @brief 判断结点是否 < _nCap / 2
   */
  bool LessThanHalf() const;
  /**
   * @brief 判断结点是否为空结点
   */
  bool Empty() const;

  /**
   * @brief 获得结点保存的索引字段类型
   */
  FieldType GetType() const;
  /**
   * @brief 子节点个数
   */
  Size size() const;

  /**
   * @brief 将该节点分裂为两个
   * @return NodePage 分裂出来的节点
   */
  NodePage *Split();
  /**
   * @brief 将相邻的两个节点合并为当前这一个节点，并删除last节点
   * @param pNextPage 左侧节点（相邻）
   */
  void MergePrev(NodePage *pPrevPage);
  /**
   * @brief 将相邻的两个节点合并为当前这一个节点，并删除next节点
   * @param pNextPage 右侧节点（相邻）
   */
  void MergeNext(NodePage *pNextPage);
  /**
   * @brief 整理 [left, right) 内的各子节点
   */
  void Arange(Size left, Size right);

 private:
  void print() const;
  /**
   * @brief 计算最大容量
   */
  void CalculateCap();

  /**
   * @brief 解析格式化的页面数据，初始化结点信息。
   */
  void Load();
  /**
   * @brief 将结点信息保存为格式化的页面数据。
   */
  void Store();

  /**
   * @brief 获得该结点最后一个Key
   */
  Field *LastKey() const;

  /**
   * @brief >=pKey 的第一个Key在KeyVec中的位置
   * @return >=pKey 的最后一个Key在KeyVec中的位置
   */
  Size LowerBound(Field *pKey);
  /**
   * @brief <=pKey 的第一个Key在KeyVec中的位置
   * @return <=pKey 的最后一个Key在KeyVec中的位置
   */
  Size UpperBound(Field *pKey);
  /**
   * @brief >pKey 的第一个Key在KeyVec中的位置
   * @return >pKey 的最后一个Key在KeyVec中的位置
   */
  Size MoreBound(Field *pKey);
  /**
   * @brief <pKey 的最后一个Key在KeyVec中的位置
   * @return <pKey 的最后一个Key在KeyVec中的位置
   */
  Size LessBound(Field *pKey);

  /**
   * @brief 分裂出当前结点的后一半子结点。
   * @return std::pair<std::vector<Field *>, std::vector<PageSlotID>>
   * 分裂出的后一半Key Value Pair数据
   */
  std::pair<std::vector<Field *>, std::vector<PageSlotID>> PopHalf();
  /**
   * @brief 取出当前结点的所有子结点。
   * @return std::pair<std::vector<Field *>, std::vector<PageSlotID>>
   * 取出的Key Value Pair数据
   */
  std::pair<std::vector<Field *>, std::vector<PageSlotID>> PopAll();
  /**
   * @brief 分裂出当前结点的后n个子结点。
   * @return std::pair<std::vector<Field *>, std::vector<PageSlotID>>
   * 分裂出的后n个Key Value Pair数据
   */
  std::pair<std::vector<Field *>, std::vector<PageSlotID>> PopBackNodes(Size n);
  /**
   * @brief 分裂出当前结点的前n个子结点。
   * @return std::pair<std::vector<Field *>, std::vector<PageSlotID>>
   * 分裂出的前n个Key Value Pair数据
   */
  std::pair<std::vector<Field *>, std::vector<PageSlotID>> PopFrontNodes(
      Size n);

  /**
   * @brief 在最前面插入子节点。
   * @param nodes 待插入的节点
   */
  void PushFrontNodes(
      std::pair<std::vector<Field *>, std::vector<PageSlotID>> nodes);
  /**
   * @brief 在最后面插入子节点。
   * @param nodes 待插入的节点
   */
  void PushBackNodes(
      std::pair<std::vector<Field *>, std::vector<PageSlotID>> nodes);
  /**
   * @brief 删除 [left, right) 间的子节点。
   * @param left 区间左端点
   * @param right 区间右端点
   */
  void EraseNodes(Size left, Size right);
};

}  // namespace dbtrain_mysql

#endif