# include "Interpreter.h"
# include <string.h>



void Interpreter::inputCommand()
{
    getline(cin, input, ';');
    parseCommand();
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

    if (command[0] == "create" || commandp[0] == "CRERATE")
        parseCreate();
    else if (command[0] == "select" || command[0] == "SELECT")
        parseSelect();
    else if (command[0] == "insert" || command[0] == "INSERT")
        parseInsert();
    else if (command[0] == "delete" || command[0] == "DELETE")
        parseDelete();
    else if (command[0] == "drop" || command[0] == "DROP")
        parseDrop();
    else if (command[0] == "update" || command[0] == "UPDATE")
        parseUpdate();
    else if (command[0] == "quit" || command[0] == "QUIT")
        parseQuit();
    else if (command[0] == "help" || command[0] == "HELP")
        parseHelp();
}

Info_t Interpreter::getInfo()
{
    return info;
}

void Interpreter::parseCreate()
{
    int count = 0;
    int i = 4;
    int length = 0;
    info.command = CREATE_TABLE;
    info.tableName = command[2];
    info.t.name = command[2];
    while (command[i] != ")")
    {
        info.t.attributes[count].name = command[i];
        i++;
        if (command[i] == "int" || command[i] == "INT")
        {
            info.t.attributes[count].type = INT;
            info.t.attributes[count].length = 4;
            info.t.attributes[count].isPrimary = false;
            length += 4;
        }
        else if (command[i] == "char" || command[i] == "CHAR" )
        {
            info.t.attributes[count].type = CHAR;
            info.t.attributes[count].length = 32;
            info.t.attributes[count].isPrimary = false;
            length += 32;
        }
        i++;
        if (command[i] == "primary")
        {
            info.t.attributes[count].isPrimary = true;
            i++;
            i++;
        }
        if (command[i] == "default")
        {
            i++;

            // set default
            // attr_t not supported yet

            i++;
        }

        count++;
    }

    info.t.attrNumber = count;
    info.t.recordLength = length;
}

void Interpreter::parseHelp()
{
    info.command = HELP;
}

void Interpreter::parseQuit()
{
    info.command = QUIT;
}

void Interpreter::parseDrop()
{
    info.command = DROP_TABLE;
    info.tableName = command[2];
}

void Interpreter::parseSelect()
{
    int i = 1;
    while (command[i] != "from" && command[i] != "FROM")
    {
        info.selectedItems.push_back(command[i]);
        i++;    
    }
    i++;
    while (command[i] != "where" && command[i] != "WHERE" && i < command.size())
    {
        info.selectedTable.push_back(command[i]);
        i++;
    }
    if (command[i] == "where" || command[i] == "WHERE")
    {
        // build condition tree
    }
}

