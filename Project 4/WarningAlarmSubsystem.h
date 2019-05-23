#ifndef WARNINGALARMSUBSYSTEM_H_INCLUDED
#define WARNINGALARMSUBSYSTEM_H_INCLUDED

#include "bool.h"

typedef struct WarningAlarmSubsystemData{
    unsigned int *temperatureRawPtr;
    unsigned short *measurementSelection;
    unsigned int *tempOutOfRange;
    Bool *tempHigh;

    // unsigned short *measurementSelection;
} WarningAlarmSubsystemData;

void WarningAlarmSubsystemFunction(void *data);

#endif // MEASURE_H_INCLUDED