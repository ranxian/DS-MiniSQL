/*
 * Record.h
 */

#ifndef RECORD_H
#define RECORD_H

#include "MiniSQL.h"

class Record
{
public:
    Record(){};
    ~Record(){};
    int Insert(info_t & insert_info);
    void Delete(info_t & delete_info, index_node_t & index);
    void Update(info_t & update_info, index_node_t & index);
    record_t *Select(info_t & select_info);
    void Print(record_t *record, info_t & info);                                 //输出一条记录
    void PrintHead(table_t & table);
private:
    /* 用来某一条记录是否符合条件树的要求，返回值为1则表示符合要求，返回0表示不符合要求，返回-1表示
    某条记录不含要求的字段值，不需判断。offset为某条记录首地址偏移 */
    int Judge(condition_tree_t * tempCondition, int offset, table_t table, ifstream &input);

    /* 根据表信息和字段名返回字段值类型等信息，0表示整形，1表示字符串，-1表示不存在此字段，Offset表示
    所查找字段相对与当前记录首地址的偏移，attriLength表示这个字段值的字节数 */
    int getInfo(table_t table, string infoName, int &Offset, int &attriLength);

};

#endif