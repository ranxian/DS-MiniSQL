#include "API.h"

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
        return -1;
    } else {
        catalog_manager->createTable(info.t);
        catalog_manager->findTable(info.tableName);
    }
    return 0;
}

int API::createIndex() {
    info_t info = interpreter->getInfo();

    string tableName = info.tableName;
    string indexName = info.indexName;
    /* TODO */
    return 0;
}

int API::select() {
    info_t info = interpreter->getInfo();
    table_t table = info.t;

    record_t *records = record_manager->Select(info);

    record_manager->PrintHead(table);
    record_manager->Print(records);
    return -1;
}

int API::insert() {
    info_t info = interpreter->getInfo();

    record_manager->Insert(info);

    return 0;
}

int API::dropTable() {
    info_t info = interpreter->getInfo();

    catalog_manager->deleteTable(info.t);

    return 0;
}

int API::deleteRecord() {
    info_t info = interpreter->getInfo();
    index_node_t *res;
    string indexName = catalog_manager->getPrimaryAttr(info.tableName).name;
    index_manager->selectIndex(
        info.tableName, 
        indexName,
        "ZHAODIAO",
        "ZHAODIAO",
        res
    );
    record_manager->Delete(info, *res);

    return -1;
}

int API::getInput() {
    interpreter->inputCommand();
    return 0;
}

int API::exit() {
    return -1;
}

void API::help() {
    printf("This is the manul\n");
}

int API::update() {
    return -1;
}

cmd_t API::commandType() {
    return interpreter->getInfo().command;
};