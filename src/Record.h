/*
Record.h
实现数据文件的创建与删除，记录的插入、删除（由表的定义与删除引起）与查找操作，并对外提供相应的接口。
支持等值查找
需要调用buffer模块和异常处理模块(再议)

接口：
Record::Record()                                       //构造函数
Record::Insert(recInfo &);                             //插入记录的函数
Record::Select(fileAddr &, seletRecInfo &) const;      //对表文件进行遍历
Record::Delete(fileAddr &);                            //删除记录时使用
Record::Update(fileAddr &, recInfo &)                  //更新数据


调用模块：
Buffer
被以下模块调用：
API
*/


#include<iostream>
using namespace std;

enum columnType {i,c};

union columnValue
{
    int intValue;                                      //整型值
    char *pcharValue;                                  //字符串指针
};
/*
struct deletedFile                                     //被删除的记录的结构体
{
    fileAddr firstDel;                                 //第一个被删除的记录的地址
    fileAddr lastDel;                                  //最后一个被删除的记录的地址
    fileAddr newInsert;                                //文件末尾第一个可插入记录的地址
	
};
*/
struct cellInfo
{
    colunmType colType;                            //属性类型
    columnvalue value;
    int priorLength;                                //记录头到当前字段之间的长度
    int colLengrh;                                  //当前字段的长度
    cellInfo *next;
};

struct selectCell
{
    char columnName[32];                            //字段名，方便打印
    columnType colType;                            //字段类型，方便打印
    int priorLength;                                //记录头到此字段之间的长度
    int colLengrh;                                  //字段类型的长度
    selectCell *next;                               //下一个字段信息
};

class selectRecInfo
{
    selectCell * head;
    int columnNum;
    int recordLength;
public:
    selectRecInfo();
    ~selectRecInfo();
};

class recInfo
{
public:
    cellInfo *head;
    int colNum;
    int recordLength;
    recInfo();
    ~recInfo();
};

class Record
{
public:
    Record();
    ~Record(){};
    fileAddr Insert(recInfo&);                          //插入记录
    void Delete(fileAddr&);                             //删除记录
    void Update(fileAddr&, recInfo&);                   //更新数据
    recInfo *Select(fileAddr &, seletRecInfo &) const;  //选择单条记录
    void printHead(seletRecInfo &)const;                //打印列表头
    void Print(filePtr &, recInfo& a) const;       //打印record with index
    void printEnd(seletRecInfo &) const;                //打印列表尾部
    filePtr findPlace();
private:
    filePtr firstDel;
    filePtr lastDel;
    filePtr newInsert;                                

}