#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "MiniSQL.h"
using namespace std;

class Interpreter
{
public:
    void inputCommand();                                            // get command from STDIN
    void getCondition(std::vector<string> command, condition_tree_t * condition);  // get condition tree
    info_t getInfo();                                        // get the result after interpretion
private:
    /*--------------parse different types of commands------------------*/
    bool parseCommand();                                            // parse the input
    void parseInsert();
    void parseSelect();
    void parseCreate();
    void parseUpdate();
    void parseDelete();
    void parseQuit();
    void parseHelp();           
    void parseDrop();  
    /*-----------------------------------------------------*/         
    void clearInfo();           // clear all info before rewriting
    string input;                                                   // command input by user
    std::vector<string> command;                                    // parsed command 
    info_t info;                // infomation interpreted by Interpreter
    condition_tree_t * makeTree(int index);
};
#endif