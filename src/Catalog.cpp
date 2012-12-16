#include "Catalog.h"

attr_t Catalog::findAttr(string tableName, string attrName)
{

}

table_t findTable(string tableName)
{

}

void Catalog::create(table_t & table)
{
    ofstream fout;
    fout.open("table.info", ios::app);

    // 这是一个表的开头
    fout << "*\n";
    // 表名
    fout << table.name << " ";
    // 一条记录的字节数
    fout << table.recordLength << " ";
    // 字段数
    fout << table.attrNumber << "\n";
    // 每个字段
    for (int i = 0; i < table.attrNumber; i++)
    {
        attr_t attr = table.attributes[i];
        // 字段名
        fout << attr.name << " ";
        // 字段是否是主键
        fout << attr.isPrimary << " ";
        // 字段占字节数
        fout << attr.length << " ";
        // 字段类型
        fout << attr.type << "\n";
    }

    fout.close();
}

void Catalog::delete(table_t & table)
{

}

bool Catalog::tableExist(string tableName)
{
    bool exist = false;
    ifstream fin;
    fin.open(TABLE_LIST, ios::in);

    char curTableName[MAX_FILENAME_LENGTH];   
    string tableName;

    while (!fin.eof())
    {
        fin.getline(curTableName, MAX_FILENAME_LENGTH);
        if (curTableName == "" && fin.eof())
        {
            break;
        }
        if (curTableName == tableName)
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

}

bool Catalog::attrTypeCheck()
{

}


attr_t getPrimaryAttrName()
{

}


Catalog::Catalog()
{

}

Catalog::~Catalog()
{

}