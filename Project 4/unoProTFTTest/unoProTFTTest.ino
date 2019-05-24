#include <Arduino.h>
#include "TCB.h"
#include "taskqueue.h"
#include "scheduler.h"
#include "bool.h"

//Define struct of Measurement system
typedef struct MeasureSubsystemData{
    unsigned int *temperatureRawPtr;
    unsigned int *systolicPressRawPtr;
    unsigned int *diastolicPressRawPtr;
    unsigned int *pulseRateRawPtr;

} measureSubsystemData;

//Measurements initial value
unsigned int temperatureRaw = 75;
unsigned int systolicPressRaw = 80;
unsigned int diastolicPressRaw = 80;
unsigned int pulseRateRaw = 50;
    //define BOOL flag
    bool even = true;
    bool tempReverse = FALSE;
    bool pulseReverse = FALSE;
    bool systolicFlag = FALSE;
    bool diastolicFlag = FALSE;

#define LENGTH 1
long long MAJOR_CYCLE = 1000;
long long MINOR_CYCLE = 100;
Scheduler scheduler;
Taskqueue queue;

//globals init function setup
void init();
void initMeasureData();

//TCB function setup
void invoke(TCB* tcb);
void intiTCB(TCB* tcb,void* taskDataPtr, void (*taskPtr)(void*),TaskPriority priority);

//Taskqueue function
void initTaskQueue(Taskqueue* queue, TCB* tcbArray, int length);
TCB* getNextTCB(Taskqueue* queue);

//Scheduler function setup
void scheduleAndRun (Scheduler* scheduler, Taskqueue* queue);
void initScheduler(Scheduler* scheduler);

//MeasureSubsystemFunction function setup
void MeasureSubsystemFunction(void* data);
char intByte;

void setup() {
  Serial.begin(9600);           // start serial for output
  //Create struct name for initialization
  measureSubsystemData measureData;
  
  TCB tcbs[LENGTH];
  initScheduler(&scheduler);
  measureData.temperatureRawPtr = &temperatureRaw;
  measureData.systolicPressRawPtr = &systolicPressRaw;
  measureData.diastolicPressRawPtr = &diastolicPressRaw;
  measureData.pulseRateRawPtr = &pulseRateRaw;
  initTCB(&tcbs[0],(void*)&measureData,MeasureSubsystemFunction,PRIORITY_LOW);
  initTaskQueue(&queue,tcbs,LENGTH);
  Serial.println("Setup Finishes!");
}

void loop() {
    
  if (Serial.available()>0)
    intByte = Serial.read();
  if (intByte == 'A') //'A' is the flag to run MeasureFunction in Uno
    scheduleAndRun(&scheduler,&queue);
   delay(500);
}

