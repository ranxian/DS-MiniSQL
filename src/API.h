#ifndef __API_H_
#define __API_H_

#include "MiniSQL.h"
#include "Catalog.h"
#include "Interpreter.h"
#include "Record.h"
#include "Index.h"

class API
{
public:
    int createTable();
    int dropTable();
    int createIndex();
    int select();
    int insert();
    int deleteRecord();
    int getInput();
    int exit();
    cmd_t commandType;
private:
    Catalog *catalog_manager;
    Index *index_manager;
    Interpreter *interpreter;
    Record *record_manager;
};

#endif