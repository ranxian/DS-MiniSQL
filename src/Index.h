#ifndef INDEX_H
#define INDEX_H

#include "MiniSQL.h"

/*
*   NOTE: 由于 B+ 树的代码量碉堡了，改用 线性索引 方式实现，若还有余力再改为 B+ 树
*         现在采用从小到大的顺序排列
*         待修改为 二分查找 / 二级索引 / B+ 树
*/

/***********************************************************/

class Index
{
public:
    // 查找关键码为 value 的索引项
    void selectIndex(string tableName, string indexName, string value, index_node_t *res);
    // 建立索引
    void createIndex(string tableName, string indexName, attr_t & attr);                           
    // 插入关键码为 value 的新索引项
    void insertIndex(string tableName, string indexName, index_node_t & node);
    // 删除关键码为 value 的索引项
    void deleteIndex(string tableName, string indexName, string value);                           
    // 更新关键码为 value 的索引项，新关键码为 newValue
    void updateIndex(string tableName, string indexName, string value, string newValue);          
    Index();
    ~Index();
private:
    inline bool lessThan(string value_1, string value_2, attrtype_t type);
    inline void readHead(fstream & fin, index_head_t & head);
    inline void writeHead(fstream & fout, index_head_t & head);
    inline void readNode(fstream & fin, index_node_t & node);
    inline void writeNode(fstream & fout, index_node_t & node);
};

#endif