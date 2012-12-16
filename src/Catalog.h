#ifndef CATALOG_H
#define CATALOG_H

/* 表与字段的结构 */
/* 字段结构 */
typedef struct {
    string name;        // 字段名
    bool isPrimary;     // 是否主键
    int length;         // 字段占字节数
    attrtype_t type;    // 类型（CHAR, INT）
    // bool isUnique;
} attr_t;

/* 表的结构 */
typedef struct 
{
    string name;        // 表名
    int recordLength;   // 一条记录的字节数
    int attrNumber;     // 字段数
    attr_t attributes[MAX_ATTR_NUM];    //字段
} table_t;

/***********************************************************/

class Catalog
{
public:
    attr_t findAttr(string tableName, string attrName);  // 返回要求的字段信息
    table_t findTable(string tableName);                 // 返回要求的表的信息 
    void create(table_t & table);                        // 建表
    void delete(table_t & table);                        // 删除表

    Catalog();
    ~Catalog();
private:
    bool tableExist(string tableName);   // 返回表是否存在
    bool attrExist();                    // 返回字段是否存在
    bool attrTypeCheck();                // 返回字段信息是否满足类型条件

    attr_t getPrimaryAttrName();   // 返回主键的字段信息（然后去找索引）
};

#endif