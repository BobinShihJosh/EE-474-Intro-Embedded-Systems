#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "bool.h"

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


#endif