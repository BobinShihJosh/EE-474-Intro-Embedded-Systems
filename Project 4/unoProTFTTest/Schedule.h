#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED

#include "TCB.h"
#include "bool.h"
#include <iostream>
#include <cstdlib>
#include "data.h"

extern TCB* list;
// extern Bool taskFlags[8];

void schedule();
void insert(TCB *node);
void deleteTask(TCB *node);

#endif