#include "Index.h"

int Index::selectIndex(string tableName, string indexName, string valueFrom, string valueTo, index_node_t *res)
{
    fstream fin;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fin.open(file.c_str(), ios::in | ios::binary);

    // 读出索引头
    index_head_t idxHd;
    readHead(fin, idxHd);

    // 查找索引
    // 二分查找到要求索引的起始、结束地址
    int from;
    int to;
    // 如果是要取出所有索引的话
    if (valueFrom == "ZHAODIAO" && valueTo == "ZHAODIAO")
    {
        from = IDXHEAD_SIZE_IN_FILE;
        to = IDXHEAD_SIZE_IN_FILE + (idxHd.recNum - 1) * IDXNODE_SIZE_IN_FILE;
    }
    // 否则
    else
    {
        // 如果查找范围最小值不比第一个索引值大，那么从第一个索引开始收集
        index_node_t firstNode;
        fin.seekg(IDXHEAD_SIZE_IN_FILE);
        readNode(fin, firstNode);
        if (!lessThan(firstNode.value, valueFrom, idxHd.attr.type))
        {
            from = IDXHEAD_SIZE_IN_FILE;
        }
        // 否则，进行二分查找
        else
        {
            fin.seekg(IDXHEAD_SIZE_IN_FILE);
            from = biSearchFrom(fin, 1, idxHd.recNum, valueFrom, idxHd.attr.type);
        }
        // 如果查找范围最大值不比最后一个索引值小，那么收集到最后一个索引
        index_node_t lastNode;
        fin.seekg(IDXHEAD_SIZE_IN_FILE + (idxHd.recNum - 1) * IDXNODE_SIZE_IN_FILE);
        readNode(fin, lastNode);
        if (!lessThan(valueTo, lastNode.value, idxHd.attr.type))
        {
            to = IDXHEAD_SIZE_IN_FILE + (idxHd.recNum - 1) * IDXNODE_SIZE_IN_FILE;
        }
        // 否则，进行二分查找
        else
        {
            fin.seekg(IDXHEAD_SIZE_IN_FILE);
            to = biSearchTo(fin, 1, idxHd.recNum, valueTo, idxHd.attr.type);
        }
    }

    // cout << "--------------from: " << from << " to: " << to << endl;
    
    // 将所有索引项加入到 res 链表中
    index_node_t *cur = res;
    cur->nextNode = NULL;
    // 更新写指针到第一个索引的起始地址
    fin.seekg(from);
    while (true)
    {
        // 将当前索引项加入链表
        readNode(fin, *cur);
        // 如果还有下一个索引项就申请空间
        if ((int)fin.tellg() <= to)
        {
            cur->nextNode = new index_node_t;
            cur = cur->nextNode;
            cur->nextNode = NULL;
        }
        // 如果读到最后一个索引项了 退出循环
        else
        {
            break;
        }
    }

    fin.close();

    // 成功返回 0
    return 0;
}

int Index::createIndex(string tableName, string indexName, attr_t & attr)
{
    fstream fout;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fout.open(file.c_str(), ios::out | ios::binary);

    // 将索引头信息写到索引文件
    index_head_t idxHd;
    idxHd.attr = attr;
    idxHd.recNum = 0;
    writeHead(fout, idxHd);

    fout.close();

    // 成功返回 0
    return 0;
}

