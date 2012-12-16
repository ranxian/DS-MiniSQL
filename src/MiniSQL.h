/**************************** 
 * MiniSQL.h - 宏定义，配置文件 
 ****************************/

#ifndef MINISQL_H
#define MINISQL_H

/* 引用库 */
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>
#include <map>
#include <stack>
#include <vector>
using namespace std;

#define MAX_FILENAME_LENGTH 256     /* 最长文件名长度 */
#define MAX_CMD_LENGTH      256     /* 最长命令长度 */
#define MAX_ATTRNAME_LENGTH 256     /* 最长字段长度 */
#define MAX_RECORD_LENGTH   256     /* 最长记录长度 */
#define MAX_ATTR_NUM        32      /* 一个表的最长字段数目 */
#define TABLE_LIST "table.list"     /* 保存表信息的文件 */
#define INDEX_LIST "index.list"     /* 保存索引信息的文件 */
#define FILE_PAGESIZE 4096          /* 虚拟页大小 */
#define MEM_MAXPAGE 1000            /* 内存页最大数目 */
#define FILENAME_MAXLEN 256         /* 文件名最大长度 */
#define MAX_CHAR_LENGTH     32      /* 最大 CHAR 类型字段长度 */

/* 语法元素定义 */

/* 字段类型 */
typedef enum {
    CHAR,
    INT
} attrtype_t;

/* 表与字段的结构 */
/* 字段结构 */
struct attr_t {
    string name;        // 字段名
    bool isPrimary;     // 是否主键
    int length;         // 字段占字节数
    attrtype_t type;    // 类型（CHAR, INT）
    // bool isUnique;
};

/* 表的结构 */
struct table_t
{
    string name;        // 表名
    int attrNumber;     // 字段数
    int recordLength;   // 一条记录的字节数
    attr_t attributes[MAX_ATTR_NUM];    //字段
};

/* 运算符类型 */
typedef enum {
    EQ,     // ==
    NE,     // <>
    GT,     // >
    LT,     // <
    GTE,    // >=
    LTE     // <=
} oper_t;

/* 逻辑运算 */
typedef enum {
    AND,
    OR
} logic_t;

/* 操作类型 */
typedef enum {
    NONE,           // 无操作
    CREATE_TABLE,   // 建表
    DROP_TABLE,     // 删表
    CREATE_INDEX,   // 建索引 - 不急着做
    DELETE_INDEX,   // 删索引 - 不急着做
    UPDATE,         // 更新记录
    SELECT,         // 查记录
    INSERT,
    DELETE,         // 删记录
    QUIT,           // 退出程序
    HELP            // 打印帮助文档 - 不急着做
} cmd_t;

/* 条件树的结构 */
struct condition_tree_t
{
    condition_tree_t * left;    // 左子树
    condition_tree_t * right;   // 右子树
    logic_t logic;              // 不同条件之间的逻辑关系                    
    oper_t opName;              // ${leftOperand} ${opName} ${rightOperand}
    string leftOperand;         
    string rightOperand;
    bool end;
};

/* 解析器解析命令后的结果 */
struct info_t {
    cmd_t command;
    string tableName;                       // 命令相关的表名
    table_t t;                              // 命令相关的表信息
    std::vector<string> selectedItems;      // select 语句中被选择的字段
    std::vector<string> selectedTable;      // select 语句中被选择的Table
    std::map<string, string> insertItems;   // map of attribute name & value while inserting
    std::map<string, string> updateItems;   // map of attribute name & value while updating   
    condition_tree_t * tree;                // 条件树，用于 where 语句
};

/* 索引节点 */
struct index_node_t 
{
    string value;       // 关键码
    void *basep;        // 内存中的基地址
    unsigned offset;    // basep 的偏移

    index_node_t *nextNode;
};

/* 索引头 */
struct index_head_t
{
    attr_t attr;            // 做索引的字段
    index_node_t *firstNode; // 指向第一个索引
};

struct record_t
{   
    attrtype_t type;
    string str_value;
    int int_value;
    record_t *next;
};

/* 全局配置 */
#endif