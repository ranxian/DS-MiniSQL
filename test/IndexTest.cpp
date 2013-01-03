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
    index_node_t insertNode[10], res;
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

    condition_tree_t *cNode = new condition_tree_t;
    cNode->leftOperand = "学号";

    // 建立索引
    cout << "---建立索引：" << endl;
    IndexManager.createIndex("Persons", "学号", attr);
    cout << endl;

    // 插入索引项
    cout << "---插入索引项：" << endl;
    IndexManager.insertIndex("Persons", "学号", insertNode[0]);
    IndexManager.insertIndex("Persons", "学号", insertNode[1]);
    IndexManager.insertIndex("Persons", "学号", insertNode[2]);
    cout << endl;

    IndexManager.debugPrint("Persons", "学号");

    // 查找索引项
    cout << "---查找索引项：" << endl;

    cNode->opName = EQ;
    cNode->rightOperand = "1100012957";
    IndexManager.selectIndex("Persons", cNode, &res);
    printNode(&res);

    cNode->opName = NE;
    cNode->rightOperand = "1100012957";
    IndexManager.selectIndex("Persons", cNode, &res);
    printNode(&res);

    cNode->opName = GT;
    cNode->rightOperand = "1100012957";
    IndexManager.selectIndex("Persons", cNode, &res);
    printNode(&res);

    cNode->opName = LT;
    cNode->rightOperand = "1100099999";
    IndexManager.selectIndex("Persons", cNode, &res);
    printNode(&res);

    cNode->opName = GTE;
    cNode->rightOperand = "1100012957";
    IndexManager.selectIndex("Persons", cNode, &res);
    printNode(&res);

    cNode->opName = LTE;
    cNode->rightOperand = "1100012957";
    IndexManager.selectIndex("Persons", cNode, &res);
    printNode(&res);
    cout << endl;

    // 删除索引项
    cout << "---删除索引项：" << endl;
    IndexManager.deleteIndex("Persons", "学号", "1100012957");
    cout << endl;

    // 更新索引项
    cout << "---更新索引项：" << endl;
    IndexManager.updateIndex("Persons", "学号", "1100099999", "1100199999");
    cout << endl;

    IndexManager.debugPrint("Persons", "学号");

    // 查找索引项
    cout << "---查找索引项：" << endl;
    cNode->opName = GTE;
    cNode->rightOperand = "1100012949";
    IndexManager.selectIndex("Persons", cNode, &res);
    printNode(&res);
    cout << endl;

    // 恢复一条索引
    IndexManager.insertIndex("Persons", "学号", insertNode[2]);
    
    IndexManager.debugPrint("Persons", "学号");

    // OR 合并索引列表
    index_node_t ORres, ORres1, ORres2;
    cout << "---OR 合并索引列表：" << endl;

    cNode->opName = GTE;
    cNode->rightOperand = "1100012999";
    IndexManager.selectIndex("Persons", cNode, &ORres);
    printNode(&ORres);

    cNode->opName = LTE;
    cNode->rightOperand = "1100012950";
    IndexManager.selectIndex("Persons", cNode, &ORres1);
    printNode(&ORres1);

    index_node_t **tmp = new index_node_t * [2];
    tmp[0] = &ORres;
    tmp[1] = &ORres1; 
    IndexManager.mergeIndexOR(tmp, 2, &ORres2);
    printNode(&ORres2);
    delete [] tmp;
    cout << endl;

    // 恢复一条索引
    IndexManager.updateIndex("Persons", "学号", "1100012950", "1100012957");

    // AND 合并索引列表
    index_node_t ANDres, ANDres1, ANDres2;
    cout << "---AND 合并索引列表：" << endl;

    cNode->opName = GTE;
    cNode->rightOperand = "1100012957";
    IndexManager.selectIndex("Persons", cNode, &ANDres);
    printNode(&ANDres);

    cNode->opName = EQ;
    cNode->rightOperand = "1100012957";
    IndexManager.selectIndex("Persons", cNode, &ANDres1);
    printNode(&ANDres1);

    tmp = new index_node_t * [2];
    tmp[0] = &ANDres;
    tmp[1] = &ANDres1; 
    IndexManager.mergeIndexAND(tmp, 2, &ANDres2);
    printNode(&ANDres2);
    delete [] tmp;
    cout << endl;

    // 尝试搜索具有相同关键码的多个索引项
    index_node_t selRes;
    cout << "---搜索具有相同关键码的多个索引项：" << endl;
    IndexManager.insertIndex("Persons", "学号", insertNode[2]);
    IndexManager.insertIndex("Persons", "学号", insertNode[2]);
    IndexManager.insertIndex("Persons", "学号", insertNode[2]);

    cNode->opName = EQ;
    cNode->rightOperand = "1100099999";
    IndexManager.selectIndex("Persons", cNode, &selRes);
    printNode(&selRes);

    // 删除一条索引后再搜索
    IndexManager.deleteIndex("Persons", "学号", "1100099999");

    IndexManager.debugPrint("Persons", "学号");

    cNode->opName = GT;
    cNode->rightOperand = "1100012956";
    IndexManager.selectIndex("Persons", cNode, &selRes);
    printNode(&selRes);
    cout << endl;

    // 更新索引项
    cout << "---更新索引项：" << endl;
    IndexManager.updateIndex("Persons", "学号", "1100099999", "1100199999");
    cout << endl;

    IndexManager.debugPrint("Persons", "学号");

    return 0;
}