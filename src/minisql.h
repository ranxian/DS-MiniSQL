#include "Interpreter.h"
#include <string>
#include <iostream>
using namespace std;
Catalog catlog_manager;

void Init();
void Run();
void Exit();
void createTable(Information_t *info);
void createIndex(Information_t *info);
void createDatabse(Information_t *info);
void select(Information_t *info);
void insert(Information_t *info);
void dropTable(Information_t *info);
void dropIndex(Information_t *info);
void dropDatabase(Information_t *info);
void deleteRecord(Information_t *info);
void execfiles(Information_t *info);