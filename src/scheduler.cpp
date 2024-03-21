#include "scheduler.h"

Scheduler::Scheduler()
{
    items_in_queue = 0; // initialise variables from the constructor
    queue_start = 0;
    queue_end = 0;
}

int Scheduler::schedule_function(queued_function func, const char * id, unsigned long initial_run, unsigned long recur)
{
	int rv = 0;

    if(strlen(id) > this->MAX_ID_LENGTH) // check if the id is too long
    {
        rv = -1;
    } else {
        // create a new queue item and fill it with the function pointer, next run time, recur time and id
    	queue_item new_item;
    	new_item.f_ptr = func;
    	memset(new_item.item_name, 0, 8);
    	memcpy(new_item.item_name, id, strlen(id));
    	new_item.recur = recur;
    	new_item.next = initial_run;

    	rv = add_to_queue(new_item); // add the new item to the queue
    }

	return rv;
}

int Scheduler::schedule_remove_function(const char * id)
{
	queue_item target;
    int rv = -1;
    // loop through the queue and remove the item with the matching id
    for (unsigned int i = 0; i < items_in_queue; ++i)
    {
        if(queue_get_top(target) == 0)
        {
            if(strcmp(target.item_name, id) == 0)
            {
                rv = 0;
            } else {
                add_to_queue(target);
            }
        } else {
            rv = -1;
            break;
        }
    }

    return rv;
}

int Scheduler::schedule_change_function(const char * id, unsigned long next_run_time, unsigned long new_recur)
{
	queue_item target;
    int rv = -1;
    // loop through the queue and change the next run time and recur time of the item with the matching id
    for (unsigned int i = 0; i < items_in_queue; ++i)
    {
        if(queue_get_top(target) == 0)
        {
            if(strcmp(target.item_name, id) == 0)
            {
                target.next = next_run_time;
                target.recur = new_recur;
                rv = 0;
            }
            add_to_queue(target);
        } else {
            rv = -1;
            break;
        }
    }

    return rv;
}

int Scheduler::Run(unsigned long now)
{
	queue_item target;
    int rv = 0;
    // if there are no items in the queue, return an error code
    if(items_in_queue == 0)
    {
        rv = -1;
    }
    // loop through the queue and run the functions that are due
    for (unsigned int i = 0; i < items_in_queue; ++i)
    {
        if(queue_get_top(target)==0)
        {
            if(target.next <= now)
            {
                int trv;
                trv = (target.f_ptr)(now);
                if(trv == 0)
                {
                    rv++;
                }
                if(target.recur != 0)
                {
                    target.next = now + target.recur;
                    add_to_queue(target);
                }
            } else {
                add_to_queue(target);
            }
        } else {
            rv = -1;
            break;
        }
    }

    return rv;
}

int Scheduler::queue_get_top(queue_item &item)
{
	int rv = 0;
    //Remove the top item, stuff it into item
    if (queue_end != queue_start) {
            queue_item temp_queue_item = schedule[queue_start];
            queue_start = (queue_start + 1) % queue_schedule_size;
            item = temp_queue_item;
            items_in_queue--;
    } else {
    //if the buffer is empty, return an error code
        rv = -1;
    }

    return rv;  
}

int Scheduler::add_to_queue(queue_item item)
{
	//circular buffer is used to store the scheduled functions
	int rv = 0;
    if ((queue_end + 1) % queue_schedule_size != queue_start) {
        schedule[queue_end] = item;
        queue_end = (queue_end + 1) % queue_schedule_size;
        items_in_queue++;
    } else {
        //if buffer is full, error
        rv = -1;
    }
    return rv;
}