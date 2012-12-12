# include "Interpreter.h"

int Interpreter::getCommandType()
{
    return commandType;
}

void Interpreter::inputCommand()
{
    getline(cin, input, ';');
}

void Interpreter::parseCommand()
{
    int start, index;
    string seperators=" , \n";

    int index, start;
    start = input.find_first_not_of(seperators);

    while (start != string::npos)
    {
        index = input.find_first_of(seperators,start);
        if (index == string::npos)
        {
            command.push_back(input.substr(start));
            break;
        }
        else
        {
            command.push_back(input.substr(start,index-start));
            start = input.find_first_not_of(seperators,index+1);
        }
    }
    if (command[0] == "create" || command[0] == "CREATE")
    {

    }
    else if (command[0] == "select" || command[0] == "SELECT")
    {

    }
    else if (command[0] == "insert" || command[0] == "INSERT")
    {

    }
    else if (command[0] == "drop" || command[0] == "DROP")
    {

    }
    else if (command[0] == "delete" || command[0] == "DELETE")
    {

    }
    else if (command[0] == "quit" || command[0] == "QUIT")
    {

    }
    else if (command[0] == "execfiles" || command[0] == "EXECFILES")
    {
        
    }
}