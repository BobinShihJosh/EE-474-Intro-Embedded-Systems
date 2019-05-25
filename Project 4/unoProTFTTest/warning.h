#ifndef WARNING_H_INCLUDE
#define WARNING_H_INCLUDE

#include "bool.h"

unsigned int bpOutOfRange;
unsigned int tempOutOfRange;
unsigned int pulseOutOfRange;
unsigned int rrOutOfRange;
Bool bpHigh;
Bool tempHigh;
Bool pulseLow;
Bool rrLow;
Bool rrHigh;
Bool lowBattery;

typedef struct WarningAlarmSubsystemData{
    unsigned short *functionSelectPtr;
    // Data Pointers
    unsigned int *temperatureRawPtr;
    unsigned int *systolicPressRawPtr;
    unsigned int *diastolicPressRawPtr;
    unsigned int *pulseRateRawPtr;
    unsigned int *respirationRateRawPtr;
    unsigned short *batteryStatePtr;
    // FOR ALARMS - RED
    unsigned char *bpOutOfRangePtr;
    unsigned char *tempOutOfRangePtr;
    unsigned char *pulseOutOfRangePtr;
    unsigned char *rrOutOfRangePtr;
    unsigned char *lowBatteryPtr;
    // FOR WARNING - ORANGE
    Bool *bpHighPtr;
    Bool *tempHighPtr;
    Bool *pulseLowPtr;
    Bool *rrLowPtr;
    Bool *rrHighPtr;
    unsigned long *localTime;
    unsigned short *alarmAcknowledgePtr;
} warningAlarmSubsystemData;

void WarningAlarmSubsystemFunction(void* data);

#endif