/**************************** 
 * MiniSQL.h - 宏定义，配置文件 
 ****************************/

#ifndef MINISQL_H
#define MINISQL_H

/* 引用库 */
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>

/* 引用模块 */
#include "Catalog.h"
#include "Interpreter.h"
#include "Index.h"
#include "Record.h"
#include "API.h"

/* 全局配置 */
#define MAX_FILENAME_LENGTH 256     /* 最长文件名长度 */
#define MAX_CMD_LENGTH      256     /* 最长命令长度 */
#define MAX_ATTRNAME_LENGTH 256     /* 最长字段长度 */
#define MAX_RECORD_LENGTH   256     /* 最长记录长度 */
#define MAX_ATTR_NUM        32      /* 一个表的最长字段数目 */
#define TABLE_LIST "table.list"     /* 保存表信息的文件 */
#define INDEX_LIST "index.list"     /* 保存索引信息的文件 */
#define FILE_PAGESIZE 4096          /* 虚拟页大小 */
#define MEM_MAXPAGE 1000            /* 内存页最大数目 */
#define FILENAME_MAXLEN 256         /* 文件名最大长度 */
#define MAX_CHAR_LENGTH     32      /* 最大 CHAR 类型字段长度 */

#endif