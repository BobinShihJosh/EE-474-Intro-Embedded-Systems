#include "warning.h"
#include "bool.h"
// #include <Arduino.h>

void WarningAlarmSubsystemFunction(void* data) {
    warningAlarmSubsystemData* warningAlarmData = (warningAlarmSubsystemData*) data;
    unsigned int temp = *warningAlarmData->temperatureRawPtr;
    unsigned int systolicPress = *warningAlarmData->systolicPressRawPtr;
    unsigned int diastolicPress = *warningAlarmData->diastolicPressRawPtr;
    unsigned int pulseRate = *warningAlarmData->pulseOutOfRangePtr;
    unsigned int respirationRate = *warningAlarmData->respirationRateRawPtr;
    unsigned int battery = *warningAlarmData->batteryStatePtr;
    unsigned short acknowledge = *warningAlarmData->alarmAcknowledgePtr;

    // Temp warning & alarm
    if (temp < 36.1 * 0.95 || temp > 37.8 * 1.05) {
        *warningAlarmData->tempHighPtr = TRUE; // need to be orange and falsh at 1 sec rate
        if ((temp < 36.1 * 0.85 || temp > 37.8 * 1.15) && acknowledge == 0) {
            *warningAlarmData->tempOutOfRangePtr = 1; // need to be red and flash at 1 sec rate    
        }
    } else {
        *warningAlarmData->tempOutOfRangePtr = 0;
        *warningAlarmData->tempHighPtr = FALSE;
    } 
    // BP warning & alarm
    if (systolicPress < 120 * 0.95 || systolicPress > 130 * 1.05 || diastolicPress < 70 * 0.95 || diastolicPress > 80 * 1.05) {
        *warningAlarmData->bpHighPtr = TRUE; // need to be orange and flash at 0.5 sec rate
        if ((systolicPress < 120 * 0.8 || systolicPress > 130 * 1.2) && acknowledge == 0) {
            *warningAlarmData->bpOutOfRangePtr = 1; // need to be red and flash at 0.5 sec rate
        }
    } else {
        *warningAlarmData->bpHighPtr = FALSE;
        *warningAlarmData->bpOutOfRangePtr = 0;
    }
    // PR warning & alarm
    if (pulseRate < 60 * 0.95 || pulseRate > 100 * 1.05) {
        *warningAlarmData->pulseLowPtr = TRUE; // Oragne & flash 2 sec rate
        if ((pulseRate < 60 * 0.85 || pulseRate > 100 * 1.15) && acknowledge == 0) {
            *warningAlarmData->pulseOutOfRangePtr = 1; // Red & flash 2 sec rate
        }
    } else {
        *warningAlarmData->pulseLowPtr = FALSE;
        *warningAlarmData->pulseOutOfRangePtr = 0;
    }
    // RR warning & alarm
    if (respirationRate < 12 * 0.95) {
        *warningAlarmData->rrLowPtr = TRUE; // Orange but no flash
        if ((respirationRate < 12 * 0.85) && acknowledge == 0) {
            *warningAlarmData->rrOutOfRangePtr = 1; // Red but no flash
        }
    } else if (respirationRate > 25 * 1.05) {
        *warningAlarmData->rrHighPtr = TRUE; // Orange but no flash
        if ((respirationRate > 25 * 1.15) && acknowledge == 0) {
            *warningAlarmData->rrOutOfRangePtr = 1; // Red but no flash
        }
    } else {
        *warningAlarmData->rrLowPtr = FALSE;
        *warningAlarmData->rrHighPtr = FALSE;
        *warningAlarmData->rrOutOfRangePtr = 0;
    }
    // Battery warning & alarm
    if (battery < 40) {
        *warningAlarmData->lowBatteryPtr = 1; // Red but no flash
    }
}