#include "taskqueue.h"
#include <time.h>
#include <stdio.h>
//#include <Arduino.h>
void initTaskQueue(Taskqueue* queue) {
    queue -> head = NULL;
    queue -> tail = NULL;
    queue -> initial=NULL;
    queue -> length = 0;
}

void insert_queue(Taskqueue* queue, TCB* node ){

if (queue->head==NULL)
    {
        queue->head=node;
        queue->tail=node;
        queue->initial=node; //record the initial position of the task queue
    }
    else
    {
        queue->tail->next = node;
        node->prev = queue->tail;
        queue->tail = node;
    }
    return;
}

//TCB* delete_queue(Taskqueue* queue);

TCB* getNextTCB(Taskqueue* queue){

TCB* tmp;
tmp = queue->head;
if (queue->head == NULL)
    printf("No task queue available.\n");
else if (queue->head->next!=NULL)
        queue->head = queue->head->next;
    else
        queue->head = queue->initial;

return tmp;

}


