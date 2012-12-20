#include "API.h"
#include "MiniSQL.h"
#include "Interpreter.h"

int main()
{
    Interpreter itp;
    while(1)
    {
        if (itp.inputCommand())
         itp.debug();
    }

    return 0;
}