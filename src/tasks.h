#ifndef TASKS_H
#define TASKS_H

#include "mbed.h"
#include "system.h"
#include "TextLCD.h"
#include "keypad_control.h"

extern DigitalOut g_alarm_led;
extern alarm_state_t g_alarm_state;
extern uint8_t g_alarm_led_state;
extern TextLCD g_lcd;
extern KeypadControl g_keypad_control;
extern Timer g_timer;

int alarm_led_blink(unsigned long now);
int lcd_display(unsigned long now);
int enter_code(unsigned long now);

#endif /* TASKS_H */