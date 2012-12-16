#include "MiniSQL.h"

int main()
{
    Init();             // 初始化一些参数
    Run();              // 运行数据库
    Exit();             // 善后
}

void Init()
{
    return;
}

void Run()
{
    Interpreter itprtr;
    while (true) {
        itprtr.inputCommand();
        itprtr.parseCommand();
        int command_type = itprtr.getCommandType();
        if (command_type == QUIT) break;

        switch (command_type) {
            case CREATE_TABLE:
                createTable(&itprtr.getInfo());
                break;
            case CREATE_INDEX:
                createIndex(&itprtr.getInfo());
                break;
            case CREATE_DATABASE:
                createDatabse(&itprtr.getInfo());
                break;
            case SELECT:
                select(&itprtr.getInfo());
                break;
            case INSERT:
                insert(&itprtr.getInfo());
                break;
            case DROP_TABLE:
                dropTable(&itprtr.getInfo());
                break;
            case DROP_INDEX:
                dropIndex(&itprtr.getInfo());
                break;
            case DROP_DATABASE:
                dropDatabase(&itprtr.getInfo());
                break;
            case DELETE:
                deleteRecord(&itprtr.getInfo());
                break;
            case EXECFILES:
                /* 这个是干么用的？ */
                break;
            case QUIT:
                return;
            default:
                return;
        }
    }
    return;
}

void Exit()
{   
    cout << "Existing MiniSQL..." << endl;
    cout << "Bye..." << endl;

    return;
}

void createTable(Information_t *info) {
    catalog_manager.create(info);
    // 创建表（Record）
    // 建立索引（Index）
    // 保存表信息（Catalog）
}
void createIndex(Information_t *info) {
    // 得到表信息
    // 建立索引
    // 保存表信息
}
void createDatabse(Information_t *info) {
    // 暂时不考虑这个功能
}
void select(Information_t *info) {
    // 得到表、索引信息
    // 去B+树搜索
    // 去Record取数据
    // 打印
}
void insert(Information_t *info) {
    // 得到表，索引信息
    // 去Record插入数据
    // 去B+数插入索引
    // Catalog保存表的信息
}
void dropTable(Information_t *info) {
    // 得到表、索引信息
    // 去Record删除数据
    // 去B+树删除索引
    // catalog 抛弃表的信息
}
void dropDatabase(Information_t *info) {
    // 也不考虑这个功能
}
void deleteRecord(Information_t *info) {
    // 得到表，索引信息
    // 去B+树删索引
    // 用这个索引去删数据
    // Catalog保存表的信息
}
void execfiles(Information_t *info) {
    // 暂时不要这个功能
}
