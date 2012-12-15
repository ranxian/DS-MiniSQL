#ifndef CATALOG_H
#define CATALOG_H

#include "Interpreter.h"

// 存放 表的信息 的结构
typedef struct *tableInfo pTableInfo;
typedef struct
{
    char tableName[32];             // 表名，最长 32 位
    int totalAttr;                  // 字段数
    int totalLenght;                // 一个记录占的字节数
    attrInfo attr[MAX_ATTR_NUM];    // 字段

} tableInfo;

// 字段的类型
typedef enum {
    INT,
    CHAR
} attrType;

// 存放 字段的信息 的结构
typedef struct *AttrInfo pAttrInfo;
typedef struct 
{
    char attrName[32];              // 字段名，最长 32 位
    int isPrimary;                  // 是否主键
    int colLength;                  // 字段占的字节数
    int isUnique;                   // 是否应该具有唯一值
    attrType type;                  // 字段类型，int/char

} attrInfo;

/***********************************************************/

class Catalog
{
public:
    bool tableExist(char *tableName);                           // 返回表是否存在
    bool attrExist(struct Information_t token);                 // 返回字段是否存在
    bool attrTypeCheck(struct Information_t token);             // 返回字段信息是否满足类型条件

    pAttrInfo findAttr(struct Information_t token);             // 返回要求的字段信息
    pAttrInfo getPrimaryAttrName(struct Information_t token);   // 返回主键的字段信息（然后去找索引）

    void create(struct Information_t token);                    // 建表
    void delete(struct Information_t token);                    // 删除表

    Catalog();
    ~Catalog();
private:
};

#endif