/**************************** 
 * MiniSQL.h - 宏定义，配置文件 
 ****************************/

#ifndef _MINISQL_H_
#define _MINISQL_H_

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
#define TABLE_LIST "../data/table.list"     /* 保存表信息的文件 */
#define FILE_PAGESIZE 4096          /* 虚拟页大小 */
#define MEM_MAXPAGE 1000            /* 内存页最大数目 */
#define FILENAME_MAXLEN 256         /* 文件名最大长度 */
#define MAX_CHAR_LENGTH     32      /* 最大 CHAR 类型字段长度 */

#define IDXHEAD_SIZE_IN_FILE (sizeof(attr_t) + sizeof(int))
                                    /* 一个索引头在文件中所占的大小 */
#define IDXNODE_SIZE_IN_FILE (sizeof(unsigned) + MAX_CHAR_LENGTH * sizeof(char)) 
                                    /* 一个索引节点在文件中所占的大小 */
#define ATTR_SIZE_IN_FILE (sizeof(bool) + sizeof(int) + sizeof(attrtype_t) + MAX_CHAR_LENGTH * sizeof(char))
                                    /* 一个字段在文件中所占的大小 */
#define TABLEHEAD_SIZE_IN_FILE (sizeof(int))
                                    /* 一个表信息头在文件中所占的大小 */
#define TABLENODE_SIZE_IN_FILE (2 * sizeof(int) + MAX_CHAR_LENGTH * sizeof(char) + MAX_ATTR_NUM * ATTR_SIZE_IN_FILE)
                                    /* 一个表信息项在文件中所占的大小 */

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
    int attrNum;        // 字段数
    int recordLength;   // 一条记录的字节数
    attr_t attributes[MAX_ATTR_NUM];    //字段
};

/* 表信息文件的文件头 */
struct table_head_t
{   
    int tableNum;       // 现存放的表的数量
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
    // void *basep;        // 内存中的基地址
    unsigned offset;    // basep 的偏移

    // index_node_t *nextNode;
};

/* 索引头 */
struct index_head_t
{
    attr_t attr;                // 做索引的字段
    int recNum;                 // 记录数目

    // index_node_t *firstNode;    // 指向第一个索引
};

/* 记录类型 */
struct record_t
{   
    attrtype_t type;
    string str_value;
    int int_value;
    record_t *next;
};

/* 全局配置 */
#endif