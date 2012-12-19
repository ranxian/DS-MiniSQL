#include "API.h"

API::API() 
{
    interpreter = new Interpreter;
}

API::~API()
{
    delete interpreter;
}

int API::createTable() {}

int API::createIndex() {}

int API::select() {}

int API::insert() {}

int API::dropTable() {}

int API::deleteRecord() {}

int API::getInput() {
    interpreter->inputCommand();
}

int API::exit() {}

cmd_t API::commandType() {
    return interpreter->getInfo().command;
};