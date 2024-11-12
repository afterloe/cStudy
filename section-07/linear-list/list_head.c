#ifndef __LIST_HEAD__
#define __LIST_HEAD__

typedef void* L;

/**
 * @brief 初始化操作， 建立一个空的线性表
 *
 * @param l 线性表头指针
 * @return 线性表头指针
 */
typedef L (*InitList)(L* l);

/**
 * @brief 判断列表是否为空
 *
 * @param l 现性表
 * @return 0 - false | 1 - true
 */
typedef int (*ListEmpty)(L l);

/**
 * @brief 清空线性表
 *
 * @param L 线性表
 * @return 0 - false | 1 - true
 */
typedef int (*CleanList)(L* L);

/**
 * @brief 将线性表中第i个位置的元素返回
 *
 * @param L 线性表
 * @param i 第几个元素
 * @param e 元素指针
 * @return  元素指针
 */
typedef L (*GetElem)(L l, int i, L* e);

/**
 * @brief 元素匹配
 *
 * @param l 线性表
 * @param e 元素
 * @return 查找成功返回其元素的下标，否则，返回-1
 */
typedef int (*LocateElem) (L l, L e);

/**
 * @brief 在线性表中的第i个元素插入新元素
 *
 * @param l 线性表
 * @param i 插入的位置
 * @param e 插入的元素
 * @return 插入成功返回插入位置的下标，否则，返回-1
 */
typedef int (*ListInsert) (L l, int i, L e);

/**
 * @brief 删除线性表中的第i个元素
 *
 * @param l 线性表
 * @param i 插入的位置
 * @param e 被删除的元素指针, 不需要则传NULL
 * @return 删除成功返回被删除的元素，否则，返回NULL
 */
typedef L (*ListDelete) (L l, int i, L e);

/**
 * @brief 查询元素个数
 *
 * @param l 线性表
 * @return 元素个数
 */
typedef long (*ListLength) (L l);

/**
 * @brief 销毁
 * 
 * @param l 线性表
 * @return 0 - false | 1 - true
 */
typedef int (*DestroyList) (L* l);

#endif
