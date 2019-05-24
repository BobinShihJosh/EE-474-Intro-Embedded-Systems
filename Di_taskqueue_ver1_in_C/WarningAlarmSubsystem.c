#include "WarningAlarmSubsystem.h"
// #include <Arduino.h>
#include "bool.h"
#include <stdio.h>

void WarningAlarmSubsystemFunction(void* data){

    warningAlarmSubsystemData* warningAlarmData = (warningAlarmSubsystemData*) data;
    if (*(warningAlarmData->measurementSelectionPtr) == 0) {
        if (*(warningAlarmData->temperatureRawPtr) < 36 || *(warningAlarmData->temperatureRawPtr) > 37) {
            *(warningAlarmData->tempHighPtr) = TRUE;
        }
    }
    printf("Run warning alarm successfully.\n");
}
