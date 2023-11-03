#include "initialisation.h"

INIT_status INIT_Tasks(void) {
    int8_t rv = 0;
    rv |= g_scheduler.scheduleFunction(testFunction, "test", 1000, TEST_FUNC1_REFRESH_MS);
    rv |= g_scheduler.scheduleFunction(testFunction2, "test2", 1000, TEST_FUNC2_REFRESH_MS);
    rv |= g_scheduler.scheduleFunction(testFunction3, "test3", 1000, TEST_FUNC3_REFRESH_MS);
    rv |= g_scheduler.scheduleFunction(testFunction4, "test4", 1000, TEST_FUNC4_REFRESH_MS);

    if(rv == -1)
        return INIT_FAIL;
    else
        return INIT_SUCCESS;
}
