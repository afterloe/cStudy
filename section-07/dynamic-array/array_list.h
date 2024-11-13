#ifndef __ARRAY_LIST__
#define __ARRAY_LIST__

typedef struct __Node
{
    void** data; // 具体数据指针
    int size; // 数组大小
    int capacity;  // 数组容量
} Array;


/**
 * @brief 初始化操作， 建立一个空的线性表
 *
 * @param *array 线性表头指针
 * @param size 初始化容量
 * @return 线性表头指针
 */
extern void* initList(void* array, int size);

/**
 * @brief 判断列表是否为空
 *
 * @param array 现性表
 * @return 0 - false | 1 - true
 */
extern int isEmpty(const void* array);

/**
 * @brief 清空线性表
 *
 * @param *array 线性表
 * @return 0 - false | 1 - true
 */
extern int clean(Array* array);

/**
 * @brief 将线性表中第i个位置的元素返回
 *
 * @param *array 线性表
 * @param idx 第几个元素
 * @param elem 元素指针
 * @return 元素指针
 */
extern void* getElem(Array* array, int idx, void* elem);

/**
 * @brief 元素匹配
 *
 * @param array 线性表
 * @param elem 元素
 * @return 查找成功返回其元素的下标，否则，返回-1
 */
extern int locate(Array* array, void* elem);

/**
 * @brief 在线性表中的第i个元素插入新元素
 *
 * @param array 线性表
 * @param idx 插入的位置
 * @param elem 插入的元素
 * @return 插入成功返回插入位置的下标，否则，返回-1
 */
extern int insert(void* array, int idx, void* elem);

/**
 * @brief 删除线性表中的第i个元素
 *
 * @param array 线性表
 * @param idx 插入的位置
 * @param elem 被删除的元素指针, 不需要则传NULL
 * @return 删除成功返回被删除的元素，否则，返回NULL
 */
extern void* delete(Array* array, int idx, void* elem);

/**
 * @brief 查询元素个数
 *
 * @param array 线性表
 * @return 元素个数
 */
extern long length(void* array);

/**
 * @brief 销毁
 *
 * @param array 线性表
 * @return 0 - false | 1 - true
 */
extern int destroy(Array* array);


#endif