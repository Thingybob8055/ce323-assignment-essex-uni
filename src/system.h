#ifndef SYSTEM_H
#define SYSTEM_H

#include <map>
#include <string>

/* System configuration related stuff goes here */

// refresh rates for the tasks
constexpr int ALARM_LED_MS = 500;
constexpr int LCD_REFRESH_MS = 200;
constexpr int KEYPAD_POLL_MS = 100;
constexpr int SWITCH_POLL_MS = 100;

// alarm system states
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

static const std::string password = "1234";  // password for the alarm system

constexpr int EXIT_INTERVAL_MS = 60000;  // exit interval in milliseconds

constexpr int ENTRY_INTERVAL_MS = 60000;  // entry interval in milliseconds

constexpr int ALARM_LED_ON_INTERVAL_MS = 120000; // alarm led on interval in milliseconds (for alarm state)

/**< Set to true to show main top level logic debug output on Serial */
#define  SYS_DEBUG_APP_LOGIC    false
#if SYS_DEBUG_APP_LOGIC
    #define debug_printf(...)    printf(__VA_ARGS__)
#else
    #define debug_printf(...)
#endif

#endif /* SYSTEM_H */