//MeasureSubsystemFunction definintion
void MeasureSubsystemFunction(void* data) {
    //cast c_ptr to computeData structure type...
      measureSubsystemData* measureData = (measureSubsystemData*) data;

      if (even) {
        // tempRaw
        if (tempReverse) {
            if (*(unsigned int*)(measureData->temperatureRawPtr) < 15) {
                tempReverse = !tempReverse;
            } else {
                *(unsigned int*)(measureData->temperatureRawPtr) -= 2;
            }
        } else {
            if (*(unsigned int*)(measureData->temperatureRawPtr) > 50) {
                tempReverse = !tempReverse;
            } else {
                *(unsigned int*)(measureData->temperatureRawPtr) += 2;
            }
        }
      
        // systolicPressRaw
        if (*(unsigned int*)(measureData->systolicPressRawPtr) > 97) {
            *(unsigned int*)(measureData->systolicPressRawPtr) = 80;
            systolicFlag = true; //set variable not sure, may be just local
        } else {
            *(unsigned int*)(measureData->systolicPressRawPtr) += 3;
        }

        // diastolicPressRaw
        if (*(unsigned int*)(measureData->diastolicPressRawPtr) < 40) {
            diastolicFlag = true;//set variable not sure, may be just local
            *(unsigned int*)(measureData->diastolicPressRawPtr) = 80;
        } else {
            *(unsigned int*)(measureData->diastolicPressRawPtr) -= 2;
        }

        //pulseRateRaw
        if (pulseReverse) {
            if (*(unsigned int*)(measureData->pulseRateRawPtr) < 15) {
                pulseReverse = !pulseReverse;
            } else {
                *(unsigned int*)(measureData->pulseRateRawPtr) += 1;
            }
        } else {
            if (*(unsigned int*)(measureData->pulseRateRawPtr) > 40) {
                pulseReverse = !pulseReverse;
            } else {
                *(unsigned int*)(measureData->pulseRateRawPtr) -= 1;
            }
        }
      

      } else {
        // tempRaw
        if (tempReverse) {
            if (*(unsigned int*)(measureData->temperatureRawPtr) < 15) {
                tempReverse = !tempReverse;
            } else {
                *(unsigned int*)(measureData->temperatureRawPtr) += 1;
            }
        } else {
            if (*(unsigned int*)(measureData->temperatureRawPtr) > 50) {
                tempReverse = !tempReverse;
            } else {
                *(unsigned int*)(measureData->temperatureRawPtr) -= 1;
            }
        }
        
        // systolicPressRaw
        if (*(unsigned int*)(measureData->systolicPressRawPtr) > 97) {
            *(unsigned int*)(measureData->systolicPressRawPtr) = 80;
            systolicFlag = true;//set variable not sure, may be just local
        } else {
            *(unsigned int*)(measureData->systolicPressRawPtr) -= 1;
        }

        // diastolicPressRaw
        if (*(unsigned int*)(measureData->diastolicPressRawPtr) < 40) {
            diastolicFlag = true;//set variable not sure, may be just local
            *(unsigned int*)(measureData->diastolicPressRawPtr) = 80;
        } else {
            *(unsigned int*)(measureData->diastolicPressRawPtr) += 1;
        }

        //pulseRateRaw
        if (pulseReverse) {
            if (*(unsigned int*)(measureData->pulseRateRawPtr) < 15) {
                pulseReverse = !pulseReverse;
            } else {
                *(unsigned int*)(measureData->pulseRateRawPtr) -= 3;
            }
        } else {
            if (*(unsigned int*)(measureData->pulseRateRawPtr) > 40) {
                pulseReverse = !pulseReverse;
            } else {
                *(unsigned int*)(measureData->pulseRateRawPtr) += 3;
            }
        } 
            
    }   
    even = !even;
Serial.print(*(measureData->temperatureRawPtr));
Serial.print(*(measureData->systolicPressRawPtr));
Serial.print(*(measureData->diastolicPressRawPtr));
Serial.println(*(measureData->pulseRateRawPtr));
//Serial.print("06");

}

//TCB function definition
void invoke(TCB* tcb) {
    (tcb -> taskPtr)(tcb -> taskDataPtr);
}

void initTCB(TCB* tcb, void* taskDataPtr, void (*taskPtr)(void*), TaskPriority priority) {
    tcb -> taskDataPtr = taskDataPtr;
    tcb -> taskPtr = taskPtr;
    tcb -> priority = priority;
}

//Taskqueue function setup
void initTaskQueue(Taskqueue *queue, TCB* tcbArray, int length){
    queue->tcbArray = tcbArray;
    queue->length = length;
    queue->cur_index=0;
    //printf("Task queue initiated!\n");
}

TCB* getNextTCB(Taskqueue* queue){
    TCB* nextTCB = &(queue->tcbArray)[queue->cur_index];
    queue->cur_index =(queue->cur_index+1)%queue->length;
    return nextTCB;
}

//Schedule And Run function setup
void scheduleAndRun (Scheduler* scheduler, Taskqueue* queue){
    //Serial.println("Running ScheduleAndRun...");
    long long currentTime = millis();

    int isMajor = currentTime>= scheduler->nextEndMajor; //are you after a major cycle
    int isMinor = currentTime>= scheduler->nextEndMinor;

    cycleLevel level = CYCLE_REAL_TIME;

    if (isMinor){
        scheduler->nextEndMinor = currentTime + MINOR_CYCLE;
        level = CYCLE_MINOR;
    }
    if (isMajor){
        scheduler->nextEndMajor = currentTime +  MAJOR_CYCLE;
        level = CYCLE_MAJOR;
    }

    for (int i=0;i<queue->length;i++){
        TCB* curTCB=getNextTCB(queue);
        if(level == CYCLE_MAJOR){
            invoke(curTCB);
        }
        else if (level == CYCLE_MINOR && curTCB->priority !=PRIORITY_LOW){
            invoke(curTCB);
        }
        else if (level==CYCLE_REAL_TIME && curTCB->priority == PIRORITY_REAL_TIME){
            invoke(curTCB);
        }
    }
}
   void initScheduler(Scheduler* scheduler){
    scheduler->nextEndMajor = 0;
    scheduler->nextEndMinor = 0;
   }
