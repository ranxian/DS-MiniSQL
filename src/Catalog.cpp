#include "Catalog.h"

attr_t Catalog::findAttr(string tableName, string attrName)
{

}

table_t findTable(string tableName)
{
    
}

void Catalog::create(table_t & table)
{
    string fileName = table.name + ".table";

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