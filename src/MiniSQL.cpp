#include "API.h"
#include "MiniSQL.h"
#include "helper.h"

int main()
{
    API api;
    cout << "+-------------------------+\n" ;
    cout << "| Welcome to use MiniSQL. |\n";
    cout << "+-------------------------+\n";
    cout << flush;    
    while(1)
    {
        cout << "MiniSQL> " << flush;
        if (api.getInput() < 0) {
            sql_error("Command format error");
            continue;
        }
        switch (api.commandType()) {
            case NONE:
                break;
            case CREATE_TABLE:
                api.createTable();
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