#ifndef TASKQUEUE_H_INCLUDED
#define TASKQUEUE_H_INCLUDED

#include "TCB.h"

typedef struct Taskqueue
{
    TCB* head;
    TCB* tail;
    TCB* initial; //record the initial position of the task queue
    int length;
} Taskqueue;

void initTaskQueue(Taskqueue* queue);
void insert_queue(Taskqueue* queue, TCB* tcb);
TCB* delete_queue(Taskqueue* queue);
TCB* getNextTCB(Taskqueue* queue);


#endif // TASKQUEUE_H_INCLUDED
