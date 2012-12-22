#include "../src/API.h"
#include "../src/MiniSQL.h"
#include "../src/Interpreter.h"

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
