/*
Record.cpp
*/



#include "Record.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
/* 所有的文件的名字是表的名字后面加后缀.rec */


/* 根据字段名返回字段值类型，0表示整形，1表示字符串，-1表示没有此字段,同时设置
某个字段相对于每一条记录初始位置的偏移量，为offset */
int Record::getInfo(table_t table, string infoName, int &Offset, int &attriLength)
{
    int i;
    Offset = 0;
    attriLength = 0;
    for (i=0; i<table.attrNum; i++)
    {
        if (i != 0)
        {
            Offset += table.attributes[i - 1].length;
        }
        
        if (table.attributes[i].name == infoName)
        {
            attriLength = table.attributes[i].length;
            if (table.attributes[i].type == CHAR)
                return 1;
            else if (table.attributes[i].type == INT)
                return 0;
        }
    }

    return -1;
}

/* 用来某一条记录是否符合条件树的要求，返回值为1则表示符合要求，返回0表示不符合要求，返回-1表示
某条记录不含要求的字段值，不需判断。offset表示某条记录的首地址偏移，input为传入的读文件流 */

int Record::Judge(condition_tree_t * tempCondition, int offset, table_t table, ifstream &input)
{
    
    //如果某一个子树返回-1，直接不用判断，一层层向上返回-1
    if ((Judge(tempCondition->left, offset, table, input) == -1) || 
        (Judge(tempCondition->right, offset, table, input) == -1))
        return -1;

    //如果不是叶节点
    else if(!tempCondition->end)
    {
        //如果逻辑符号为与的情况
        if (tempCondition->logic == AND)
            return (Judge(tempCondition->left, offset, table, input) & 
                Judge(tempCondition->right, offset, table, input));

        //如果逻辑符号为或的情况
        else return (Judge(tempCondition->left, offset, table, input) | 
                Judge(tempCondition->right, offset, table, input));
    }
    //剩下的情况就认为是叶节点，即判断单元
    else
    {
        
        //此变量用来标记某个字段之相对于这个记录首地址的偏移，即attriOffset>=0 && 
        //attriOffset <= recordLength-最后一条记录的长度
        int attriOffset = 0;

        //此变量用来记录一个字段值的字节大小
        int attriLength = 0;
        //不管何种情况，先以字符串方式读出，判断是否为空（“oop”）
        char outChar[MAX_CHAR_LENGTH];
        memset(outChar, 0, sizeof outChar);
        
        //剩下的情况字段值都不为空
        //要判断字符串的情况,此时应该只有等于和不等于两种情况？
        if (getInfo(table, tempCondition->leftOperand, attriOffset, attriLength) == 1)
        {
            //定位到相应的字段值首地址
            input.seekg(offset + attriOffset, ios::beg);
            input.read((char *)outChar, attriLength);
            //将读出的字符串变为string类
            string out = outChar;
            if (out == "oop")
                return -1;
            
            switch(tempCondition->opName)
            {
                //判断字符串相等情况
                case EQ:
                    if (outChar == tempCondition->rightOperand)
                        return 1;
                    else
                        return 0;
                    break;

                //判断字符串不等情况
                default:
                    if(outChar == tempCondition->rightOperand)
                        return 0;
                    else 
                        return 1;
            }
        }
        //此种情况为比较整型变量
        else if(getInfo(table, tempCondition->leftOperand, attriOffset, attriLength) == 0)
        {
            //定位到相应的字段值首地址
            input.seekg(offset + attriOffset, ios::beg);
            input.read((char *)outChar, attriLength);
            //将读出的字符串变为string类
            string out = outChar;
            if (out == "oop")
                return -1;
            //将字段值取出，以整形存储
            int outInt = 0;
            //定位到相应的字段值首地址
            input.seekg(offset + attriOffset, ios::beg);

            input.read((char *)&outInt, attriLength);
            //将右值rightOperand转换为整型值
            char *rightNum = (char *)tempCondition->rightOperand.c_str();
            int rightnum = atoi(rightNum);

            switch (tempCondition->opName)
            {
                case EQ:
                    if (outInt == rightnum)
                        return 1;
                    else
                        return 0;
                    break;

                case NE:
                    if (outInt != rightnum)
                        return 1;
                    else 
                        return 0;
                    break;

                case GT:
                    if (outInt > rightnum)
                        return 1;
                    else 
                        return 0;
                    break;

                case LT:
                    if (outInt < rightnum)
                        return 1;
                    else 
                        return 0;
                    break;

                case GTE:
                    if (outInt >= rightnum)
                        return 1;
                    else
                        return 0;
                    break;

                default:
                    if (outInt <= rightnum)
                        return 1;
                    else 
                        return 0;
            }
        }
        //此种情况说明它的左操作数（及字段名）根本不存在
        else 
            return -1;
    }
    return -1;
}

