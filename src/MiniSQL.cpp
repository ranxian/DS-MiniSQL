#include "API.h"
#include "MiniSQL.h"

int main()
{
    API api;
    printf("+-------------------------+\n");
    printf("| Welcome to use MiniSQL. |\n");
    printf("+-------------------------+\n");
    while(1)
    {
        switch (api.getInput()) {
            case NONE:
                break;
            case CREATE_TABLE:
                break;
            case DROP_TABLE:
                api.dropTable();
                break;
            case UPDATE:
                api.update();
                break;
            case SELECT:
                api.select();
                break;
            case INSERT:
                api.insert();
                break;
            case DELETE:
                api.deleteRecord();
                break;
            case QUIT:
                api.exit();
                break;
            case HELP:
                api.help();
                break;
            default:
                break;
        }
    }

    return 0;
}