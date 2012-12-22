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
}

int API::createTable() {
    info_t info;

    info = interpreter->getInfo();
    string tableName = info.tableName;

    if (catalog_manager->tableExist(tableName)) {
        return -1;
    } else {
        catalog_manager->createTable(info.t);
    }
}

int API::createIndex() {

}

int API::select() {
    return -1;
}

int API::insert() {
    return -1;
}

int API::dropTable() {
    return -1;
}

int API::deleteRecord() {
    return -1;
}

int API::getInput() {
    interpreter->inputCommand();
    return -1;
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