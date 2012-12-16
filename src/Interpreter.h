#ifndef INTERPRETER_H
#define INTERPRETER_H
# include <string>
#include "Table.h"
#include "Catalog.h"
#include "ConditionTree.h"
/* 语法元素定义 */
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

/* 字段类型 */
typedef enum {
    CHAR,
    INT
} attr_t;

/* 操作类型 */
typedef enum {
    NONE,           // 无操作
    CREATE_TABLE,   // 建表
    DROP_TABLE,     // 删表
    CREATE_INDEX,   // 建索引 - 不急着做
    DELETE_INDEX,   // 删索引 - 不急着做
    UPDATE,         // 更新记录
    SELECT,         // 查记录
    DELETE,         // 删记录
    QUIT,           // 退出程序
    HELP            // 打印帮助文档 - 不急着做
} cmd_t;

/* 解析器解析命令后的结果 */
typdef struct {
    cmd_t command;
    string tableName;       // 命令相关的表名
    tableInfo t;            // 命令相关的表信息
    std::vector<string> selectedItems; // select 语句中被选择的字段
    std::vector<string> insertItems;   // insert 语句被更新的字段值
    ConditionTree * tree;   // 条件树，用于 where 语句
    // how to transfer insert infomation?? --zqm
} Info_t;

class Interpreter
{
public:
    void inputCommand();
    bool parseCommand();
    void getCondition(std::vector<string> command, ConditionTree * condition);
    int getCommandType();
    Information_t getInfo();
private:
    int commandType;
    string input;
    std::vector<string> command;
    Information_t info;
};
#endif