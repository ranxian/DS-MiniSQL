/*
 * Record.h
 */

#ifndef RECORD_H
#define RECORD_H

#include "MiniSQL.h"


class Record
{
public:
    Record();
    ~Record(){};
    int Insert(info_t & insert_info);
    void Delete(info_t & delete_info, index_node_t & index);
    void Update(info_t & update_info, index_node_t & index);
    record_t Select(info_t & select_info);
    void Print(record_t *record);                                 //输出一条记录
    void PrintHead(table_t & table);

};

#endif