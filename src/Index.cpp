#include "index.h"

void Index::selectIndex(string tableName, string indexName, string value, index_node_t *res)
{
    ifstream fin;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fin.open(file.c_str(), ios::in | ios::binary);

    // 读出索引头
    index_head_t idxHd;
    readHead(fin, idxHd);

    // 查找索引
    for (int i = 0; i < idxHd.recNum; i++)
    {
        index_node_t curIdxNode;
        readNode(fin, curIdxNode);

        // 找到了要求索引项
        if (curIdxNode.value == value)
        {
            // 填写结果
            res->value = curIdxNode.value;
            // res->basep = curIdxNode.basep;
            res->offset = curIdxNode.offset;
            break;
        }
    }

    fin.close();
}

void Index::createIndex(string tableName, string indexName, attr_t & attr)
{
    ofstream fout;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fout.open(file.c_str(), ios::out | ios::binary);

    // 将索引头信息写到索引文件
    index_head_t idxHd;
    idxHd.attr = attr;
    idxHd.recNum = 0;
    writeHead(fout, idxHd);

    fout.close();
}

void Index::insertIndex(string tableName, string indexName, index_node_t node)
{
    ifstream fin;
    ofstream fout;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fin.open(file.c_str(), ios::in | ios::binary);
    fout.open(file.c_str(), ios::out | ios::binary);

    // 读出索引头
    index_head_t idxHd;
    readHead(fin, idxHd);
    attrtype_t type = idxHd.attr.type;
    int recNum = idxHd.recNum;  // 注意：是插入该索引项之前的索引项数目

    // 更新索引头的索引项数目
    idxHd.recNum++;

    // 写入索引头
    writeHead(fout, idxHd);

    // 若插入之前索引项数为 0，直接插入
    if (recNum == 0)
    {
        writeNode(fout, node);
    }

    // 若插入之前当前已存在索引项，将记录全部读出再插入
    else
    {
        // 存放读出来的索引项
        index_node_t *idxNode = new index_node_t[recNum];
        // 读出索引项
        for (int i = 0; i < recNum; i++)
        {
            readNode(fin, idxNode[i]);
        }

        // 查找合适的插入位置
        int pos = 0;        // 插入的位置
        for (int i = 0; i < recNum - 1; i++)
        {
            // 满足该条件时插到 i 和 i + 1 之间
            if (lessThan(idxNode[i].value, node.value, type) &&
                lessThan(idxNode[i + 1].value, node.value, type))
            {
                pos = i;
                break;
            }
        }

        // 应该插到 pos 后
        // 把写指针移动到写入新索引项的位置 即（索引头 + pos 个索引项之后）
        // 指针的当前位置是索引头后面 故向后偏移 pos 个索引项的大小
        int offset = pos * IDXNODE_SIZE_IN_FILE;
        fout.seekp(offset, ios::cur);

        // 写入插入项
        writeNode(fout, node);

        // 将插入项之后的索引项一条条写入
        for (int i = pos + 1; i < recNum; i++)
        {
            writeNode(fout, idxNode[i]);
        }

        // 回收内存
        delete [] idxNode;
    }

    fin.close();
    fout.close();
}

void Index::deleteIndex(string tableName, string indexName, string value)
{
    ifstream fin;
    ofstream fout;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fin.open(file.c_str(), ios::in | ios::binary);
    fout.open(file.c_str(), ios::out | ios::binary);

    // 读出索引头
    index_head_t idxHd;
    readHead(fin, idxHd);
    int recNum = idxHd.recNum;

    // 更新索引头的索引项数目 并 写入
    idxHd.recNum++;
    writeHead(fout, idxHd);

    // 查找索引
    for (int i = 0; i < idxHd.recNum; i++)
    {
        index_node_t curIdxNode;
        readNode(fin, curIdxNode);

        // 存放读出来的索引项
        index_node_t *idxNode = new index_node_t[recNum];
        // 读出索引项 并 找到要删除的索引项
        int pos;    // 第 pos 个索引项是要删除的索引项
        for (int i = 0; i < recNum; i++)
        {
            readNode(fin, idxNode[i]);
            if (idxNode[i].value == value)
            {
                pos = i;
            }
        }

        // 将写指针放到第 pos 个索引项的开头
        // 写第 pos + 1 及其后面的所有索引项
        fout.seekp(IDXHEAD_SIZE_IN_FILE + (pos - 1) * IDXNODE_SIZE_IN_FILE);
        for (int i = pos + 1; i < recNum; i++)
        {
            writeNode(fout, idxNode[i]);
        }
    }

    fin.close();
    fout.close();
}

void Index::updateIndex(string tableName, string indexName, string value, string newValue)
{
    ifstream fin;
    ofstream fout;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fin.open(file.c_str(), ios::in | ios::binary);

    // 读出索引头
    index_head_t idxHd;
    readHead(fin, idxHd);

    // 查找索引
    for (int i = 0; i < idxHd.recNum; i++)
    {
        index_node_t curIdxNode;
        readNode(fin, curIdxNode);

        // 找到了要求索引项
        if (curIdxNode.value == value)
        {
            // 更新索引项的关键码值
            curIdxNode.value = newValue;

            // 将更新了的索引项写回文件
            // 先将写指针放到正确位置
            fout.seekp((int)fin.tellg() - (int)IDXNODE_SIZE_IN_FILE);
            writeNode(fout, curIdxNode);

            break;
        }
    }

    fin.close();
    fout.close();
}

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

void Index::readHead(ifstream & fin, index_head_t & head)
{
    fin.read((char *)&(head.attr), sizeof(attr_t));
    fin.read((char *)&(head.recNum), sizeof(int));
}

void Index::writeHead(ofstream & fout, index_head_t & head)
{
    fout.write((char *)&(head.attr), sizeof(attr_t));
    fout.write((char *)&(head.recNum), sizeof(int));
    fout.flush();
}

void Index::readNode(ifstream & fin, index_node_t & node)
{
    char buf[MAX_CHAR_LENGTH];
    fin.read((char *)buf, MAX_CHAR_LENGTH);
    // fin.read((char *)&(node.basep), sizeof(void *));
    fin.read((char *)&(node.offset), sizeof(unsigned));
    node.value = buf;
}
void Index::writeNode(ofstream & fout, index_node_t & node)
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