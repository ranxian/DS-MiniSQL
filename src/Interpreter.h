#ifndef INTERPRETER_H
#define INTERPRETER_H
# include <string>
# include <map>
# include <stack>
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
} attrtype_t;

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

/* 条件树的结构 */
typedef struct
{
    condition_tree_t * left;    // 左子树
    condition_tree_t * right;   // 右子树
    logic_t logic;              // 不同条件之间的逻辑关系                    
    oper_t opName;              // ${leftOperand} ${opName} ${rightOperand}
    string leftOperand;         
    string rightOperand;
    bool end;
} condition_tree_t;

/* 解析器解析命令后的结果 */
typedef struct {
    cmd_t command;
    string tableName;                       // 命令相关的表名
    table_t t;                              // 命令相关的表信息
    std::vector<string> selectedItems;      // select 语句中被选择的字段
    std::vector<string> selectedTable;      // select 语句中被选择的Table
    std::map<string, string> insertItems;   // map of attribute name & value while inserting
    std::map<string, string> updateItems;   // map of attribute name & value while updating   
    condition_tree_t * tree;                   // 条件树，用于 where 语句
} info_t;

class Interpreter
{
public:
    void inputCommand();                                            // get command from STDIN
    void getCondition(std::vector<string> command, ConditionTree * condition);  // get condition tree
    Information_t getInfo();                                        // get the result after interpretion
private:
    /*--------------parse different types of commands------------------*/
    bool parseCommand();                                            // parse the input
    void parseInsert();
    void parseSelect();
    void parseCreate();
    void parseUpdate();
    void parseDelete();
    void parseQuit();
    void parseHelp();           
    void parseDrop();  
    /*-----------------------------------------------------*/         
    void clearInfo();           // clear all info before rewriting
    string input;                                                   // command input by user
    std::vector<string> command;                                    // parsed command 
    Info_t info;                // infomation interpreted by Interpreter
    condition_tree_t * makeTree(int index);
};
#endif