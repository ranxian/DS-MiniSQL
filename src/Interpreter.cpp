# include "Interpreter.h"
# include <string.h>


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

    // cut into pieces
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

    //     interprete the input

    // Create database or create table
    if (command[0] == "create" || command[0] == "CREATE")
    {
        if (command[1] == "DATABASE" || command[1] == "database")
        {
            commandType = CREATE_DATABASE;
            info.databaseName = command[2];
        }
        else if (command[1] == "TABLE" || command[1] == "table")
        {
            commandType = CREATE_TABLE;
            info.tableName = command[2];
            char * str = info.tableName.c_str();
            str[31] = '\0';
            strcpy(info.t.tableName, str);
             int n = (comand.size()-5)/2;
             info.t.totalAttr = n;
             for (int i = 0; i < n; i++)
             {
                // input information to table
                // table not ready yet?
             }
        }

    }
    // select from table
    else if (command[0] == "select" || command[0] == "SELECT")
    {
        commandType = SELECT;
        int i = 1;
        while (command[i] != "FROM" && command[i] != "from")
        {
            selectedItems.push_back(command[i]);
            i++;
        }
        i++;
        tableName = command[i];
        if (i == command.size()-1)
            return;
        // build condition Tree
        // not finished
    }

    // insert into table
    else if (command[0] == "insert" || command[0] == "INSERT")
    {
        commandType = INSERT;
        // not ready
    }

    // drop table or database
    else if (command[0] == "drop" || command[0] == "DROP")
    {
        if (commad[1] == "TABLE" || command[1] == "table")
        {
            commandType = DROP_TABLE;
            info.tableName = command[2];
        }
        else if (command[1] == "DATABASE" || command[1] == "database")
        {
            commandType = DROP_DATABASE;
            info.databaseName = command[2];
        }
    }

    // delete
    else if (command[0] == "delete" || command[0] == "DELETE")
    {
        // not ready
    }

    // quit
    else if (command[0] == "quit" || command[0] == "QUIT")
    {
        commandType = QUIT;
    }

    // exec some files
    else if (command[0] == "execfiles" || command[0] == "EXECFILES")
    {
        commandType = EXECFILES;
        info.fileNmae = command[1];
    }
}

Information_t Interpreter::getInfo()
{
    return info;
}