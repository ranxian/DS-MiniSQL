/*
 * Record.h
 */


#include<iostream>
using namespace std;

typedef struct 
{   
    attrtype_t type;
    string str_value;
    int int_value;
    record_t *next;
} record_t;

class Record
{
public:
    Record();
    ~Record(){};
    void Insert(info_t & insert_info);
    void Delete(info_t & delete_info, index_node_t & index);
    void Update(info_t & update_info, index_node_t & index);
    record_t *Select(info_t & select_info);
    void Print(record_t *record);
    void PrintHead(table_t & table);
private:                              
}