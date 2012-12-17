#include "index.h"

void Index::select(string tableName, string indexName, string value, index_node_t *res)
{
    
}

void Index::create(string tableName, string indexName, attr_t & attr)
{
    index_head_t *idxHd = new index_head_t;
    idxHd->attr = attr;
    idxHd->recNum = 0;
    idxHd->firstNode = NULL;

    string file = "../data/" + tableName + "_" + indexName + ".idx";
    ofstream fout;
    fout.open(file.c_str(), ios::out | ios::app);

    // 将索引头信息写到索引文件
    writeHead(fout, *idxHd);

    fout.close();
}

void Index::insert(string tableName, string indexName, index_node_t node)
{
    ifstream fin;
    ofstream fout;
    index_head_t *idxHd = new index_head_t;

    // 根据索引名找到索引文件
    string file = "../data/" + tableName + "_" + indexName + ".idx";
    fin.open(file.c_str(), ios::in | ios::binary);

    // 读出索引头
    readHead(fin, *idxHd);
    attrtype_t type = idxHd->attr->type;
    int recNum = idxHd->recNum;

    // 更新索引头的记录数目
    idxHd->recNum++;

    // 写入索引头
    writeHead(fout, *idxHd);

    // 若插入之前记录数为 0，直接插入
    if (recNum == 0)
    {
        writeNode(fout, node);
    }

    // 若插入之前当前已存在记录，将记录全部读出再插入
    else
    {
        // 存放读出来的记录
        index_node_t idxNode[idxHd->recNum];
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

}

bool lessThan(string value_1, string value_2, attrtype_t type)
{

}

void readHead(ifstream & fin, index_head_t & head)
{
    fin.read((char *)&head, sizeof(index_head_t));
}

void writeHead(ofstream & fout, index_head_t & head)
{
    fout.write((char *)&head, sizeof(index_head_t));
}

void readNode(ifstream & fin, index_node_t & node)
{
    char buf[MAX_CHAR_LENGTH];
    fin.read((char *)buf, MAX_CHAR_LENGTH);
    fin.read((char *)&(node.basep), sizeof(void *));
    fin.read((char *)&(node.offset), sizeof(unsigned));
    node.value = buf;
}
void writeNode(ofstream & fout, index_node_t & node)
{
    char buf[MAX_CHAR_LENGTH];
    node->value.copy(buf, MAX_CHAR_LENGTH);
    fout.write((char *)buf, MAX_CHAR_LENGTH);
    fout.write((char *)&(node.basep), sizeof(void *));
    fout.write((char *)&(node.offset), sizeof(unsigned));
}

Index::Index()
{

}

Index::~Index()
{

}