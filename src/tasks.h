#ifndef TASKS_H
#define TASKS_H

#include "mbed.h"

extern DigitalOut g_myled;
extern DigitalOut g_myled2;
extern DigitalOut g_myled3;
extern DigitalOut g_myled4;
extern uint8_t g_state_1;
extern uint8_t g_state_2;
extern uint8_t g_state_3;
extern uint8_t g_state_4;


int testFunction(unsigned long now);

int testFunction2(unsigned long now);

int testFunction3(unsigned long now);

int testFunction4(unsigned long now);

#endif /* TASKS_H */