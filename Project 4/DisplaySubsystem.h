#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "bool.h"

typedef struct DisplaySubsystemData{
    unsigned int *temperatureCorrectedPtr;
    unsigned short *measurementSelection;
    unsigned int *tempOutOfRange;
    unsigned bool *tempHigh;

    // unsigned short *measurementSelection;
} DisplaySubsystemData;

void DisplaySubsystemFunction(void *data);

#endif // MEASURE_H_INCLUDED