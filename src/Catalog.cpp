#include "Catalog.h"

attr_t Catalog::findAttr(string tableName, string attrName)
{
    ifstream fin;
    fin.open(TABLE_LIST, ios::in);

    table_t tableTmp;
    attr_t attrTmp;

    // 读出表信息头 获得表项的数目
    table_head_t tableHd;
    readTableHead(fin, tableHd);
    int tableNum = tableHd.tableNum;

    // 查找表名为 tableName 的表项
    for (int i = 0; i < tableNum; i++)
    {
        readTable(fin, tableTmp);
        // 查找表中名为 attrName 的字段
        if (tableTmp.name == tableName)
        {
            for (int j = 0; j < tableTmp.attrNum; j++)
            {
                if (tableTmp.attributes[j].name == attrName)
                {
                    attrTmp = tableTmp.attributes[j];
                    break;
                }
            }
            break;
        }
    }

    fin.close();
    return attrTmp;
}

table_t Catalog::findTable(string tableName)
{
    ifstream fin;
    fin.open(TABLE_LIST, ios::in);

    table_t tableTmp;

    // 读出表信息头 获得表项的数目
    table_head_t tableHd;
    readTableHead(fin, tableHd);
    int tableNum = tableHd.tableNum;

    // 查找表名为 tableName 的表项
    for (int i = 0; i < tableNum; i++)
    {
        readTable(fin, tableTmp);
        if (tableTmp.name == tableName)
        {
            break;
        }
    }

    fin.close();
    return tableTmp;
}

attr_t Catalog::getPrimaryAttrName(string tableName)
{
    ifstream fin;
    fin.open(TABLE_LIST, ios::in);

    table_t tableTmp;
    attr_t attrTmp;

    // 读出表信息头 获得表项的数目
    table_head_t tableHd;
    readTableHead(fin, tableHd);
    int tableNum = tableHd.tableNum;

    // 查找表名为 tableName 的表项
    for (int i = 0; i < tableNum; i++)
    {
        readTable(fin, tableTmp);
        // 查找表中是主键的字段
        if (tableTmp.name == tableName)
        {
            for (int j = 0; j < tableTmp.attrNum; j++)
            {
                if (tableTmp.attributes[j].isPrimary)
                {
                    attrTmp = tableTmp.attributes[j];
                    break;
                }
            }
            break;
        }
    }

    fin.close();
    return attrTmp;
}

bool Catalog::tableExist(string tableName)
{
    ifstream fin;
    fin.open(TABLE_LIST, ios::in);

    bool exist = false;
    table_t tableTmp;

    // 读出表信息头 获得表项的数目
    table_head_t tableHd;
    readTableHead(fin, tableHd);
    int tableNum = tableHd.tableNum;

    // 查找是否存在表名为 tableName 的表项
    for (int i = 0; i < tableNum; i++)
    {
        readTable(fin, tableTmp);
        if (tableTmp.name == tableName)
        {
            exist = true;
            break;
        }
    }

    fin.close();
    return exist;
}

bool Catalog::attrExist(string tableName, string attrName)
{
    ifstream fin;
    fin.open(TABLE_LIST, ios::in);

    bool exist = false;
    table_t tableTmp;

    // 读出表信息头 获得表项的数目
    table_head_t tableHd;
    readTableHead(fin, tableHd);
    int tableNum = tableHd.tableNum;

    // 查找是否存在表名为 tableName 的表项
    for (int i = 0; i < tableNum; i++)
    {
        readTable(fin, tableTmp);
        // 该表存在 查找表中是否存在名为 attrName 的字段
        if (tableTmp.name == tableName)
        {
            for (int j = 0; j < tableTmp.attrNum; j++)
            {
                // 该字段存在
                if (tableTmp.attributes[j].name == attrName)
                {
                    exist = true;
                    break;
                }
            }
            break;
        }
    }

    fin.close();
    return exist;
}

