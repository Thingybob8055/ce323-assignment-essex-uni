#include "initialisation.h"

INIT_status INIT_Tasks(void) {
    int8_t rv = 0;  // return value from scheduler functions
    // schedule tasks in the scheduler
    rv |= g_scheduler.schedule_function(state_handler, "led", 1000, ALARM_LED_MS);
    rv |= g_scheduler.schedule_function(lcd_display, "lcd", 1000, LCD_REFRESH_MS);
    rv |= g_scheduler.schedule_function(enter_code, "keypad", 1000, KEYPAD_POLL_MS);
    rv |= g_scheduler.schedule_function(read_switches, "switch", 1000, SWITCH_POLL_MS);

    // check if any of the tasks failed to schedule
    if(rv == -1)
        return INIT_FAIL;
    else
        return INIT_SUCCESS;
}

// Initialise the red/green LEDs from the mbed board
INIT_status INIT_GRLEDs(void) {
    lat = 0;
    g_sw.format(16,0);
    g_sw.frequency(1000000);
    return INIT_SUCCESS;
}