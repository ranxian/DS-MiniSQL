#ifndef CATALOG_H
#define CATALOG_H

#include "MiniSQL.h"
/***********************************************************/

class Catalog
{
public:
    attr_t findAttr(string tableName, string attrName);  // 返回要求的字段信息
    table_t findTable(string tableName);                 // 返回要求的表的信息 
    attr_t getPrimaryAttrName();                         // 返回主键的字段信息（然后去找索引）
    bool attrExist();                                    // 返回字段是否存在
    bool attrTypeCheck();                                // 返回字段信息是否满足类型条件
    bool tableExist(string tableName);                   // 返回表是否存在
    bool attrExist(string tableName, string attrName);   // 返回表是否存在该字段
    void createTable(table_t & table);                   // 建表
    void deleteTable(table_t & table);                   // 删除表

    Catalog();
    ~Catalog();
private:

    inline void writeTableHead(ofstream & fout, table_head_t & tableHead);
    inline void readTableHead(ifstream & fin, table_head_t & tableHead);
    inline void writeTable(ofstream & fout, table_t & table);
    inline void readTable(ifstream & fin, table_t & table);
    inline void writeAttr(ofstream & fout, attr_t & attr);
    inline void readAttr(ifstream & fin, attr_t & attr);
};

#endif