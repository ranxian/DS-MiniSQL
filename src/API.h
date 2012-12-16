#ifndef __API_H_
#define __API_H_

#include "MiniSQL.h"

class API
{
public:
    int createTable();
    int dropTable();
    int createIndex();
    int select();
    int insert();
    int dropTable();
    int deleteRecord();
    int getInput();
    int exit();
    cmd_t commandType;
private:
    Catalog catalog_manager;
    Index index_manager;
    Interpreter interpreter;
    Record record_manager;
};

#endif