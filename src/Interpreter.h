#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "MiniSQL.h"
using namespace std;

class Interpreter
{
public:
    // get command from STDIN
    void inputCommand();                                            
    // get condition tree
    void getCondition(std::vector<string> command, condition_tree_t * condition);  
    // get the result after interpretion
    info_t getInfo();                         
    // print information for debug               
    void debug();                             

private:
    /*--------------parse different types of commands------------------*/
    void parseCommand();                                            // parse the input
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