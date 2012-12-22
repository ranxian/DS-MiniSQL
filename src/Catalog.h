#ifndef CATALOG_H
#define CATALOG_H

#include "MiniSQL.h"
/***********************************************************/

class Catalog
{
public:
    // 返回要求的字段信息
    attr_t findAttr(string tableName, string attrName);  
    // 返回要求的表的信息
    table_t findTable(string tableName);                  
    // 返回主键的字段信息（然后去找索引）
    attr_t getPrimaryAttrName(string tableName);                               
    // 返回表是否存在
    bool tableExist(string tableName);                  
    // 返回表是否存在该字段
    bool attrExist(string tableName, string attrName); 
    // 建表  
    void createTable(table_t & table);                  
    // 删除表 
    void deleteTable(table_t & table);           

    Catalog();
    ~Catalog();
private:
    // 初始化表文件（写入表信息头）请在建立第一个表之前调用
    void initTable();        
    // 文件读写的包装函数
    void writeTableHead(fstream & fout, table_head_t & tableHead);
    void readTableHead(fstream & fin, table_head_t & tableHead);
    void writeTable(fstream & fout, table_t & table);
    void readTable(fstream & fin, table_t & table);
    void writeAttr(fstream & fout, attr_t & attr);
    void readAttr(fstream & fin, attr_t & attr);
};

#endif