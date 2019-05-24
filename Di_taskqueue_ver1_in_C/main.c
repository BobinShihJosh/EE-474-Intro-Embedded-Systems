#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "globals.h"
#include "bool.h"
#include "TCB.h"
#include "scheduler.h"
#include "taskqueue.h"

#define LENGTH 8

#define MEASURE_TCB 0
#define COMPUTE_TCB 1
#define WARNINGALARM_TCB 2
#define DISPLAY_TCB 3
#define STATUS_TCB 4
#define COMMUNICATION_TCB 5
#define TFTKEYPAD_TCB 6

TCB tcbs[LENGTH];
void test_delay();

int main()
{
    Scheduler scheduler;
    Taskqueue queue; //define a queue struct
    init();
    initTaskQueue(&queue); //initialize queue struct, values inside the queue can be shared and accessed through different functions
    initScheduler(&scheduler);

  initTCB(&tcbs[TFTKEYPAD_TCB], (void*)&tftData, TFTkeypadSubsystemFunction, PRIORITY_HIGH);
  //initTCB(&tcbs[MEASURE_TCB], (void*)&measureData, MeasureSubsystemFunction, PRIORITY_LOW);
 // initTCB(&tcbs[COMPUTE_TCB], (void*)&computeData, ComputeSubsystemFunction, PRIORITY_LOW);
  initTCB(&tcbs[WARNINGALARM_TCB], (void*)&warningAlarmData, WarningAlarmSubsystemFunction, PRIORITY_HIGH);
  initTCB(&tcbs[DISPLAY_TCB], (void*)&displayData, DisplaySubsystemFunction, PRIORITY_LOW);
  initTCB(&tcbs[STATUS_TCB], (void*)&statusData, StatusSubsystemFunction, PRIORITY_LOW);
//  initTCB(&tcbs[COMMUNICATION_TCB], (void*)&communicationData, CommunicationSubsystemFunction, PRIORITY_LOW);
    insert_queue(&queue,&tcbs[TFTKEYPAD_TCB]);
    insert_queue(&queue,&tcbs[WARNINGALARM_TCB]);
    insert_queue(&queue,&tcbs[DISPLAY_TCB]);
    insert_queue(&queue,&tcbs[STATUS_TCB]);

    while(1)
    {
        scheduleAndRun(&scheduler, &queue);
        test_delay(1);
    }
    return 0;
}

void test_delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
}
