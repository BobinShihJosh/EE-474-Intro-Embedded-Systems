#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include <stddef.h>
#include "bool.h"
#include "TFTkeypadSubsystem.h"
#include "MeasureSubsystem.h"
#include "ComputeSubsystem.h"
#include "DisplaySubsystem.h"
#include "WarningAlarmSubsystem.h"
#include "StatusSubsystem.h"
//#include "SchedulerSubsystem.h"

//#define MEASURE_BUFF_SIZE 8
//#define PRESSURE_BUFF_SIZE 16
//#define PULSERATE_BUFF_SIZE 8

//Measurement
unsigned int temperatureRaw;
//unsigned int temperatureRawBuf[8];
//unsigned int bloodPressRawBuf[16];
//unsigned int pulseRateRawBuf[8];
//Compute
unsigned int tempCorrected;
//unsigned char temperatureCorrectedBuf[8];
//unsigned char bloodPressCorrectedBuf[16];
//unsigned char pulseRateCorrectedBuf[8];

//TFT Key
unsigned short functionSelect;
unsigned short measurementSelection;
unsigned short alarmAcknowledge;

//Status
unsigned short batteryState;
//Alarms
//unsigned char bpOutOfRange;
unsigned int tempOutOfRange;
//unsigned char pulseOutOfRange;
//Warning
Bool bpHigh;
Bool tempHigh;
Bool pulseLow;

//static allocation to struct
measureSubsystemData measureData;
computeSubsystemData computeData;
displaySubsystemData displayData;
warningAlarmSubsystemData warningAlarmData;
statusSubsystemData statusData;
tftkeypadSubsystemData tftData;

//SchedulerSubsystemData scheduleData;

void init();

#endif // GLOBALS_H_INCLUDED
