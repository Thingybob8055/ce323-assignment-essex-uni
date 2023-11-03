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

INIT_status INIT_Tasks(void);

#endif /* INITIALISATION_H */