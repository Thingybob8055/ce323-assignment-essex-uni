#ifndef SYSTEM_H
#define SYSTEM_H

#include <map>
#include <string>

const int ALARM_LED_MS = 500;
const int LCD_REFRESH_MS = 200;
const int KEYPAD_POLL_MS = 100;
const int SWITCH_POLL_MS = 100;
const int CMD_POLL_MS = 100;

typedef enum ALARM_SYSTEM_STATE {
    UNSET_STATE,
    EXIT_STATE,
    SET_STATE,
    ENTRY_STATE,
    ALARM_STATE,
    REPORT_STATE
} alarm_state_t;

//map the alarm state to strings, and is a static variable
static std::map<alarm_state_t, std::string> alarm_state_map = {
    {UNSET_STATE, "UNSET STATE"},
    {EXIT_STATE, "EXIT STATE"},
    {SET_STATE, "SET STATE"},
    {ENTRY_STATE, "ENTRY STATE"},
    {ALARM_STATE, "ALARM STATE"},
    {REPORT_STATE, "REPORT STATE"}
};

static const std::string password = "1234";

constexpr int EXIT_INTERVAL_MS = 3000;

constexpr int ENTRY_INTERVAL_MS = 10000;

constexpr int ALARM_LED_ON_INTERVAL_MS = 60000;

/**< Set to true to show main top level logic debug output on Serial */
#define  SYS_DEBUG_APP_LOGIC    false
#if SYS_DEBUG_APP_LOGIC
    #define debug_printf(...)    printf(__VA_ARGS__)
    // #define debug_println(x)     Serial.println(x)
    // #define debug_print(x)       Serial.print(x)
#else
    #define debug_printf(...)
    // #define debug_println(x)
    // #define debug_print(x)
#endif

#endif /* SYSTEM_H */