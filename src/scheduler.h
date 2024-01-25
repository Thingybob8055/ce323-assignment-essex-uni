#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <mbed.h>

typedef int (*queued_function)(unsigned long);

#define queue_schedule_size 11

struct queue_item {
	queued_function f_ptr;
	unsigned long next;
	unsigned long recur;
	char item_name[8];
};

class Scheduler
{
private:
	unsigned int queue_start;
	unsigned int queue_end;
	unsigned int items_in_queue;
	const uint8_t MAX_ID_LENGTH = 7;
	queue_item schedule[queue_schedule_size];

	int queue_get_top(queue_item &item);
	int add_to_queue(queue_item item);

public:
	Scheduler();

	int schedule_function(queued_function func, const char * id, unsigned long initial_run, unsigned long recur);
	int schedule_remove_function(const char * id);
	int schedule_change_function(const char * id, unsigned long next_run_time, unsigned long new_recur);

	int Run(unsigned long now);

};

#endif /* SCHEDULER_H */