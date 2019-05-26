#include "Schedule.h"
#include "TCB.h"
#include "MeasureSubsystem.h"
#include "ComputeSubsystem.h"
#include "WarningAlarmSubsystem.h"


int main() {
    
    initTCB(&TFTkeyPadTCB, (void*)&tftData, TFTkeypadSubsystemFunction);
    TCB measureTCB;
    TCB computeTCB;
    TCB warningTCB;

    measureSubsystemData measureData;
    computeSubsystemData computeData;
    WarningAlarmSubsystemData warningData;
    
    void* measuredata = &measureData;
    void* computedata = &computeData;
    void* warningdata = &warningData;

    measureTCB.taskDataPtr = measuredata;
    computeTCB.taskDataPtr = computedata;
    warningTCB.taskDataPtr = warningdata;
    measureTCB.id = 1;
    computeTCB.id = 44;
    warningTCB.id = 57;

    insert(&measureTCB);

    printf("%d\n",387);

    insert(&computeTCB);

    printf("%d\n",287);

    insert(&warningTCB);


    TCB* cur = list;
    while(cur != NULL) {
        printf("%d\n", cur->id);
        cur = cur->next;
    }
    
    deleteTask(&warningTCB);
    
    TCB* cur2 = list;
    while(cur2 != NULL) {
        printf("%d\n", cur2->id);
        cur2 = cur2->next;
    }

    int age;
    std::cin>>age;

    schedule();
    return 1;
}


// unsigned int alarmCounter = 0; // initial at global

// void MeasureSubsystemFunction(void* data) {
//     if (*(measureSubsystemData->alarmAcknowledgePtr) == 1) {
//         alarmCounter++;
//         if (alarmCounter == 5) {
//             *(measureSubsystemData->alarmAcknowledgePtr) = 0;
//         }
//     }
// }

// #ifndef DISPLAY_H_INCLUDED
// #define DISPLAY_H_INCLUDED

// #include "bool.h"

typedef struct DisplaySubsystemData{
    // Data
    double *tempCorrectedPtr;
    unsigned int *sysCorrectedPtr;
    unsigned int *diasCorrectedPtr;
    unsigned int *prCorrectedPtr;
    unsigned int *rrCorrectedPtr;
    unsigned int *batteryStatePtr;
    // Selection
    unsigned short *functionSelectPtr;
    // Red Ptr
    unsigned char *tempOutOfRangePtr;
    unsigned char *bpOutOfRangePtr;
    unsigned char *pulseOutOfRangePtr;
    unsigned char *rrOutOfRangePtr;
    unsigned char *lowBatteryPtr;
    // Orange Ptr
    Bool *bpHighPtr;
    Bool *tempHighPtr;
    Bool *pulseLowPtr;
    Bool *rrLowPtr;
    Bool *rrHighPtr;
    // Acknowledge
    unsigned short *alarmAcknowledgePtr;
    // Time
    unsigned long *localTime;
} displaySubsystemData;

void DisplaySubsystemFunction(void *data);


// #endif