# include "Interpreter.h"
# include <string.h>



bool Interpreter::inputCommand()
{
    getline(cin, input, ';');
    cin.get();
    return parseCommand();
}

bool Interpreter::parseCommand()
{
    int i, count = 0;
    clearInfo();
    size_t start, index, cutIndex;
    string seperators=" , \n";
    string cut = "()<>";
    string temp;

    start = input.find_first_not_of(seperators);

    // cut into pieces
    while (start != string::npos)
    {
        index = input.find_first_of(seperators,start);
        if (index == string::npos)
        {
            temp = (input.substr(start,index-start));
            while ((cutIndex = temp.find_first_of(cut)) != string::npos)
            {
                if (temp == "<>")
                    break;
                if (cutIndex != 0)
                    command.push_back(temp.substr(0,cutIndex));
                command.push_back(temp.substr(cutIndex,1));
                temp = temp.substr(cutIndex+1);
            }
            if (temp != "")
                command.push_back(temp);
            break;
        }
        else
        {
            temp = (input.substr(start,index-start));
            while ((cutIndex = temp.find_first_of(cut)) != string::npos)
            {
                if (temp == "<>")
                    break;
                if (cutIndex != 0)
                    command.push_back(temp.substr(0,cutIndex));
                command.push_back(temp.substr(cutIndex,1));
                temp = temp.substr(cutIndex+1);
            }
            if (temp != "")
                command.push_back(temp);
            start = input.find_first_not_of(seperators,index+1);
        }
    }
    /* for debug
    for (i = 0; i < command.size(); i++)
    {
        printf("%s %d\n", command[i].c_str(),command[i].length());
    }
    */
    
    for (i = 0; i < (int)command.size(); i++)
    {
        if (command[i] == "(")
            count++;
        if (command[i] == ")")
            count--;
        if (count < 0)
        {
            printf("Brackets doesn't match. Please check again.\n");
            return false;
        }
    }
    if (count != 0)
    {
        printf("Brackets doesn't match. Please check again.\n");
        return false;
    }

   // printf("%s\n",command[0].c_str() );
    if (!strcasecmp(command[0].c_str(), "create"))
        return parseCreate();
    else if (!strcasecmp(command[0].c_str(), "select"))
        return parseSelect();
    else if (!strcasecmp(command[0].c_str(), "insert"))
        return parseInsert();
    else if (!strcasecmp(command[0].c_str(), "delete"))
        return parseDelete();
    else if (!strcasecmp(command[0].c_str(), "drop"))
        return parseDrop();
    else if (!strcasecmp(command[0].c_str(), "update"))
        return parseUpdate();
    else if (!strcasecmp(command[0].c_str(), "quit"))
        return parseQuit();
    else if (!strcasecmp(command[0].c_str(), "help"))
        return parseHelp();
    else
    {
        printf("Command '%s' invalid. Please check again.\n",command[0].c_str());
        return false;
    }
}

info_t Interpreter::getInfo()
{
    return info;
}

