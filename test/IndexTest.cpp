#include "../src/MiniSQL.h"
#include "../src/Index.h"

void printNode(index_node_t * node)
{
    while (true)
    {
        cout << "Index Node: " << endl
            << " value:" << node->value << endl
            << " offset:" << node->offset << endl;
        if (node->nextNode != NULL)
            node = node->nextNode;
        else 
            break;
    }
    cout << endl;
}

int main()
{
    Index IndexManager;
    index_node_t insertNode[10], res, res2, res3;
    insertNode[0].value = "1100012957";
    insertNode[0].offset = 16;
    insertNode[1].value = "1100012950";
    insertNode[1].offset = 0;
    insertNode[2].value = "1100099999";
    insertNode[2].offset = 8;

    attr_t attr;
    attr.name = "学号";
    attr.isPrimary = true;
    attr.length = 8;
    attr.type = INT;

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
    IndexManager.selectIndex("Persons", "学号", "0", "9999999999", &res);
    printNode(&res);
    IndexManager.selectIndex("Persons", "学号", "1100012957", "1100012957", &res);
    printNode(&res);
    IndexManager.selectIndex("Persons", "学号", "1100012952", "1100012958", &res);
    printNode(&res);
    IndexManager.selectIndex("Persons", "学号", "1100012952", "1100099999", &res);
    printNode(&res);
    IndexManager.selectIndex("Persons", "学号", "ZHAODIAO", "ZHAODIAO", &res);
    printNode(&res);
    cout << endl;

    // 删除索引项
    cout << "删除索引项：" << endl;
    IndexManager.deleteIndex("Persons", "学号", "1100099999");
    cout << endl;

    // 更新索引项
    cout << "更新索引项：" << endl;
    IndexManager.updateIndex("Persons", "学号", "1100012957", "1100012958");
    cout << endl;

    // 查找索引项
    cout << "查找索引项：" << endl;
    IndexManager.selectIndex("Persons", "学号", "1100012958", "1100012958", &res);
    printNode(&res);
    cout << endl;

    // 合并索引列表
    IndexManager.insertIndex("Persons", "学号", insertNode[2]);
    cout << "合并索引列表：" << endl;
    IndexManager.selectIndex("Persons", "学号", "1100012950", "1100012957", &res);
    printNode(&res);
    IndexManager.selectIndex("Persons", "学号", "1100012957", "1100099999", &res2);
    printNode(&res2);
    cout << endl;
    index_node_t **tmp = new index_node_t * [2];
    tmp[0] = &res;
    tmp[1] = &res2; 
    IndexManager.mergeIndex(tmp, 2, &res3);
    printNode(&res3);
    delete [] tmp;
    cout << endl;




}