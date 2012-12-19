#include "../src/MiniSQL.h"
#include "../src/Index.h"

int main()
{
    Index IndexManager;
    static index_node_t insertNode[10], res;
    insertNode[0].value = "1100012957";
    insertNode[0].offset = 16;
    insertNode[1].value = "1100012950";
    insertNode[1].offset = 0;
    insertNode[2].value = "110001295x";
    insertNode[2].offset = 8;


    static attr_t attr;
    attr.name = "学号";
    attr.isPrimary = true;
    attr.length = 8;
    attr.type = CHAR;

    // 建立索引
    IndexManager.createIndex("Persons", "学号", attr);

    // 插入索引项
    IndexManager.insertIndex("Persons", "学号", insertNode[0]);
    // IndexManager.insertIndex("Persons", "学号", insertNode[1]);
    // IndexManager.insertIndex("Persons", "学号", insertNode[2]);

    // 
}