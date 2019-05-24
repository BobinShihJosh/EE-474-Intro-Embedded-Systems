#ifndef MEASURESUBSYSTEM_H_INCLUDED
#define MEASURESUBSYSTEM_H_INCLUDED

#include "bool.h"

typedef struct MeasureSubsystemData{
    unsigned int *temperatureRawPtr;
    // unsigned int *bloodPressRawPtr;
    // unsigned int *systolicPressRawPtr;
    // unsigned int *diastolicPressRawPtr;
    // unsigned int *pulseRateRawPtr;
    unsigned short *measurementSelectionPtr;
} measureSubsystemData;

void MeasureSubsystemFunction(void *data);

#endif // MEASURE_H_INCLUDED
