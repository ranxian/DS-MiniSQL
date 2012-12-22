#include "API.h"

API::API() 
{
    interpreter = new Interpreter;
}

API::~API()
{
    delete interpreter;
}

int API::createTable() {
    return -1;
}

int API::createIndex() {
    return -1;
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

cmd_t API::commandType() {
    return interpreter->getInfo().command;
};