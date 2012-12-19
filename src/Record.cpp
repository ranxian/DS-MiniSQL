/*
Record.cpp
print和printhead分别干嘛
select从何搞起
如何输入(所有空的地方输入"oop",占满字节数)
*/



#include "Record.h"


/* 所有的文件的名字是表的名字后面加后缀.rec */

/* Insert函数返回最后一条记录相对文件头的偏移量 */
int Record::Insert(info_t & insert_info)
{
    /* 根据表明生成文件名 */
    string Filename;
    Filename = "\"" + insert_info.tableName + ".rec\"";

    //filename即为表名处理过的字符串
    char *filename = (char *)Filename.c_str();                  
    int i;

    ofstream output;
    output.open(filename, ios::app|ios::binary|ios::out);
    map<string, string> ::iterator iter;
    //对这个表中每个字段进行遍历，看是否在map对中某个字段的数据
    for (i=0; i<insert_info.t.attrNumber; i++)                  
    {                                                         
        attr_t target = insert_info.t.attributes[i];
        for (iter=insert_info.insertItems.begin(); iter!=insert_info.insertItems.end();
            iter++)
        {
            //如果某个字段在map中存在
            if (target.name == iter->first)                      
            {
                 //字段的值（string类型）
                string temp = iter->second;                     
                output.write((char *)temp.c_str(), target.length);
                break;
            }
        }
        if (iter != insert_info.insertItems.end())               
            continue;
        
        //如果某个字段不在map中，则输入空的字节数
        else                                                     
        {
            string hollow = "oop";
            output.write((char *)hollow.c_str(), target.length);
        }


    }

}

/* 将所有的字段值都改为oop */
void Record::Delete(info_t & delete_info, index_node_t & index)         
{
    string Filename;
    Filename = "\"" + delete_info.tableName + ".rec\"";
    char *filename = (char *)Filename.c_str();  
    ofstream output;
    output.open(filename, ios::binary|ios::app|ios::out);
    //定位到相应记录
    output.seekp(index.offset, ios::beg);                     
    table_t target = delete_info.t;
    int i;
    string temp = "oop";
     //对所有字段都写入oop串
    for (i=0; i<target.attrNumber; i++)                      
    {
        output.write((char *)temp.c_str(), target.attributes[i].length);
    }
}


/* 基本处理同insert */
void Record::Update(info_t & update_info, index_node_t & index)
{
    string Filename;
    Filename = "\"" + update_info.tableName + ".rec\"";
    char *filename = (char *)Filename.c_str();  
    ofstream output;
    output.open(filename, ios::binary|ios::app|ios::out);

     //定位到相应的记录
    output.seekp(index.offset, ios::beg);                      
    map<string, string> ::iterator iter;
    int i;
    for (i=0; i<update_info.t.attrNumber; i++)                  
    {                                                           
        attr_t target = update_info.t.attributes[i];
        for (iter=update_info.updateItems.begin(); iter!=update_info.updateItems.end();
            iter++)
        {
            if (target.name == iter->first)                      
            {
                string temp = iter->second;                      
                output.write((char *)temp.c_str(), target.length);
                break;
            }

        }

    }

    
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