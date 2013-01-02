#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "MiniSQL.h"
using namespace std;

class Interpreter
{
public:
    /*
     * get command from STDIN
     */
    bool inputCommand();                      
    /*                      
     * get the result after interpretation
     */
    info_t getInfo();                         
    /*
     * print information for debug 
     */             
    void debug();    
    // Constructor
    Interpreter(); 
    // Destructor
    ~Interpreter();                        

private:
    /*--------------parse different types of commands------------------*/
    bool parseCommand();                                          
    bool parseInsert();
    bool parseSelect();
    bool parseCreate();
    bool parseUpdate();
    bool parseDelete();
    bool parseQuit();
    bool parseHelp();           
    bool parseDrop();  
    /*-----------------------------------------------------*/    
    // clear all info before rewriting     
    void clearInfo();           
    // show details of condition tree
    void showConditionTree(condition_tree_t * root);  
    // destruct the condition tree 
    void clearTree(condition_tree_t * root);
    // make condition tree with given input
    condition_tree_t * makeTree(int index);

    /* private variables */
    string input;                                            // command input by user
    std::vector<string> command;                             // parsed command 
    info_t info;                                             // infomation interpreted by Interpreter

};
#endif