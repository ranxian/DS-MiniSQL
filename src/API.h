#ifndef __API_H_
#define __API_H_

#include "MiniSQL.h"
#include "Catalog.h"
#include "Interpreter.h"
#include "Record.h"
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
    // 删除数据
    int deleteRecord();
    // 从标准输入读
    int getInput();
    // 退出
    int exit();
    // 命令类型
    cmd_t commandType();
private:
    Catalog *catalog_manager;
    Index *index_manager;
    Interpreter *interpreter;
    Record *record_manager;
};

#endif