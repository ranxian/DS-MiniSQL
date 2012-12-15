#ifndef INTERPRETER_H
#define INTERPRETER_H
# include <string>
#include "Table.h"
#include "Catalog.h"
#include "ConditionTree.h"
/*----------constant variables for indentifying command type------------------*/
extern const int CREATE_TABLE = 0;
extern const int CREATE_INDEX = 1;
extern const int CREATE_DATABASE = 2;
extern const int SELECT = 3;
extern const int INSERT = 4;
extern const int DROP_TABLE = 5;
extern const int DROP_INDEX = 6;
extern const int DROP_DATABASE = 7;
extern const int DELETE = 8;
extern const int QUIT = 9;
extern const int EXECFILES = 10;


class Interpreter
{
public:
    void inputCommand();
    bool parseCommand();
    void getCondition(std::vector<string> command, ConditionTree * condition);
    int getCommandType();
    Information_t getInfo();
private:
    int commandType;
    string input;
    std::vector<string> command;
    Information_t info;
};

struct  Information_t
{
    string databaseName;
    string tableName;
    tableInfo t;
    std::vector<string> selectedItems;
    ConditionTree * tree;
    string fileName;
    // how to transfer insert infomation??


};
#endif