void Catalog::createTable(table_t & table)
{
    ifstream fin;
    ofstream fout;
    fin.open(TABLE_LIST, ios::in | ios::binary);
    fout.open(TABLE_LIST, ios::out | ios::binary);

    // 读出表头 更新表头的表数目 并 写入
    table_head_t tableHd;
    readTableHead(fin, tableHd);
    tableHd.tableNum++;
    writeTableHead(fout, tableHd);

    // 将写指针移动到文件末尾
    // 写入新建立的表的信息
    fout.seekp(ios::end);
    writeTable(fout, table);

    fin.close();
    fout.close();
}

void Catalog::deleteTable(table_t & table)
{
    ifstream fin;
    ofstream fout;
    fin.open(TABLE_LIST, ios::in | ios::binary);
    fout.open(TABLE_LIST, ios::out | ios::binary);

    // 读出表头 获得表的数量
    table_head_t tableHd;
    readTableHead(fin, tableHd);
    int tableNum = tableHd.tableNum;

    // 更新表头中表的数量 并 将表头写入
    tableHd.tableNum--;
    writeTableHead(fout, tableHd);

    // 读出所有表项 并 找到要删除的表的位置
    int n = 0;      // 第 n 个表项是要删除的表项
    int pos = 0;    // pos 是要删除的表项的起始地址
    // 开辟空间存放所有表项
    table_t *tables = new table_t[tableNum];
    for (int i = 0; i < tableNum; i++)
    {
        readTable(fin, tables[i]);
        if (tables[i].name == table.name)
        {
            n = i;
            pos = (int)fin.tellg() - (int)TABLENODE_SIZE_IN_FILE;
        }
    }

    // 从地址 pos 处开始写入第 n + 1 及其后面的表信息项
    fout.seekp(pos);
    for (int i = n + 1; i < tableNum; i++)
    {
        writeTable(fout, tables[i]);
    }

    // 回收内存
    delete [] tables;

    fin.close();
    fout.close();
}

void Catalog::writeTableHead(ofstream & fout, table_head_t & tableHead)
{
    fout.write((char *)&(tableHead.tableNum), sizeof(int));
    fout.flush();
}

void Catalog::readTableHead(ifstream & fin, table_head_t & tableHead)
{
    fin.read((char *)&(tableHead.tableNum), sizeof(int));
}

void Catalog::writeTable(ofstream & fout, table_t & table)
{
    fout.write((char *)table.name.c_str(), MAX_CHAR_LENGTH);
    fout.write((char *)&(table.attrNum), sizeof(int));
    fout.write((char *)&(table.recordLength), sizeof(int));
    for (int i = 0; i < table.attrNum; i++)
    {
        writeAttr(fout, table.attributes[i]);
    }
    fout.flush();
}

void Catalog::readTable(ifstream & fin, table_t & table)
{
    char buf[MAX_CHAR_LENGTH];
    fin.read((char *)buf, MAX_CHAR_LENGTH);
    fin.read((char *)&(table.attrNum), sizeof(int));
    fin.read((char *)&(table.recordLength), sizeof(int));
    table.name = buf;
    for (int i = 0; i < table.attrNum; i++)
    {
        readAttr(fin, table.attributes[i]);
    }
}

void Catalog::writeAttr(ofstream & fout, attr_t & attr)
{
    fout.write((char *)attr.name.c_str(), MAX_CHAR_LENGTH);
    fout.write((char *)&(attr.isPrimary), sizeof(bool));
    fout.write((char *)&(attr.length), sizeof(int));
    fout.write((char *)&(attr.type), sizeof(attrtype_t));
    fout.flush();
}

void Catalog::readAttr(ifstream & fin, attr_t & attr)
{
    char buf[MAX_CHAR_LENGTH];
    fin.read((char *)buf, MAX_CHAR_LENGTH);
    fin.read((char *)&(attr.isPrimary), sizeof(bool));
    fin.read((char *)&(attr.length), sizeof(int));
    fin.read((char *)&(attr.type), sizeof(attrtype_t));
    attr.name = buf;
}

Catalog::Catalog()
{

}

Catalog::~Catalog()
{

}