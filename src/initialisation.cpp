#include "initialisation.h"

INIT_status INIT_Tasks(void) {
    int8_t rv = 0;
    rv |= g_scheduler.scheduleFunction(alarm_led_blink, "led", 1000, ALARM_LED_MS);
    rv |= g_scheduler.scheduleFunction(lcd_display, "lcd", 1000, LCD_REFRESH_MS);

    if(rv == -1)
        return INIT_FAIL;
    else
        return INIT_SUCCESS;
}
