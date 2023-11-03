#include "tasks.h"

int testFunction(unsigned long now)
{
    g_state_1 = !g_state_1;
    g_myled = g_state_1;
    // pc.write("testFunction called!\n", 21);
    return 1;
}

int testFunction2(unsigned long now)
{
    g_state_2 = !g_state_2;
    g_myled2 = g_state_2;
    // pc.write("testFunction2 called!\n", 22);
    return 0;
}

int testFunction3(unsigned long now)
{
    g_state_3 = !g_state_3;
    g_myled3 = g_state_3;
    // pc.write("testFunction3 called!\n", 22);
    return 0;
}

int testFunction4(unsigned long now)
{
    g_state_4 = !g_state_4;
    g_myled4 = g_state_4;
    // pc.write("testFunction4 called!\n", 22);
    return 0;
}