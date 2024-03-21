#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <mbed.h>

typedef int (*queued_function)(unsigned long); // function pointer type

#define queue_schedule_size 11  // max number of items in the queue

// struct to hold the function pointer and the time to run
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
	const uint8_t MAX_ID_LENGTH = 7; // max length of the id string
	queue_item schedule[queue_schedule_size]; // array to hold the scheduled functions

	int queue_get_top(queue_item &item);  // get the top item from the queue
	int add_to_queue(queue_item item);  // add an item to the queue

public:
	Scheduler(); // constructor

	// function to schedule a function to run at a certain time
	int schedule_function(queued_function func, const char * id, unsigned long initial_run, unsigned long recur);
	// function to remove a function from the schedule
	int schedule_remove_function(const char * id);
	// function to change the time and recur time of a scheduled function
	int schedule_change_function(const char * id, unsigned long next_run_time, unsigned long new_recur);
	// start the scheduler
	int Run(unsigned long now);

};

#endif /* SCHEDULER_H */