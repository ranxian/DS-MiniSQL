#ifndef INDEX_H
#define INDEX_H

#include "Catalog.h"

/*
*   NOTE: 由于 B+ 树的代码量碉堡了，改用 线性索引 方式实现，若还有余力再改为 B+ 树
*/

// 单个索引项（一个索引节点） 的结构
typedef struct 
{
    attrType value;             // 索引字段的值
    unsigned pageNum;           // 记录所在的页号
    unsigned long pageOffset;   // 记录所在页的页偏移

} indexNode;

// 存储 查找结果 的结构
typedef indexResult *pIndexResult;
typedef struct
{
    unsigned pageNum;           // 记录所在的页号
    unsigned long pageOffset;   // 记录所在页的页偏移

} indexResult;

/***********************************************************/

class Index
{
public:
    pIndexResult select(pAttrInfo *attrInfo, char *value);                   // 查找关键码为 value 的索引项
    void create(pAttrInfo *attrInfo);                                        // 建立索引
    void insert(pAttrInfo *attrInfo, char *value);                           // 插入关键码为 value 的新索引项
    void delete(pAttrInfo *attrInfo, char *value);                           // 删除关键码为 value 的索引项
    void update(pAttrInfo *attrInfo, char *value, char *newValue);           // 更新关键码为 value 的索引项，新关键码为 newValue
private:
};




#endif