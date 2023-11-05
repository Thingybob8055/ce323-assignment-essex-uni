#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <mbed.h>

typedef int (*queuedFunction)(unsigned long);

#define QueueScheduleSize 11

struct queueItem {
	queuedFunction fPtr;
	unsigned long next;
	unsigned long recur;
	char itemName[8];
};

class Scheduler
{
private:
	unsigned int _queueStart;
	unsigned int _queueEnd;
	unsigned int _itemsInQueue;
	const uint8_t MAX_ID_LENGTH = 7;
	queueItem _schedule[QueueScheduleSize];

	int _queueGetTop(queueItem &item);
	int _addToQueue(queueItem item);

public:
	Scheduler();

	int scheduleFunction(queuedFunction func, const char * id, unsigned long initialRun, unsigned long recur);
	int scheduleRemoveFunction(const char * id);
	int scheduleChangeFunction(const char * id, unsigned long nextRunTime, unsigned long newRecur);

	int Run(unsigned long now);

};

#endif