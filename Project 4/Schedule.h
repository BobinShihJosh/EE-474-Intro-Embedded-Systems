#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED

#include "TCB.h"
#include <iostream>
#include <cstdlib>

extern TCB* list;

void schedule(TCB *taskLinkedList);
void insert(TCB *node);
void deleteTask(TCB *node);
void initSchedule(TCB *node);

#endif