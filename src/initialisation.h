#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "Scheduler.h"
#include "tasks.h"
#include "system.h"

enum INIT_status {
    INIT_FAIL,
    INIT_SUCCESS,
};

extern Scheduler g_scheduler;
extern SPI g_sw; //For the LEDS, controlled using SPI
extern DigitalOut lat;

INIT_status INIT_Tasks(void);
INIT_status INIT_GRLEDs(void);

#endif /* INITIALISATION_H */