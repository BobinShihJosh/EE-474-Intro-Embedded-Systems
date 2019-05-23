#include "WarningAlarmSubsystem.h"
#include <Arduino.h>
#include "bool.h"

WarningAlarmSubsystemFunction(void* data){

    WarningAlarmSubsystemData* warningAlarmData = (WarningAlarmSubsystemData*) data;
    if (*(WarningAlarmSubsystemData->measurementSelection) == 0) {
        if (*(warningAlarmData->temperatureRawPtr) < 36 || *(warningAlarmData->temperatureRawPtr) > 37)) {
            *(warningAlarmData->tempHigh) = 1;
        }
    }

}
