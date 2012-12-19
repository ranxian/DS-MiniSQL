#include "../src/MiniSQL.h"
#include "../src/Index.h"

void printNode(index_node_t & node)
{
    cout << "Index Node: " << endl
        << " value:" << node.value << endl
        << " offset:" << node.offset << endl;

}

int main()
{
    Index IndexManager;
    static index_node_t insertNode[10], res, res2;
    insertNode[0].value = "1100012957";
    insertNode[0].offset = 16;
    insertNode[1].value = "1100012950";
    insertNode[1].offset = 0;
    insertNode[2].value = "9999999999";
    insertNode[2].offset = 8;

    static attr_t attr;
    attr.name = "学号";
    attr.isPrimary = true;
    attr.length = 8;
    attr.type = CHAR;

    // 建立索引
    cout << "建立索引：" << endl;
    IndexManager.createIndex("Persons", "学号", attr);
    cout << endl;

    // 插入索引项
    cout << "插入索引项：" << endl;
    IndexManager.insertIndex("Persons", "学号", insertNode[0]);
    IndexManager.insertIndex("Persons", "学号", insertNode[1]);
    IndexManager.insertIndex("Persons", "学号", insertNode[2]);
    cout << endl;

    // 查找索引项
    cout << "查找索引项：" << endl;
    IndexManager.selectIndex("Persons", "学号", "1100012957", &res);
    printNode(res);
    IndexManager.selectIndex("Persons", "学号", "9999999999", &res);
    printNode(res);
    cout << endl;

    // 删除索引项
    cout << "删除索引项：" << endl;
    IndexManager.deleteIndex("Persons", "学号", "9999999999");
    cout << endl;

    // 更新索引项
    cout << "更新索引项：" << endl;
    IndexManager.updateIndex("Persons", "学号", "1100012957", "1100012958");
    cout << endl;

    // 查找索引项
    cout << "查找索引项：" << endl;
    IndexManager.selectIndex("Persons", "学号", "1100012958", &res);
    printNode(res);
    cout << endl;

}