#include "WarningAlarmSubsystem.h"
// #include <Arduino.h>
#include "bool.h"

void WarningAlarmSubsystemFunction(void* data){

    WarningAlarmSubsystemData* warningAlarmData = (WarningAlarmSubsystemData*) data;
    if (*(warningAlarmData->measurementSelection) == 0) {
        if (*(warningAlarmData->temperatureRawPtr) < 36 || *(warningAlarmData->temperatureRawPtr) > 37) {
            *(warningAlarmData->tempHigh) = TRUE;
        }
    }

}
