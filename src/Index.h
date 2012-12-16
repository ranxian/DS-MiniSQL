#ifndef INDEX_H
#define INDEX_H

#include "Catalog.h"

/*
*   NOTE: 由于 B+ 树的代码量碉堡了，改用 线性索引 方式实现，若还有余力再改为 B+ 树
*         现在采用从小到大的顺序排列
*/
/* 索引名 */
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
    index_node_t *select(attr_t attribute, string value);                  // 查找关键码为 value 的索引项
    void create(attr_t attribute);                                         // 建立索引
    void insert(attr_t attribute, string value);                           // 插入关键码为 value 的新索引项
    void delete(attr_t attribute, string value);                           // 删除关键码为 value 的索引项
    void update(attr_t attribute, string value, string newValue);          // 更新关键码为 value 的索引项，新关键码为 newValue

    Index();
    ~Index();
private:
    index_node_t searchResult;
};




#endif