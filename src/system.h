#ifndef SYSTEM_H
#define SYSTEM_H


const int TEST_FUNC1_REFRESH_MS = 500;
const int TEST_FUNC2_REFRESH_MS = 3000;
const int TEST_FUNC3_REFRESH_MS = 100;
const int TEST_FUNC4_REFRESH_MS = 1000;

typedef enum ALARM_SYSTEM_STATE {
    UNSET_STATE,
    EXIT_STATE,
    SET_STATE,
    ENTRY_STATE,
    ALARM_STATE,
    REPORT_STATE
} alarm_state_t;

#endif /* SYSTEM_H */