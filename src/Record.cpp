/*
Record.cpp

未知：
lastInsert
totalLenth
*/

#include<iostream>
#include<string>
#include<fstream>
#include "minisql.h"


/* 所有的文件的名字是表的名字后面加后缀.rec */

/* Insert函数返回最后一条记录相对文件头的偏移量 */
int Record::Insert(info_t & insert_info)
{
    /* 根据表明生成文件名 */
    char filename[40];
    int i;
    int tableLength = insert_info.t.name.length();
    filename[0] = '"';
    for (i=1; i<=tableLength; i++)
    {
        filename[i] = insert_info.t.name[i-1];
    }
    filename[tableLength + 1] = '.';
    filename[tableLength + 2] = 'r';
    filename[tableLength + 3] = 'e';
    filename[tableLength + 4] = 'c';
    filename[tableLength + 5] = '"';
    filename[tableLength + 6] = '\0';
    ofstream output;
    output.open(filename,ios::app|ios::binary|ios::out);
    map<string, string> ::iterator iter;
    for (iter=insert_info.insertItems)

    





}

void Record::Delete(info_t & delete_info, index_node_t & index)
{

}

void Record::Update(info_t & update_info, index_node_t & index)
{

}


record_t  Record::Select(info_t & select_info)
{

}

void Record::Print(record_t * record)
{

}


void Record::PrintHead(table_t & table)
{

}