bool Interpreter::parseCreate() // OK
{
    int count = 0;
    int i = 4;
    int length = 0;
    info.command = CREATE_TABLE;
    if (command.size() < 7)
    {
        printf("Syntax error in create command.\n");
        return false;
    }
    info.tableName = command[2];
    info.t.name = command[2];
    while (command[i] != ")")
    {
        if (i == (int)command.size())
        {
            printf("Syntax error in Create cmmand. (Forget the ')' ?)\n");
            return false;
        }
        info.t.attributes[count].name = command[i];
        i++;
        if (!strcasecmp(command[i].c_str(),"int"))
        {
            info.t.attributes[count].type = INT;
            info.t.attributes[count].length = 4;
            info.t.attributes[count].isPrimary = false;
            length += 4;
        }
        else if (!strcasecmp(command[i].c_str(),"char"))
        {
            info.t.attributes[count].type = CHAR;
            info.t.attributes[count].length = 32;
            info.t.attributes[count].isPrimary = false;
            length += 32;
        }
        else
        {
            printf("The type '%s' is not supported. Please check again.\n",command[i].c_str() );
            info.command = NONE;
            return false;
        }
        i++;
        if (!strcasecmp(command[i].c_str(),"Primary"))
        {
            info.t.attributes[count].isPrimary = true;
            i++;
            i++;
        }
        if (!strcasecmp(command[i].c_str(),"default"))
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
    return true;
}

bool Interpreter::parseHelp()   // OK
{
    info.command = HELP;
    return true;
}

bool Interpreter::parseQuit()   //OK
{
    info.command = QUIT;
    return true;
}

bool Interpreter::parseDrop()   //OK
{
    info.command = DROP_TABLE;
    if (command.size() != 3)
    {
        printf("Syntax error in drop command. Please check again\n");
        return false;
    }
    info.tableName = command[2];
    return true;
}

bool Interpreter::parseSelect() //OK
{
    info.command = SELECT;
    int i = 1;
    while (strcasecmp(command[i].c_str(),"from"))
    {
        info.selectedItems.push_back(command[i]);
        i++; 
        if (i == (int)command.size())
        {
            printf("Systax error: No talbe specified\n");
            return false;
        }   
    }
    if (i == 1)
    {
        printf("No columns selected. Please check again\n");
        return false;
    }
    i++;
    if (i == (int)command.size())
    {
        printf("Systax error: No talbe specified\n");
        return false;

    }
    while (strcasecmp(command[i].c_str(),"where"))
    {
        info.selectedTable.push_back(command[i]);
        i++;
        if (i == (int)command.size())
        {
            info.tree = NULL;
            return true;
        }
    }
    if (!strcasecmp(command[i].c_str(),"where"))
    {
        info.tree = makeTree(i+1);
        if (info.tree == NULL)
        {
            return false;
        }
    }
    return true;
}

bool Interpreter::parseDelete() //OK
{
    info.command = DELETE;
    if (command.size() < 3)
    {
        printf("Syntax error in delete command. Please check again\n");
        return false;
    }
    info.tableName = command[2];
    if (command.size() == 3)
    {
        info.tree = NULL;
    }
    else
    {
        info.tree = makeTree(4);
        if (info.tree == NULL)
            return false;
    }
    return true;
}

void Interpreter::clearInfo()
{
    command.clear();
    info.command = NONE;
    info.tableName = "";
    if (info.tree)
        clearTree(info.tree);
    info.tree = NULL;
    info.selectedItems.clear();
    info.selectedTable.clear();
    info.insertItems.clear();
}

bool Interpreter::parseInsert()  //OK
{
    //printf("reach here\n");
    info.command = INSERT;
    if (command.size() < 3)
    {
        printf("Systax error. Need more input\n");
        return false;
    }
    info.tableName = command[2];
    int index1 ,index2;
    index1 = index2 = 4;
    while (command[index2] != "(")
    {
        index2++;
        if (index2 == (int)command.size())
        {
            printf("Systax error in insert command. Please check again.\n");
            return false;
        }
    }
    index2++;
    while (command[index1] != ")")
    {
        //printf("%s %s\n",command[index1].c_str(),command[index2].c_str() );
        info.insertItems.insert(map<string,string>::value_type(command[index1],command[index2]));
        index1++;
        index2++;
        //printf("%d %d\n",index1, index2 );
        if (index2 == (int)command.size())
        {
            printf("Systax error in insert command. Please check again.\n");
            return false;
        }
    }
    return true;
}

bool Interpreter::parseUpdate() //OK
{
    info.command = UPDATE;
    if (command.size() == 1)
    {
        printf("No table specified. Please check again\n");
        return false;
    }
    info.tableName = command[1];
    if (command.size() <= 6 )
    {
        printf("Systax error. Update command needs more input\n");
        return false;
    }
    int index1 = 3;
    int index2 = 5;
    info.updateItems.insert(map<string,string>::value_type(command[index1],command[index2]));
    if (command.size() != 6)
    {
        if (!strcasecmp(command[6].c_str(),"where"))
        {
            info.tree = makeTree(7);
            if (info.tree == NULL)
                return false;
        }
    }
    return true;
}

condition_tree_t * Interpreter::makeTree(int index)
{
    std::stack<condition_tree_t *> atom;
    std::stack<condition_tree_t *> logic;
    condition_tree_t * ptr;
    int i;
    i = index;
    while (i < (int)command.size())
    {
        ptr = new condition_tree_t();
        if (!strcasecmp(command[i].c_str(),"and"))
        {
            ptr->logic = AND;
            ptr->end = false;
            logic.push(ptr);
            i++;
        }
        else if (!strcasecmp(command[i].c_str(),"or"))
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
            if (i == (int)command.size())
            {
                printf("Syntax error in condition expression.\n");
                return NULL;
            }
            ptr->rightOperand = command[i];
            ptr->end = true;
            if (isdigit(ptr->leftOperand[0]))
            {
                string t = ptr->leftOperand;
                ptr->leftOperand = ptr->rightOperand;
                ptr->rightOperand = t;
                if (ptr->opName == GT)
                    ptr->opName = LT;
                else if (ptr->opName == LT)
                    ptr->opName = GT;
                else if (ptr->opName == GTE)
                    ptr->opName = LTE;
                else if (ptr->opName == LTE)
                    ptr->opName = GTE;
            }
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
    if (info.command == CREATE_TABLE)
    {
        for (i = 0; i < info.t.attrNum; i++)
            printf("%s %d\n",info.t.attributes[i].name.c_str(),info.t.attributes[i].length );
    }
    if (info.command == SELECT)
    {
        printf("selected items:\n");
        for (i = 0; i < (int)info.selectedItems.size();i++)
            printf("%s\n",info.selectedItems[i].c_str() );
        printf("selected table:\n");
        for (i = 0; i < (int)info.selectedTable.size();i++)
            printf("%s\n",info.selectedTable[i].c_str() );
        printf("Condition tree:\n");
        showConditionTree(info.tree);

    }
    if (info.command == INSERT)
    {
        std::map<string, string>::iterator iter = info.insertItems.begin();
        while (iter != info.insertItems.end())
        {
            printf("%s %s\n",iter->first.c_str(),iter->second.c_str() );
            iter++;
        }
    }
    if (info.command == UPDATE)
    {
        std::map<string, string>::iterator iter = info.updateItems.begin();
        while (iter != info.updateItems.end())
        {
            printf("%s %s\n",iter->first.c_str(),iter->second.c_str() );
            iter++;
        }
        showConditionTree(info.tree);
    }
    if (info.command == DELETE)
    {
        showConditionTree(info.tree);
    }
    if (info.command == DROP_TABLE)
    {

    }
}

void Interpreter::showConditionTree(condition_tree_t * root)
{
    if (root == NULL)
        return;
    if (root->end)
    {
        printf("%s %d %s\n",root->leftOperand.c_str(),root->opName,root->rightOperand.c_str() );
    }
    else
    {
        printf("%d\n", root->logic );
        showConditionTree(root->left);
        showConditionTree(root->right);
    }
}

void Interpreter::clearTree(condition_tree_t * root)
{
    if (!root->end)
    {
        clearTree(root->left);
        clearTree(root->right);

    }
    root->left = NULL;
    root->right = NULL;
    delete root;
}