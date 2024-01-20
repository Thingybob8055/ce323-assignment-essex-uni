#include "initialisation.h"

INIT_status INIT_Tasks(void) {
    int8_t rv = 0;
    rv |= g_scheduler.scheduleFunction(alarm_led_blink, "led", 1000, ALARM_LED_MS);
    rv |= g_scheduler.scheduleFunction(lcd_display, "lcd", 1000, LCD_REFRESH_MS);
    rv |= g_scheduler.scheduleFunction(enter_code, "keypad", 1000, KEYPAD_POLL_MS);
    rv |= g_scheduler.scheduleFunction(read_switches, "switch", 1000, 100);

    if(rv == -1)
        return INIT_FAIL;
    else
        return INIT_SUCCESS;
}

INIT_status INIT_GRLEDs(void) {
    lat = 0;
    g_sw.format(16,0);
    g_sw.frequency(1000000);
    return INIT_SUCCESS;
}