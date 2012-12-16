#ifndef CATALOG_H
#define CATALOG_H

#include "MiniSQL.h"
/***********************************************************/

class Catalog
{
public:
    attr_t findAttr(string tableName, string attrName);  // 返回要求的字段信息
    table_t findTable(string tableName);                 // 返回要求的表的信息 
    void createTable(table_t & table);                   // 建表
    void deleteTable(table_t & table);                   // 删除表
    bool attrExist(string tableName, string attrName);

    Catalog();
    ~Catalog();
private:
    bool tableExist(string tableName);   // 返回表是否存在
    bool attrExist();                    // 返回字段是否存在
    bool attrTypeCheck();                // 返回字段信息是否满足类型条件

    attr_t getPrimaryAttrName();   // 返回主键的字段信息（然后去找索引）
};

#endif