/* Insert函数返回最后一条记录相对文件头的偏移量 */
int Record::Insert(info_t & insert_info)
{
    
    /* 根据表明生成文件名 */
    string Filename;
    Filename = "../data/" + insert_info.tableName + ".rec";

    //filename即为表名处理过的字符串
    char *filename = (char *)Filename.c_str();                  
    int i;

    ofstream output;
    output.open(filename, ios::app|ios::binary|ios::out);
    //此时记录下文件的偏移
    int offset = (int)output.tellp();
    map<string, string> ::iterator iter;

    //对这个表中每个字段进行遍历，看是否在map对中某个字段的数据
    for (i=0; i<insert_info.t.attrNum; i++)                  
    {                                                         
        attr_t target = insert_info.t.attributes[i];
        for (iter=insert_info.insertItems.begin(); iter!=insert_info.insertItems.end();
            iter++)
        {
            //如果某个字段在map中存在
            if (target.name == iter->first)                      
            {
                 //字段的值本为string类型，先转换为char类型
                char *va = (char *)iter->second.c_str();
                //如果是int类型，就将string类型转换为int型，但必须保持数据大小为4字节
                if (target.type == INT)
                {
                    int value = atoi(va);
                    output.write((char *)&value, 4);
                }
                //如果是char类型，就将string转换为char
                else 
                {
                    output.write(va, target.length);
                }
                break;
            }
        }
        //这种情况是找到对应字段的情况
        if (iter != insert_info.insertItems.end())               
            continue;
        
        //如果某个字段不在map中，则输入空的字节数
        else                                                     
        {
            string hollow = "oop\0";
            output.write((char *)hollow.c_str(), target.length);
        }


    }

    return offset;

}

/* 将所有的字段值都改为oop */
void Record::Delete(info_t & delete_info, index_node_t & index)         
{
    string Filename;
    Filename = "../data/" + delete_info.tableName + ".rec";
    char *filename = (char *)Filename.c_str();  
    ofstream output;
    output.open(filename, ios::binary|ios::app|ios::out);
    //定位到相应记录
    output.seekp(index.offset, ios::beg);                     
    table_t target = delete_info.t;
    int i;
    string temp = "oop";
     //对所有字段都写入oop串
    for (i=0; i<target.attrNum; i++)                      
    {
        output.write((char *)temp.c_str(), target.attributes[i].length);
    }
}


/* 基本处理同insert */
void Record::Update(info_t & update_info, index_node_t & index)
{
    string Filename;
    Filename = "../data/" + update_info.tableName + ".rec";
    char *filename = (char *)Filename.c_str();  
    ofstream output;
    output.open(filename, ios::binary|ios::app|ios::out);

     //定位到相应的记录
    output.seekp(index.offset, ios::beg);                      
    map<string, string> ::iterator iter;
    int i;
    for (i=0; i<update_info.t.attrNum; i++)                  
    {                                                           
        attr_t target = update_info.t.attributes[i];
        for (iter=update_info.updateItems.begin(); iter!=update_info.updateItems.end();
            iter++)
        {
            //找到对应字段
            if (target.name == iter->first)                      
            {
                char *va = (char *)iter->second.c_str();
                if (target.type == INT)
                {
                    int value = atoi(va);
                    output.write((char *)&value, 4);
                }
                else
                {
                    output.write(va, target.length);
                }
                break;
            }

        }

    }

    
}


record_t  *Record::Select(info_t & select_info)
{
    //先打开对应的文件
    string Filename;
    Filename = "../data/" + select_info.tableName + ".rec";
    char *filename = (char *)Filename.c_str();  
    ifstream input;
    input.open(filename, ios::binary|ios::app|ios::in);


    //curEnd表示文件末位距离文件首的偏移
    int curEnd = (int) input.tellg();
    //建立一个链表，链表节点为一条条符合条件的完整的记录，head为整个链表的头指针
    //返回值为head的next指针
    record_t *head = new record_t;
    head->next = NULL;
    record_t *move = head;
    //如果出现一个符合要求的记录，就包装成一个结构体record_t,并使move->next指向它
    //然后移动move，即move = move->next

    //condition指针指向整个条件树的根节点
    condition_tree_t *condition = select_info.tree;
    int i,j;
    


    //i表示每一条记录的首地址偏移
    for(i=0; i!=curEnd; i+=select_info.t.recordLength)
    {
        

        if(Judge(condition, i, select_info.t, input) == 1)
        {
            
            
            //以下部分为将一条记录打包成record_t的工作

            //将文件读指针移动到记录头
            input.seekg(i, ios::beg);
            move->next = new record_t;
            move = move->next;
            move->next = NULL;
            move->value = new value_t;
            value_t * valueMove = move->value;
            for (j=0; j<select_info.t.attrNum; j++)
            {
                
                if (j != 0)
                {
                    valueMove->next = new value_t;
                    valueMove = valueMove->next;
                }
                //不管何种情况，先以字符串方式读出，判断是否为空（“oop”）
                char outChar[MAX_CHAR_LENGTH];
                memset(outChar, 0, sizeof outChar);
                input.read((char *)outChar, select_info.t.attributes[j].length);
                //将读出的字符串变为string类
                string out = outChar;

                //如果某字段值为空
                if (out == "oop")
                {
                    valueMove->type = NOATTR;

                }
                
                //字段值为字符串类型   
                else if (select_info.t.attributes[j].type == CHAR)
                {
                    valueMove->type = CHAR;
                    valueMove->str_value = out;

                }
                
                //字段值为整形类型
                else 
                {
                    valueMove->type = INT;
                    int intValue = atoi(outChar);
                    valueMove->int_value = intValue;
                }
                valueMove->next = NULL;
                



            }



               
        }
    }

    return head->next;

}

/* 输出一条记录 */
void Record::Print(record_t * record)
{
    value_t *link = record->value; 
    while (link != NULL)
    {
        //如果记录为空
        if (link->type == NOATTR)
        {
            cout << "NULL ";
        }
        else if (link->type == CHAR)
        {
            cout << link->str_value << " ";
        }
        else
        {
            cout << link->int_value << " ";
        }
        link = link->next;
    }
    cout << endl;
}

/* 用来输出一个表的字段信息 */
void Record::PrintHead(table_t & table)
{

    int i;
    for (i=0; i<table.attrNum; i++)
    {
        cout << table.attributes[i].name << " ";
    } 
    cout << endl;


}