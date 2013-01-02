#ifndef __API_H_
#define __API_H_

#include "MiniSQL.h"
#include "Catalog.h"
#include "Interpreter.h"
#include "Record.h"
#include "Index.h"
class Index;
class API
{
public:
    API();
    ~API();
    // 建表
    int createTable();
    // 删表
    int dropTable();
    // 建立索引
    int createIndex();
    // 查询
    int select();
    // 插入
    int insert();
    // 更新
    int update();
    // 删除数据
    int deleteRecord();
    // 从标准输入读
    int getInput();
    // 退出
    int exit();
    // 帮助
    void help();
    // 命令类型
    cmd_t commandType();
    index_node_t* getIndex(string tableName, condition_tree_t *node);
private:
    Catalog *catalog_manager;
    Index *index_manager;
    Interpreter *interpreter;
    Record *record_manager;
};

#endif