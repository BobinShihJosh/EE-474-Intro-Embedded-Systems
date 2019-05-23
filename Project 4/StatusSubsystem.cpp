#include "StatusSubsystem.h"
#include <Arduino.h>
#include "bool.h"

void StatusSubsystemFunction(void *data)
{
    statusSubsystemData* statusData = (statusSubsystemData*) data; 
    unsigned int temp;
    temp = *(statusData->statusPtr)-1;
    *(statusData->statusPtr) = temp;
    //unsigned int, so no need to worry about value smaller than 0; 
}
