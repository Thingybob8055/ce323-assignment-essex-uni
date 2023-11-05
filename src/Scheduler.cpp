#include "Scheduler.h"

Scheduler::Scheduler()
{
    _itemsInQueue = 0;
    _queueStart = 0;
    _queueEnd = 0;
}

int Scheduler::scheduleFunction(queuedFunction func, const char * id, unsigned long initialRun, unsigned long recur)
{
	int rv = 0;

    if(strlen(id) > this->MAX_ID_LENGTH)
    {
        rv = -1;
    } else {

    	queueItem newItem;
    	newItem.fPtr = func;
    	memset(newItem.itemName, 0, 8);
    	memcpy(newItem.itemName, id, strlen(id));
    	newItem.recur = recur;
    	newItem.next = initialRun;

    	rv = _addToQueue(newItem);
    }

	return rv;
}

int Scheduler::scheduleRemoveFunction(const char * id)
{
	queueItem target;
    int rv = -1;
    for (unsigned int i = 0; i < _itemsInQueue; ++i)
    {
        if(_queueGetTop(target) == 0)
        {
            if(strcmp(target.itemName, id) == 0)
            {
                rv = 0;
            } else {
                _addToQueue(target);
            }
        } else {
            rv = -1;
            break;
        }
    }

    return rv;
}

int Scheduler::scheduleChangeFunction(const char * id, unsigned long nextRunTime, unsigned long newRecur)
{
	queueItem target;
    int rv = -1;
    for (unsigned int i = 0; i < _itemsInQueue; ++i)
    {
        if(_queueGetTop(target) == 0)
        {
            if(strcmp(target.itemName, id) == 0)
            {
                target.next = nextRunTime;
                target.recur = newRecur;
                rv = 0;
            }
            _addToQueue(target);
        } else {
            rv = -1;
            break;
        }
    }

    return rv;
}

int Scheduler::Run(unsigned long now)
{
	queueItem target;
    int rv = 0;
    if(_itemsInQueue == 0)
    {
        rv = -1;
    }
    for (unsigned int i = 0; i < _itemsInQueue; ++i)
    {
        if(_queueGetTop(target)==0)
        {
            if(target.next <= now)
            {
                int tRv;
                tRv = (target.fPtr)(now);
                if(tRv == 0)
                {
                    rv++;
                }
                if(target.recur != 0)
                {
                    target.next = now + target.recur;
                    _addToQueue(target);
                }
            } else {
                _addToQueue(target);
            }
        } else {
            rv = -1;
            break;
        }
    }

    return rv;
}

int Scheduler::_queueGetTop(queueItem &item)
{
	int rv = 0;
    //Remove the top item, stuff it into item
    if (_queueEnd != _queueStart) {
            queueItem tempQueueItem = _schedule[_queueStart];
            _queueStart = (_queueStart + 1) % QueueScheduleSize;
            item = tempQueueItem;
            _itemsInQueue--;
    } else {
    //if the buffer is empty, return an error code
        rv = -1;
    }

    return rv;  
}

int Scheduler::_addToQueue(queueItem item)
{
	//Algorithm is shown in wikipedia article on circular buffers
	int rv = 0;
    if ((_queueEnd + 1) % QueueScheduleSize != _queueStart) {
        _schedule[_queueEnd] = item;
        _queueEnd = (_queueEnd + 1) % QueueScheduleSize;
        _itemsInQueue++;
    } else {
        //if buffer is full, error
        rv = -1;
    }
    return rv;
}