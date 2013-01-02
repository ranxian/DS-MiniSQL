#include "API.h"
#include "helper.h"
using namespace std;
API::API() 
{
    interpreter = new Interpreter;
    catalog_manager = new Catalog;
    index_manager = new Index;
    record_manager = new Record;
}

API::~API()
{
    delete interpreter;
    delete catalog_manager;
    delete index_manager;
    delete record_manager;
}

int API::createTable() {
    info_t info;

    info = interpreter->getInfo();
    string tableName = info.tableName;

    if (catalog_manager->tableExist(tableName)) {
        sql_error("TABLE \"" + tableName + "\" has already exsited");
        return -1;
    } else {
        catalog_manager->createTable(info.t);
        table_t table = catalog_manager->findTable(tableName);
        for (int i = 0; i < table.attrNum; i++) {
            index_manager->createIndex(
                tableName,
                table.attributes[i].name,
                table.attributes[i]
            );
        }
    }

    sql_msg("TABLE \"" + tableName + "\" created");
    return 0;
}

int API::createIndex() {
    info_t info = interpreter->getInfo();

    string tableName = info.tableName;
    string indexName = info.indexName;

    return 0;
}

// V
int API::select() {
    info_t info = interpreter->getInfo();
    table_t table = info.t;

    record_t *records = record_manager->Select(info);

    if (records != NULL)
        record_manager->PrintHead(table);

    record_manager->Print(records);
    return 0;
}

int API::insert() {
    info_t info = interpreter->getInfo();
    index_node_t node; 
    node.offset = record_manager->Insert(info);

    for (map<string, string>::iterator iter = info.insertItems.begin();
        iter != info.insertItems.end(); iter++) {

        node.value = iter->second;
        index_manager->insertIndex(info.tableName, iter->first, node);    
    }

    return 0;
}

// V
int API::dropTable() {
    info_t info = interpreter->getInfo();

    catalog_manager->deleteTable(info.t);
    // TODO: record_manager->deleteTable(info.t)

    return 0;
}

// no sign to delete
int API::deleteRecord() {
    info_t info = interpreter->getInfo();
    index_node_t res;

    record_manager->Delete(info, res);

    // index_node_t *todel = getIndex(info.tableName, info.tree);
    // table_t table = catalog_manager->findTable(info.tableName);

    // while (todel) {
    //     for (int i = 0; i < table.attrNum; i++)
    //         index_manager->deleteIndex(info.tableName, table.attributes[i].name, todel->value);
    // }

    return -1;
}

// V
int API::getInput() {
    if (interpreter->inputCommand())
        return 0;
    else return -1;
}

// V
int API::exit() {
    return -1;
}

// V
void API::help() {
    printf("This is the manul\n");
}

int API::update() {
    info_t info = interpreter->getInfo();
    index_node_t res;

    record_manager->Update(info, res);
    return 0;
}

cmd_t API::commandType() {
    return interpreter->getInfo().command;
};

index_node_t* API::getIndex(string tableName, condition_tree_t *node) {
    index_node_t *res = new index_node_t;
    index_node_t **temp = new index_node_t*[2];

    if (node->end) {
        index_manager->selectIndex(tableName, node, res);
    } else {
        index_node_t *res1 = getIndex(tableName, node->left);
        index_node_t *res2 = getIndex(tableName, node->right);
        temp[0] = res1;
        temp[1] = res2;
        if (node->logic == AND) {
            index_manager->mergeIndexAND(temp, 2, res);
        } else {
            index_manager->mergeIndexOR(temp, 2, res);
        }
    }
    return res;
}
