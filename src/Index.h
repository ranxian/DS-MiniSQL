#ifndef INDEX_H
#define INDEX_H

#include "Catalog.h"
#include <stdlib.h>
#include <cstring>

/*
*   NOTE: 由于 B+ 树的代码量碉堡了，改用 线性索引 方式实现，若还有余力再改为 B+ 树
*         现在采用从小到大的顺序排列
*/
/* 索引节点 */
typedef struct 
{
    string value;       // 关键码
    void *basep;        // 内存中的基地址
    unsigned offset;    // basep 的偏移
} index_node_t;

/* 索引头 */
typedef struct 
{
    attr_t attr;            // 做索引的字段
    indexNode_t *firstNode; // 指向第一个索引
} index_head_t;

/***********************************************************/

class Index
{
public:
    pIndexResult select(pAttrInfo *attrInfo, char *value);                   // 查找关键码为 value 的索引项
    void create(pAttrInfo *attrInfo);                                        // 建立索引
    void insert(pAttrInfo *attrInfo, char *value);                           // 插入关键码为 value 的新索引项
    void delete(pAttrInfo *attrInfo, char *value);                           // 删除关键码为 value 的索引项
    void update(pAttrInfo *attrInfo, char *value, char *newValue);           // 更新关键码为 value 的索引项，新关键码为 newValue

    Index();
    ~Index();
private:
    indexResult selectResult;
};




#endif