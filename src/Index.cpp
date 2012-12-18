#include "index.h"

void Index::select(string tableName, string indexName, string value, index_node_t *res)
{
    ifstream fin;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fin.open(file.c_str(), ios::in);

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

void Index::create(string tableName, string indexName, attr_t & attr)
{
    ofstream fout;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fout.open(file.c_str(), ios::out);

    // 将索引头信息写到索引文件
    index_head_t idxHd;
    idxHd.attr = attr;
    idxHd.recNum = 0;
    writeHead(fout, idxHd);

    fout.close();
}

void Index::insert(string tableName, string indexName, index_node_t node)
{
    ifstream fin;
    ofstream fout;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fin.open(file.c_str(), ios::in);

    // 读出索引头
    index_head_t idxHd;
    readHead(fin, idxHd);
    attrtype_t type = idxHd.attr.type;
    int recNum = idxHd.recNum;  // 注意：是插入该索引项之前的索引项数目

    // 更新索引头的记录数目
    idxHd.recNum++;

    // 写入索引头
    writeHead(fout, idxHd);

    // 若插入之前记录数为 0，直接插入
    if (recNum == 0)
    {
        writeNode(fout, node);
    }

    // 若插入之前当前已存在记录，将记录全部读出再插入
    else
    {
        // 存放读出来的记录
        index_node_t idxNode[recNum];
        // 读出记录
        for (int i = 0; i < recNum; i++)
        {
            readNode(fin, idxNode[i]);
        }

        // 查找合适的插入位置
        bool atLast = true; // 判断是否要插到文件最后
        int pos = 0;        // 插入的位置
        for (int i = 0; i < recNum - 1; i++)
        {
            // 满足该条件时插到 i 和 i + 1 之间
            if (lessThan(idxNode[i].value, node.value, type) &&
                lessThan(idxNode[i + 1].value, node.value, type))
            {
                atLast = false;
                pos = i;
                break;
            }
        }

        // 应该插到最后
        if (atLast)
        {
            // 改从文件尾写入的方式
            fout.close();
            fout.open(file.c_str(), ios::out | ios::app);

            writeNode(fout, node);
        }

        // 应该插到 pos 后
        else
        {
            // 将插入项之前的索引项一条条写入
            for (int i = 0; i <= pos; i++)
            {
                writeNode(fout, idxNode[i]);
            }

            // 写入插入项
            writeNode(fout, node);

            // 将插入项之后的索引项一条条写入
            for (int i = pos + 1; i < recNum; i++)
            {
                writeNode(fout, idxNode[i]);
            }
        }
    }

    fin.close();
    fout.close();
}

void Index::deleteIndex(string tableName, attr_t attribute, string value)
{
 
}

void Index::update(string tableName, string indexName, string value, string newValue)
{
    ifstream fin;
    ofstream fout;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fin.open(file.c_str(), ios::in);

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

            break;
        }
    }

    fin.close();
    fout.close();
}

bool lessThan(string value_1, string value_2, attrtype_t type)
{
    // 类型为 INT 时转化为 int 比较
    if (type == INT)
    {
        int iValue_1 = atoi(value_1);
        int iValue_2 = atoi(value_2);
        return (iValue_1 < iValue_2);
    }

    // 类型为 CHAR 时按字典序比较
    else
    {
        return (value_1 < value_2);
    }
}

void readHead(ifstream & fin, index_head_t & head)
{
    fin.read((char *)&head, sizeof(index_head_t));
    fin.flush();
}

void writeHead(ofstream & fout, index_head_t & head)
{
    fout.write((char *)&head, sizeof(index_head_t));
    fout.flush();
}

void readNode(ifstream & fin, index_node_t & node)
{
    char buf[MAX_CHAR_LENGTH];
    fin.read((char *)buf, MAX_CHAR_LENGTH);
    // fin.read((char *)&(node.basep), sizeof(void *));
    fin.read((char *)&(node.offset), sizeof(unsigned));
    node.value = buf;
    fin.flush();
}
void writeNode(ofstream & fout, index_node_t & node)
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