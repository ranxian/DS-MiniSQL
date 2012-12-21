#ifndef INDEX_H
#define INDEX_H

#include "MiniSQL.h"

/*
*   NOTE: 由于 B+ 树的代码量碉堡了，改用 线性索引 方式实现，若还有余力再改为 B+ 树
*         现在采用 线性索引 + 二分搜索
*         待修改为 二级索引 / B+ 树
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
    // 二分查找，返回关键码为 value 的节点的起始地址，给 select, update 使用
    inline int biSearch(fstream & fin, int from, int to, string value, attrtype_t type);
    // 比较关键码大小
    inline bool lessThan(string value_1, string value_2, attrtype_t type);
    // 文件读写的包装函数
    inline void readAttr(fstream & fin, attr_t & attr);
    inline void writeAttr(fstream & fout, attr_t & attr);
    inline void readHead(fstream & fin, index_head_t & head);
    inline void writeHead(fstream & fout, index_head_t & head);
    inline void readNode(fstream & fin, index_node_t & node);
    inline void writeNode(fstream & fout, index_node_t & node);
};

#endif