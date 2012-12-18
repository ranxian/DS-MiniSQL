#include "Catalog.h"

attr_t Catalog::findAttr(string tableName, string attrName)
{

}

table_t findTable(string tableName)
{

}

void Catalog::createTable(table_t & table)
{
    ofstream fout;
    fout.open(TABLE_LIST, ios::out | ios::app);

    writeTable(fout, table);

    fout.close();
}

void Catalog::deleteTable(table_t & table)
{

}

bool Catalog::tableExist(string tableName)
{
    bool exist = false;
    table_t tmpTable;

    ifstream fin;
    fin.open(TABLE_LIST, ios::in);

    while (!fin.eof())
    {
        readTable(fin, tmpTable);

        if (tmpTable.name == tableName)
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

void writeTable(ofstream & fout, table_t & table)
{
    fout.write((char *)table.name.c_str(), MAX_CHAR_LENGTH);
    fout.write((char *)&(table.attrNumber), sizeof(int));
    fout.write((char *)&(table.recordLength), sizeof(int));

    for (int i = 0; i < table.attrNumber; i++)
    {
        writeAttr(fout, table.attributes[i]);
    }
    fout.flush();
}

void readTable(ifstream & fin, table_t & table)
{
    char buf[MAX_CHAR_LENGTH];
    fin.read((char *)buf, MAX_CHAR_LENGTH);
    fin.read((char *)&(table.attrNumber), sizeof(int));
    fin.read((char *)&(table.recordLength), sizeof(int));
    table.name = buf;

    for (int i = 0; i < table.attrNumber; i++)
    {
        readAttr(fin, table.attributes[i]);
    }
    fin.flush();
}

void writeAttr(ofstream & fout, attr_t & attr)
{
    fout.write((char *)attr.name.c_str(), MAX_CHAR_LENGTH);
    fout.write((char *)&(attr.isPrimary), sizeof(bool));
    fout.write((char *)&(attr.length), sizeof(int));
    fout.write((char *)&(attr.type), sizeof(attrtype_t));
    fout.flush();
}

void readAttr(ifstream & fin, attr_t & attr)
{
    char buf[MAX_CHAR_LENGTH];
    fin.read((char *)buf, MAX_CHAR_LENGTH);
    fin.read((char *)&(attr.isPrimary), sizeof(bool));
    fin.read((char *)&(attr.length), sizeof(int));
    fin.read((char *)&(attr.type), sizeof(attrtype_t));
    attr.name = buf;
    fin.flush();
}

Catalog::Catalog()
{

}

Catalog::~Catalog()
{

}