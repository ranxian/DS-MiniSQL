#include "../src/MiniSQL.h"
#include "../src/Record.h"
#include "../src/Record.cpp"
#include "../src/Interpreter.cpp"
#include "../src/Interpreter.h"


int main()
{
    

    Interpreter itp;
    Record Test;
    info_t testInfo;
    record_t *testRecord;
    
    //建表，输出表字段信息
    if (itp.inputCommand())
    {
        testInfo = itp.getInfo();
    //Test.Insert(testInfo);
        Test.PrintHead(testInfo.t);
        cout << "table built successfully!" << endl;
    }
    

    //插入记录
    if (itp.inputCommand())
    {
        testInfo = itp.getInfo();
        cout << "Insert return: " << Test.Insert(testInfo) << endl;;
        cout << "record inserted successfully!"  << endl;
    }
    
    //Test.Print(testRecord);
    
    //插入记录
    if (itp.inputCommand())
    {
        testInfo = itp.getInfo();
        cout << "Insert return: " << Test.Insert(testInfo) << endl;;
        cout << "record inserted successfully!"  << endl;
    }
    

    //查找记录并输出
    if (itp.inputCommand())
    {
        testInfo = itp.getInfo();
        //itp.debug(); 
        testRecord = Test.Select(testInfo);
        cout << "record selected successfully!" << endl;
        if (testRecord != NULL)
        {
            Test.Print(testRecord);
        }
        else
        {
            cout << "record not found!!" << endl;
        }
        
        

    }
    


    /*
    while(1)
    {
        if (itp.inputCommand())
        {
            
            testRecord = Test.select(testInfo)

        }

         
    }
    

    */


    /*
    table.name = "Persons";
    table.attrNum = 3;
    table.recordLength = 68;
    table.attributes[0].name = "姓名";
    table.attributes[0].isPrimary = false;
    table.attributes[0].length = 32;
    table.attributes[0].type = CHAR;
    table.attributes[1].name = "性别";
    table.attributes[1].isPrimary = false;
    table.attributes[1].length = 32;
    table.attributes[1].type = CHAR;
    table.attributes[2].name = "学号";
    table.attributes[2].isPrimary = true;
    table.attributes[2].length = 8;
    table.attributes[2].type = INT;

    Record testRecord;
    
    table_t table;
    info_t info;
    
    
    record_t * record = new record_t;
    record->next = NULL;
    record->value = NULL;
    record->value = new value_t;
    record->value->type = CHAR;
    record->value->str_value = "hehehaha";
    record->value->next = new value_t;
    record->value->next->type = INT;
    record->value->next->int_value = 12;
    record->value->next->next = NULL;

    testRecord.PrintHead(table);
    testRecord.Print(record);
    */
    /*
    // 初始化表
    CatalogManager.initTable();

    // 建表
    cout << "建表：" << endl;
    CatalogManager.createTable(table);
    cout << endl;

    // 返回主键
    cout << "返回主键：" << endl;
    attr_t attrTmp = CatalogManager.getPrimaryAttrName("Persons");
    printAttr(attrTmp);
    cout << endl;

    // 返回表
    cout << "返回表：" << endl;
    table_t tableTmp = CatalogManager.findTable("Persons");
    cout << tableTmp.name << " " << tableTmp.attrNum << " " << tableTmp.recordLength << endl;
    for (int i = 0; i < tableTmp.attrNum; i++)
    {
        printAttr(tableTmp.attributes[i]);
    }
    cout << endl;

    // 返回字段
    cout << "返回字段：" << endl;
    attr_t attrTmp2 = CatalogManager.findAttr("Persons", "姓名");
    printAttr(attrTmp2);
    cout << endl;

    // 表存在
    cout << "表存在：" << endl;
    cout << CatalogManager.tableExist("Persons") << endl;
    cout << CatalogManager.tableExist("a") << endl;
    cout << endl;

    // 建表
    cout << "建表：" << endl;
    table.name = "Students";
    CatalogManager.createTable(table);
    cout << endl;

    // 表存在
    cout << "表存在：" << endl;
    cout << CatalogManager.tableExist("Persons") << endl;
    cout << CatalogManager.tableExist("Students") << endl;
    cout << endl;

    // 字段存在
    cout << "字段存在：" << endl;
    cout << CatalogManager.attrExist("Students", "学号") << endl;
    cout << CatalogManager.attrExist("Students", "什么鸟啊") << endl;
    cout << endl;

    // 删表
    cout << "删表：" << endl;
    CatalogManager.deleteTable(table);
    cout << endl;

    // 表存在
    cout << "表存在：" << endl;
    cout << CatalogManager.tableExist("Persons") << endl;
    cout << CatalogManager.tableExist("Students") << endl;
    cout << endl;
    */

    return 0;
}