#include "tasks.h"

// TODO: Set count library
int alarm_led_blink(unsigned long now) {
    switch (g_alarm_state) {
        case UNSET_STATE:
            // g_alarm_led = (led_state = !led_state);
            //convert the above 2 lines to a one li
            // g_alarm_led = !g_alarm_led;
            g_alarm_led = 0;
            break;
        default:
            break;
    }

    // pc.write("testFunction called!\n", 21);
    return 1;
}

int lcd_display(unsigned long now) {
    g_lcd.cls();
    g_lcd.locate(0, 0);
    g_lcd.printf("%s", alarm_state_map[g_alarm_state]);
    return 1;
}