# include "Interpreter.h"
# include <string.h>



void Interpreter::inputCommand()
{
    getline(cin, input, ';');
    cin.get();
    parseCommand();
}

void Interpreter::parseCommand()
{
    clearInfo();
    int start, index;
    string seperators=" , \n";

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

    if (command[0] == "create" || command[0] == "CRERATE")
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

info_t Interpreter::getInfo()
{
    return info;
}

void Interpreter::parseCreate() // OK
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

    info.t.attrNum = count;
    info.t.recordLength = length;
}

void Interpreter::parseHelp()   // OK
{
    info.command = HELP;
}

void Interpreter::parseQuit()   //OK
{
    info.command = QUIT;
}

void Interpreter::parseDrop()   //OK
{
    info.command = DROP_TABLE;
    info.tableName = command[2];
}

void Interpreter::parseSelect() //OK
{
    info.command = SELECT;
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
        info.tree = makeTree(i+1);
    }
}

void Interpreter::parseDelete() //OK
{
    info.command = DELETE;
    info.command = DELETE;
    info.tableName = command[2];
    if (command.size() == 3)
    {
        info.tree = NULL;
    }
    else
    {
        info.tree = makeTree(4);
    }
}

void Interpreter::clearInfo()
{
    command.clear();
    info.command = NONE;
    info.tableName = "";
    if (info.tree)
        delete info.tree;
    info.tree = NULL;
    info.selectedItems.clear();
    info.selectedTable.clear();
    info.insertItems.clear();
}

void Interpreter::parseInsert()  //OK
{
    info.command = INSERT;
    info.tableName = command[2];
    int index1 ,index2;
    index1 = index2 = 4;
    while (command[index2] != "(")
        index2++;
    index2++;
    while (command[index1] != ")")
    {
        info.insertItems.insert(map<string,string>::value_type(command[index1],command[index2]));
    }
}

void Interpreter::parseUpdate() //OK
{
    info.command = UPDATE;
    info.tableName = command[1];
    int index1 = 3;
    int index2 = 5;
    info.updateItems.insert(map<string,string>::value_type(command[index1],command[index2]));
    if (command.size() != 6)
    {
        if (command[6] == "where" || command[6] == "WHERE")
        {
            info.tree = makeTree(7);
        }
    }

}

condition_tree_t * Interpreter::makeTree(int index)
{
    std::stack<condition_tree_t *> atom;
    std::stack<condition_tree_t *> logic;
    condition_tree_t * ptr;
    int i,j,k;
    i = index;
    while (i < command.size())
    {
        ptr = new condition_tree_t();
        if (command[i] == "AND" || command[i] == "and")
        {
            ptr->logic = AND;
            ptr->end = false;
            logic.push(ptr);
            i++;
        }
        else if (command[i] == "OR" || command[i] == "or")
        {
            ptr->logic = OR;
            ptr->end = false;
            logic.push(ptr);
            i++;
        }
        else
        {
            ptr->leftOperand = command[i];
            i++;
            if (command[i] == "==")
                ptr->opName = EQ;
            else if (command[i] == "<>")
                ptr->opName = NE;
            else if (command[i] == ">")
                ptr->opName = GT;
            else if (command[i] == "<")
                ptr->opName = LT;
            else if (command[i] == ">=")
                ptr->opName = GTE;
            else if (command[i] == "<=")
                ptr->opName = LTE;
            i++;
            ptr->rightOperand = command[i];
            ptr->end = true;
            atom.push(ptr);
            i++;
        }
    }
    condition_tree_t *ptr1, *ptr2;
    while (logic.size())
    {
        ptr = logic.top();
        logic.pop();
        ptr1 = atom.top();
        atom.pop();
        ptr2 = atom.top();
        atom.pop();
        ptr->left = ptr1;
        ptr->right = ptr2;
        atom.push(ptr);
    }
    ptr = atom.top();
    atom.pop();
    return ptr;
}

void Interpreter::debug()
{
    int i;
    printf("information type: %d\n" ,info.command);
    printf("tablename: %s\n",info.tableName.c_str() );
    for (i = 0; i < info.t.attrNum; i++)
        printf("%s %d\n",info.t.attributes[i].name.c_str(),info.t.attributes[i].length );
    if (info.command == SELECT)
    {
        printf("selected items:\n");
        for (i = 0; i < info.selectedItems.size();i++)
            printf("%s\n",info.selectedItems[i].c_str() );
        printf("selected table:\n");
        for (i = 0; i < info.selectedTable.size();i++)
            printf("%s\n",info.selectedTable[i].c_str() );
    }
}