int Index::insertIndex(string tableName, string indexName, index_node_t & node)
{
    fstream fs;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fs.open(file.c_str(), ios::in | ios::out | ios::binary);

    // 读出索引头
    index_head_t idxHd;
    readHead(fs, idxHd);
    // 记录读指针位置
    int readPos = fs.tellg();
    attrtype_t type = idxHd.attr.type;
    int recNum = idxHd.recNum;  // 注意：是插入该索引项之前的索引项数目

    // 更新索引头的索引项数目
    idxHd.recNum++;

    // 写入索引头
    // 更改写指针位置
    fs.seekp(0, ios::beg);
    writeHead(fs, idxHd);

    // 若插入之前索引项数为 0，直接插入
    if (recNum == 0)
    {
        writeNode(fs, node);
    }

    // 若插入之前当前已存在索引项，将记录全部读出再插入
    else
    {
        // 存放读出来的索引项
        index_node_t *idxNode = new index_node_t[recNum];
        // 更新读指针位置
        fs.seekg(readPos);
        // 读出索引项
        for (int i = 0; i < recNum; i++)
        {
            readNode(fs, idxNode[i]);
        }

        // 查找合适的插入位置
        int insertPos;  // 代表插入节点所在的位置原本是第 insertPos 个索引项(从 1 开始算)
        // 如果插入的索引项关键码比第一个索引项都小，就插在最开头
        if (lessThan(node.value, idxNode[0].value, type))
        {
            insertPos = 1;
        }
        else
        {
            insertPos = recNum + 1;   // 插入的位置，若在第一个到最后一个索引之间没有找到插入位置，则默认插入到最后
            for (int i = 0; i < recNum - 1; i++)
            {
                // cout << "this node: " << idxNode[i].value << endl;
                // 满足该条件时插到 i 和 i + 1 之间
                if (!lessThan(idxNode[i + 1].value, node.value, type) &&
                    !lessThan(node.value, idxNode[i].value, type))
                {
                    insertPos = i + 2;
                    break;
                }
            }
        }

        // 应该插到 insertPos 后
        // 把写指针移动到写入新索引项的位置 即（索引头 + insertPos 个索引项之后）
        // 指针的当前位置是索引头后面 故向后偏移 insertPos 个索引项的大小
        int offset = (insertPos - 1) * IDXNODE_SIZE_IN_FILE + IDXHEAD_SIZE_IN_FILE;
        fs.seekp(offset);

        // 写入插入项
        writeNode(fs, node);

        // 将插入项之后的索引项一条条写入
        for (int i = insertPos - 1; i < recNum; i++)
        {
            writeNode(fs, idxNode[i]);
        }

        // 回收内存
        delete [] idxNode;
    }

    fs.close();

    // 成功返回 0
    return 0;
}

int Index::deleteIndex(string tableName, string indexName, string value)
{
    fstream fs;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fs.open(file.c_str(), ios::in | ios::out | ios::binary);

    // 读出索引头
    index_head_t idxHd;
    readHead(fs, idxHd);
    // 记录读指针位置
    int readPos = fs.tellg();
    int recNum = idxHd.recNum;

    // 更新索引头的索引项数目
    idxHd.recNum--;
    // 更新写指针位置 并 写入
    fs.seekp(0, ios::beg);
    writeHead(fs, idxHd);

    // 查找索引
    // 存放读出来的索引项
    index_node_t *idxNode = new index_node_t[recNum];
    // 读出索引项 并 找到要删除的索引项
    int deleteCnt;              // 第 deleteCnt 个索引项是要删除的索引项
    int writePos = readPos;     // 记录写指针位置
    // 更新读指针位置
    fs.seekg(readPos);
    for (int i = 0; i < recNum; i++)
    {
        readNode(fs, idxNode[i]);
        if (idxNode[i].value == value)
        {
            deleteCnt = i;
        }
    }
    writePos = IDXHEAD_SIZE_IN_FILE + deleteCnt * IDXNODE_SIZE_IN_FILE;

    // 将写指针放到第 deletePos 个索引项的开头
    // 写第 deletePos + 1 及其后面的所有索引项
    fs.seekp(writePos);
    for (int i = deleteCnt + 1; i < recNum; i++)
    {
        writeNode(fs, idxNode[i]);
    }

    // 回收内存
    delete [] idxNode;

    fs.close();

    // 成功返回 0
    return 0;
}

