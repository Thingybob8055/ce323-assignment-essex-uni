#include "tasks.h"

// TODO: SEt count library
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

int testFunction2(unsigned long now) {
    g_state_2 = !g_state_2;
    g_myled2 = g_state_2;
    // pc.write("testFunction2 called!\n", 22);
    return 0;
}

int testFunction3(unsigned long now) {
    g_state_3 = !g_state_3;
    g_myled3 = g_state_3;
    // pc.write("testFunction3 called!\n", 22);
    return 0;
}

int testFunction4(unsigned long now) {
    g_state_4 = !g_state_4;
    g_myled4 = g_state_4;
    // pc.write("testFunction4 called!\n", 22);
    return 0;
}