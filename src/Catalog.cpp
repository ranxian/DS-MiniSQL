#include "Catalog.h"

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

pAttrInfo Catalog::findAttr()
{

}

pAttrInfo getPrimaryAttrName()
{

}

void Catalog::create()
{

}

void Catalog::delete()
{

}

Catalog::Catalog()
{

}

Catalog::~Catalog()
{

}