int Index::updateIndex(string tableName, string indexName, string value, string newValue)
{
    fstream fs;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fs.open(file.c_str(), ios::in | ios::out | ios::binary);

    // 读出索引头
    index_head_t idxHd;
    readHead(fs, idxHd);

    // 查找索引
    // 二分查找到要求索引项的起始地址
    int pos = biSearch(fs, 1, idxHd.recNum, value, idxHd.attr.type);
    // 读取要求索引项
    fs.seekg(pos);
    index_node_t curIdxNode;
    readNode(fs, curIdxNode);

    // 更新要求索引项
    curIdxNode.value = newValue;

    // 为了保持更新后有序 先删除该索引项 再将更新过的索引项插入到合适位置
    deleteIndex(tableName, indexName, value);
    insertIndex(tableName, indexName, curIdxNode);

    fs.close();

    // 成功返回 0
    return 0;
}

int Index::mergeIndexAND(index_node_t **list, int listNum, index_node_t *res)
{
    index_node_t *curRes = res;
    int resNum = 0;
    index_node_t *lastRes;  // 标记结果列表中最后一个节点，用于删除最后多申请的一个节点
    curRes->nextNode = NULL;

    for (int i = 0; i < listNum; i++)
    {
        index_node_t *curNode = list[i];
        // 将 list[i] 中的节点加入结果列表
        while (true)
        {
            // 查找其他列表中是否都存在和 curNode 一样的节点
            bool curValid = true;   // 是否要将 curNode 添加到 res 中
            for (int j = 0; j < listNum; j++)
            {
                index_node_t *cmpNode = list[j];
                // 查看列表 list[j] 中是否存在和 curNode 一样的节点
                bool exist = false;
                while (true)
                {
                    if (cmpNode->offset == curNode->offset)
                    {
                        exist = true;
                        break;
                    }
                    // 若没有下一个节点 退出当前列表 合并下一个列表
                    if (curNode->nextNode == NULL)
                    {
                        break;
                    }
                    // 若有下一个节点 继续合并当前列表
                    else
                    {
                        curNode = curNode->nextNode;
                    }
                }
                // 如果 list[j] 中没有和 curNode 一样的节点，可以判定 curNode 是无须加入的
                if (!exist)
                {
                    curValid = false;
                    break;
                }
                // 如果 list[j] 中有和 curNode 一样的节点，继续查看下一个列表
                else
                {
                    continue;
                }
            }

            // 如果 curNode 须加入 res 的，加入之
            if (curValid)
            {
                // 查找结果列表中是否已存在当前节点
                bool exist = false;
                if (resNum > 0)
                {
                    index_node_t *tmp = res;
                    for (int i = 0; i < resNum; i++)
                    {
                        if (tmp->value == curNode->value)
                        {
                            exist = true;
                            break;
                        }
                        tmp = tmp->nextNode;
                    }
                }
                // 如果结果列表中不存在当前节点 才把当前节点加入结果列表
                if (!exist)
                {
                    curRes->value = curNode->value;
                    curRes->offset = curNode->offset;
                    resNum++;
                    // 在这里会导致最后多申请一个节点，需要删除之
                    curRes->nextNode = new index_node_t; 
                    lastRes = curRes;
                    curRes = curRes->nextNode;
                }
            }

            // 若没有下一个节点 退出当前列表 合并下一个列表
            if (curNode->nextNode == NULL)
            {
                break;
            }
            // 若有下一个节点 继续合并当前列表
            else
            {
                curNode = curNode->nextNode;
            }
        }
    }

    // 删除多余的一个节点
    delete lastRes->nextNode;
    lastRes->nextNode = NULL;

    // 成功返回 0
    return 0;
}

