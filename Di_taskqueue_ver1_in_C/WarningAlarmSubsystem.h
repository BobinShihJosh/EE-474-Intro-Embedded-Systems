#ifndef WARNINGALARMSUBSYSTEM_H_INCLUDED
#define WARNINGALARMSUBSYSTEM_H_INCLUDED

#include "bool.h"

typedef struct WarningAlarmSubsystemData{
    unsigned int *temperatureRawPtr;
    unsigned short *measurementSelectionPtr;
    unsigned int *tempOutOfRangePtr;
    unsigned short *batteryStatePtr;
    Bool *tempHighPtr;

    // unsigned short *measurementSelection;
} warningAlarmSubsystemData;

void WarningAlarmSubsystemFunction(void *data);

#endif // MEASURE_H_INCLUDED
