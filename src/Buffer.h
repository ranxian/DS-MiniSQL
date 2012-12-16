/*
BUffer类的实现
1.读取指定数据到系统缓冲区或者将缓冲区中的数据写出到文件
2.用CLOCK算法进行页替换
3.对缓冲区中各页的状态进行记录
*/
 
#include<iostream>
using namespace std;

//文件物理页头信息
class tablePageHeader
{
public:
	void initialPageHead(unsigned long mypageid, bool myisfixed); //初始化函数
	unsigned long pageId;  										  //页编号
	bool isFixed;         										  //是否常驻内存


};

//文件头信息
class tableFileCond
{
	unsigned long pageNum; 											//文件已有页总数
	char lastModifiedTime[20]; 										//最近一次修改时间
	void initialfileCond(); 										//信息初始化	
};

//文件指针
class filePtr
{
	public:
	void initialize();   											//初始化文件指针
	void * changeToMem();   										//文件指针转换为内存地址
	//void shiftOffset(int offset);  //指针滑动
	

	unsigned long filePageId;   									//页编号
	unsigned int offset;    										//页内的偏移量
	

};

//内存页信息类
class menPageInfo
{
public:
	memPageInfo(); //构造函数
	~memPageInfo(); //析构函数
	void updatePageInfo(unsigned int tableid, unsigned long filepageid); //更新内存页信息，写回或从物理页写入
	tablePageHeader *getPtr2Head() const;  								 //获取内存页头信息的首地址
	tableFileCond *getPtr2FileCond() const;  							 //获得内存页指向文件头信息的首地址
	unsigned int getTableId() const; 									 //获得内存所属文件编号
	unsigned long getFilePageId() const; 								 //获取内存页的编号

private:
	bool isLastUsed;													  //最近一次访问内存是是否被使用
	bool isModified; 													  //最近一次访问内存是是否被修改
	memPage * ptr2page;  												  //指向一个内存页
	

};

//文件管理类
class table
{
public:
	table(const char *name, unsigned int tableid); 							//构造函数
	void Deconstruct();  													//对象析构
	memPageInfo *getPageInfo(unsigned long filepageid) const;  
	filePtr operator[](unsigned long filepageid) const;
	filePtr getCataPoint() const;  											//取得catalog模块在文件中可写的首地址
	filePtr getIdPoint() const; 											//取得B+模块在文件中可写的首地址
	unsigned long getPageNum() const; 										//取得该文件页总数
	//void setPageFixed(unsigned long filepageid); //使某一物理页常驻内存
	//void setPageUnfixed(unsigned long filepageid); //取消某一页的常驻内存

private:
	unsigned int tableId;  										//文件编号
	unsigned long pPageNum;  									//文件所含物理页总数
	bool isNew;  												//是否新建
	char fileName[FILENAME_MAXLEN]; 							//文件名
	table *next; 												//下一个已打开的文件
	int ptr2File;    											//指向该文件的文件句柄


};


//内存页管理类
class memPage
{
public:
	memPage(); 															//构造函数
	~memPage();  														//析构函数
	void loadFromFile(unsigned int tableid, unsigned long filepageid);  //从物理文件导入相应内容
	void back2file() const;  											//写回物理页，如果该页已被修改
	tableFileCond *ptr2filecond(); 										//获取文件头信息
private:
	unsigned int tableId; 												//所属文件id
	unsigned long filePageId; 											//页id
	void *ptr2pageBegin;  												//内存指针指向内存映射的物理页的首地址
	tablePageHeader *ptr2head; 											//指向物理页头信息的首地址
	

	
}；


//数据库管理类
class DB
{
public:
	bool getIsNew(unsigned int tableid) const; 			//判断一个文件是否新建
	void setIsNew(unsigned int tableid, bool isnew); 	//设置文件是否新建
	unsigned long getPageNum(unsigned int tableid) const; //返回文件拥有物理页总数
	void addPageNum(unsigned int tableid, int add);  	//设置文件物理页总数
	int getPtr2file(unsigned int tableid) const;  		//返回文件句柄
	table operator[](const char *filename); 			//根据文件名返回文件管理对象，若文件已打开，直接返回，
	                                         			//否则建立一个新文件管理对象返回
	void start(); 										//数据库管理初始化
	void end(); 										//数据库管理对象析构，
private:
	unsigned int tableNum; 								//已打开的文件数
	unsigned int currTableId; 							//当前正在操作的文件id
	table *first;  										//第一个打开的文件
	table *last; 										//最后一个打开的文件
	table *currTable; 									//当前正在操作的文件
};