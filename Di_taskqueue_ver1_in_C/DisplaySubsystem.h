#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "bool.h"

typedef struct DisplaySubsystemData{
    unsigned int *tempCorrectedPtr;
    unsigned short *measurementSelectionPtr;
    unsigned int *tempOutOfRangePtr;
    unsigned short *batteryStatePtr;
    Bool *tempHighPtr;

    // unsigned short *measurementSelection;
} displaySubsystemData;

void DisplaySubsystemFunction(void *data);

#endif // MEASURE_H_INCLUDED