int Index::mergeIndexOR(index_node_t **list, int listNum, index_node_t *res)
{
    index_node_t *curRes = res;
    int resNum = 0;
    index_node_t *lastRes;  // 标记结果列表中最后一个节点，用于删除最后多申请的一个节点
    curRes->nextNode = NULL;

    for (int i = 0; i < listNum; i++)
    {
        index_node_t *cur = list[i];

        // 将 list[i] 中的节点加入结果列表
        while (true)
        {
            // 查找结果列表中是否已存在当前节点
            bool exist = false;
            if (resNum > 0)
            {
                index_node_t *tmp = res;
                for (int i = 0; i < resNum; i++)
                {
                    if (tmp->value == cur->value)
                    {
                        exist = true;
                        break;
                    }
                    tmp = tmp->nextNode;
                }
            }
            // 如果结果列表中不存在当前节点 才把当前节点加入结果列表
            if (!exist)
            {
                curRes->value = cur->value;
                curRes->offset = cur->offset;
                resNum++;
                // 在这里会导致最后多申请一个节点，需要删除之
                curRes->nextNode = new index_node_t; 
                lastRes = curRes;
                curRes = curRes->nextNode;
            }

            // 若没有下一个节点 退出当前列表 合并下一个列表
            if (cur->nextNode == NULL)
            {
                break;
            }
            // 若有下一个节点 继续合并当前列表
            else
            {
                cur = cur->nextNode;
            }
        }
    }

    // 删除多余的一个节点
    delete lastRes->nextNode;
    lastRes->nextNode = NULL;

    // 成功返回 0
    return 0;
}

/***********************************************************/

int Index::biSearch(fstream & fin, int from, int to, string value, attrtype_t type)
{
    index_node_t curIdxNode;

    // 找到该次查询的节点
    int mid = (from + to) / 2;
    // 定位该次查询节点的起始地址
    int pos = IDXHEAD_SIZE_IN_FILE + (mid - 1) * IDXNODE_SIZE_IN_FILE;

    fin.seekg(pos);

    // 读取节点并比较
    readNode(fin, curIdxNode);
    string curValue = curIdxNode.value;
    // 继续查询右半部分
    if (lessThan(curValue, value, type))
    {
        return biSearch(fin, mid + 1, to, value, type);
    }
    // 继续查询左半部分
    else if (lessThan(value, curValue, type))
    {
        return biSearch(fin, from, mid - 1, value, type);
    }
    else
    {
        return pos;
    }
}

int Index::biSearchFrom(fstream & fin, int from, int to, string value, attrtype_t type)
{
    index_node_t curIdxNode, prevIdxNode;

    // 找到该次查询的节点
    int mid = (from + to) / 2;
    // 定位该次查询节点的起始地址
    int pos = IDXHEAD_SIZE_IN_FILE + (mid - 1) * IDXNODE_SIZE_IN_FILE;

    fin.seekg(pos - IDXNODE_SIZE_IN_FILE);

    // 读取节点并比较
    readNode(fin, prevIdxNode);
    readNode(fin, curIdxNode);
    string curValue = curIdxNode.value;
    string prevValue = prevIdxNode.value;
    // 当前节点是 “第一个” 关键码大于等于 value 的节点时，返回
    if (lessThan(prevValue, value, type) &&
        !lessThan(curValue, value, type))
    {
        return pos;
    }
    // 继续查询右半部分
    else if (lessThan(curValue, value, type))
    {
        return biSearchFrom(fin, mid + 1, to, value, type);
    }
    // 继续查询左半部分
    else if (!lessThan(curValue, value, type))
    {
        return biSearchFrom(fin, from, mid - 1, value, type);
    } 
    // 表现正常是不会到这儿的
    else 
    {
        return -1;
    }
}

