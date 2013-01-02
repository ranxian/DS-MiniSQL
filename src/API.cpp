#include "API.h"
#include "helper.h"

API::API() 
{
    interpreter = new Interpreter;
    catalog_manager = new Catalog;
    index_manager = new Index;
    record_manager = new Record;
}

API::~API()
{
    delete interpreter;
    delete catalog_manager;
    delete index_manager;
    delete record_manager;
}

int API::createTable() {
    info_t info;

    info = interpreter->getInfo();
    string tableName = info.tableName;

    if (catalog_manager->tableExist(tableName)) {
        sql_error("TABLE [" + tableName + "] has already exsited");
        return -1;
    } else {
        catalog_manager->createTable(info.t);
    }

    sql_msg("TABLE [" + tableName + "] created");
    return 0;
}

int API::createIndex() {
    info_t info = interpreter->getInfo();

    string tableName = info.tableName;
    string indexName = info.indexName;
    /* TODO */
    return 0;
}

// V
// 打印多条记录
int API::select() {
    info_t info = interpreter->getInfo();
    table_t table = info.t;

    record_t *records = record_manager->Select(info);

    record_manager->PrintHead(table);
    record_manager->Print(records);
    return 0;
}

// 插入多条同样信息了吗？
int API::insert() {
    info_t info = interpreter->getInfo();

    record_manager->Insert(info);

    return 0;
}

// V
int API::dropTable() {
    info_t info = interpreter->getInfo();

    catalog_manager->deleteTable(info.t);
    // TODO: record_manager->deleteTable(info.t)

    return 0;
}

// no sign to delete
int API::deleteRecord() {
    info_t info = interpreter->getInfo();
    index_node_t res;
    // string indexName = catalog_manager->getPrimaryAttr(info.tableName).name;
    // index_manager->selectIndex(
    //     info.tableName, 
    //     indexName,
    //     "ZHAODIAO",
    //     "ZHAODIAO",
    //     res
    // );
    record_manager->Delete(info, res);

    return -1;
}

// V
int API::getInput() {
    if (interpreter->inputCommand())
        return 0;
    else return -1;
}

// V
int API::exit() {
    return -1;
}

// V
void API::help() {
    printf("This is the manul\n");
}

int API::update() {
    info_t info = interpreter->getInfo();
    index_node_t res;

    record_manager->Update(info, res);
    return 0;
}

cmd_t API::commandType() {
    return interpreter->getInfo().command;
};