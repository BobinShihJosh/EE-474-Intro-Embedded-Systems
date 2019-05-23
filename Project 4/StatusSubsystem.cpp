#include "StatusSubsystem.h"
#include <Arduino.h>
#include "bool.h"

void StatusSubsystemFunction(void *data)
{
    statusSubsystemData* statusData = (statusSubsystemData*) data; 
    unsigned int temp;
    temp = *(statusData->batteryStatePtr)-1;
    *(statusData->batteryStatePtr) = temp;
    //unsigned int, so no need to worry about value smaller than 0; 
}
