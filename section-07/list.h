#ifndef __LIST_HEAD__
#define __LIST_HEAD__

/**
 * @brief 初始化操作， 建立一个空的线性表
 *
 * @param list 线性表头指针
 * @param size 初始化容量
 * @return 线性表头指针
 */
typedef void* (*InitList)(void* list, int size);

/**
 * @brief 判断列表是否为空
 *
 * @param list 现性表
 * @return 0 - false | 1 - true
 */
typedef int (*ListEmpty)(void* list);

/**
 * @brief 清空线性表
 *
 * @param list 线性表
 * @return 0 - false | 1 - true
 */
typedef int (*CleanList)(void* list);

/**
 * @brief 将线性表中第i个位置的元素返回
 *
 * @param list 线性表
 * @param i 第几个元素
 * @param e 元素指针
 * @return  元素指针
 */
typedef void* (*GetElem)(void* list, int i, void* e);

/**
 * @brief 元素匹配
 *
 * @param list 线性表
 * @param e 元素
 * @return 查找成功返回其元素的下标，否则，返回-1
 */
typedef int (*LocateElem) (void* list, void* e);

/**
 * @brief 在线性表中的第i个元素插入新元素
 *
 * @param list 线性表
 * @param i 插入的位置
 * @param e 插入的元素
 * @return 插入成功返回插入位置的下标，否则，返回-1
 */
typedef int (*ListInsert) (void* list, int i, void* e);

/**
 * @brief 删除线性表中的第i个元素
 *
 * @param list 线性表
 * @param i 插入的位置
 * @param e 被删除的元素指针, 不需要则传NULL
 * @return 删除成功返回被删除的元素，否则，返回NULL
 */
typedef void* (*ListDelete) (void* list, int i, void* e);

/**
 * @brief 查询元素个数
 *
 * @param list 线性表
 * @return 元素个数
 */
typedef long (*ListLength) (void* list);

/**
 * @brief 销毁
 * 
 * @param list 线性表
 * @return 0 - false | 1 - true
 */
typedef int (*DestroyList) (void* list);

#endif