int Index::biSearchTo(fstream & fin, int from, int to, string value, attrtype_t type)
{
    index_node_t curIdxNode, prevIdxNode;

    // 找到该次查询的节点
    int mid = (from + to) / 2;
    // 定位该次查询节点的起始地址
    int pos = IDXHEAD_SIZE_IN_FILE + (mid - 1) * IDXNODE_SIZE_IN_FILE;

    fin.seekg(pos - IDXNODE_SIZE_IN_FILE);

    // 读取节点并比较
    readNode(fin, prevIdxNode);
    readNode(fin, curIdxNode);
    string curValue = curIdxNode.value;
    string prevValue = prevIdxNode.value;


    // 当前节点是 “第一个” 关键码大于 value 的节点时，返回 前面一个节点的其实地址 :]
    if (!lessThan(value, prevValue, type) &&
        lessThan(value, curValue, type))
    {
        return pos - IDXNODE_SIZE_IN_FILE;
    }
    // 继续查询右半部分
    else if (!lessThan(value, curValue, type))
    {
        return biSearchTo(fin, mid + 1, to, value, type);
    }
    // 继续查询左半部分
    else if (lessThan(value, curValue, type))
    {
        return biSearchTo(fin, from, mid - 1, value, type);
    } 
    // 表现正常是不会到这儿的
    else 
    {
        return -1;
    }
}

/***********************************************************/

bool Index::lessThan(string value_1, string value_2, attrtype_t type)
{
    // 类型为 INT 时转化为 int 比较
    if (type == INT)
    {
        int iValue_1 = atoi(value_1.c_str());
        int iValue_2 = atoi(value_2.c_str());

        return (iValue_1 < iValue_2);
    }

    // 类型为 CHAR 时按字典序比较
    else
    {
        return (value_1 < value_2);
    }
}

/***********************************************************/

void Index::readAttr(fstream & fin, attr_t & attr)
{
    char buf[MAX_CHAR_LENGTH];
    fin.read((char *)buf, MAX_CHAR_LENGTH);
    fin.read((char *)&(attr.isPrimary), sizeof(bool));
    fin.read((char *)&(attr.length), sizeof(int));
    fin.read((char *)&(attr.type), sizeof(attrtype_t));
    attr.name = buf;
}

void Index::writeAttr(fstream & fout, attr_t & attr)
{
    fout.write((char *)attr.name.c_str(), MAX_CHAR_LENGTH);
    fout.write((char *)&(attr.isPrimary), sizeof(bool));
    fout.write((char *)&(attr.length), sizeof(int));
    fout.write((char *)&(attr.type), sizeof(attrtype_t));
    fout.flush();
}

void Index::readHead(fstream & fin, index_head_t & head)
{
    readAttr(fin, head.attr);
    fin.read((char *)&(head.recNum), sizeof(int));
}

void Index::writeHead(fstream & fout, index_head_t & head)
{
    writeAttr(fout, head.attr);
    fout.write((char *)&(head.recNum), sizeof(int));
    fout.flush();
}

void Index::readNode(fstream & fin, index_node_t & node)
{ 
    char buf[MAX_CHAR_LENGTH];
    fin.read((char *)buf, MAX_CHAR_LENGTH);
    // fin.read((char *)&(node.basep), sizeof(void *));
    fin.read((char *)&(node.offset), sizeof(unsigned));
    node.value = buf;
}
void Index::writeNode(fstream & fout, index_node_t & node)
{
    fout.write((char *)node.value.c_str(), MAX_CHAR_LENGTH);
    // fout.write((char *)&(node.basep), sizeof(void *));
    fout.write((char *)&(node.offset), sizeof(unsigned));
    fout.flush();
}

Index::Index()
{

}

Index::~Index()
{

}

void Index::debugPrint(string tableName, string indexName)
{
    fstream fin;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fin.open(file.c_str(), ios::in | ios::binary);

    // 读出索引头
    index_head_t idxHd;
    readHead(fin, idxHd);

    cout << "record num = " << idxHd.recNum << endl;

    if (idxHd.recNum == 0)
    {
        return;
    }

    cout << "---records:" << endl;
    for (int i = 1; i <= idxHd.recNum; i++)
    {
        cout << i << ": " << endl;
        index_node_t tmp;
        readNode(fin, tmp);
        cout << "  value: " << tmp.value << endl;
        cout << "  offset: " << tmp.offset << endl;
        cout << "  pos: " << IDXHEAD_SIZE_IN_FILE + IDXNODE_SIZE_IN_FILE * (i - 1) << endl;
    }
    cout << endl;

    fin.close();
}