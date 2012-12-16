/**************************** 
 * MiniSQL.h - 宏定义，配置文件 
 ****************************/

#ifndef MINISQL_H
#define MINISQL_H

/* 引用库 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

/* 常用宏定义 */
#define MAX_FILENAME_LENGTH 256 /* 最长文件名长度 */
#define MAX_CMD_LENGTH      256 /* 最长命令长度 */
#define MAX_ATTRNAME_LENGTH 256 /* 最长字段长度 */
#define MAX_RECORD_LENGTH   256 /* 最长记录长度 */
#define MAX_ATTR_NUM        32  /* 一个表的最长字段数目 */
#define TABLE_LIST "table.list" /* 保存表信息的文件 */
#define INDEX_LIST "index.list" /* 保存索引信息的文件 */
#endif