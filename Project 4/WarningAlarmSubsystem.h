#ifndef WARNINGALARM_H_INCLUDED
#define WARNINGALARM_H_INCLUDED

#include "bool.h"

typedef struct WarningAlarmSubsystemData{
    unsigned int *temperatureRawPtr;
    unsigned short *measurementSelection;
    unsigned int *tempOutOfRange;
    unsigned bool *tempHigh;

    // unsigned short *measurementSelection;
} WarningAlarmSubsystemData;

void WarningAlarmSubsystemFunction(void *data);

#endif // MEASURE_H_INCLUDED