#ifndef TASKS_H
#define TASKS_H

#include "mbed.h"
#include "system.h"
#include "TextLCD.h"
#include "keypad_control.h"
#include <vector>

// global variables from main.cpp
extern DigitalOut g_alarm_led;
extern alarm_state_t g_alarm_state;
extern TextLCD g_lcd;
extern KeypadControl g_keypad_control;
extern Timer g_timer;

extern BusOut g_switch_cs;
extern BusIn g_switch_reading; //These two are for switches
extern SPI g_sw;
extern DigitalOut lat;

extern BufferedSerial g_pc;

// total number of characters the LCD screen can display in a single line
constexpr int total_no_of_char = 16;

// function prototypes for the scheduled tasks
int state_handler(unsigned long now);
int lcd_display(unsigned long now);
int enter_code(unsigned long now);
int read_switches(unsigned long now);

#endif /* TASKS_H */