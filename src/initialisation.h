#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "scheduler.h"
#include "tasks.h"
#include "system.h"

// enum to return the status of the initialisation functions
enum INIT_status {
    INIT_FAIL,
    INIT_SUCCESS,
};

// global variables from main.cpp
extern Scheduler g_scheduler;
extern SPI g_sw;
extern DigitalOut lat;

// initialisation functions
INIT_status INIT_Tasks(void);
INIT_status INIT_GRLEDs(void);

#endif /* INITIALISATION_H */