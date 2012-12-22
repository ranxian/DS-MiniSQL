#include "API.h"

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