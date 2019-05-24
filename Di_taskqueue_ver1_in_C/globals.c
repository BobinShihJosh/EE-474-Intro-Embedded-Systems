#include "globals.h"
#include <stdio.h>
//#include <circularBuffer.h>

void initTFTData()
{
tftData.functionSelectPtr = &functionSelect;
tftData.measurementSelectionPtr = &measurementSelection;
tftData.alarmAcknowledgePtr = &alarmAcknowledge;
}

void initMeasureData()
{
measureData.temperatureRawPtr = &temperatureRaw;
//measureData.bloodPressRawPtr = bloodPressRawBuf;
//measureData.pulseRateRawPtr = pulseRateRawBuf;
measureData.measurementSelectionPtr = &measurementSelection;
}

//
void initComputeData()
{
//initialize array to pointer
computeData.temperatureRawPtr = &temperatureRaw;
//computeData.bloodPressRawPtr = bloodPressRawBuf;
//computeData.pulseRateRawPtr = pulseRateRawBuf;

computeData.tempCorrectedPtr = &tempCorrected;
//computeData.bloodPressCorrectedPtr = bloodPressCorrectedBuf;
//computeData.pulseRateCorrectedPtr = pulseRateCorrectedBuf;

computeData.measurementSelectionPtr = &measurementSelection;
//initialize circular buffer

}

void initDisplayData()
{
displayData.tempCorrectedPtr = &tempCorrected;
displayData.measurementSelectionPtr = &measurementSelection;
displayData.tempOutOfRangePtr = &tempOutOfRange;
displayData.tempHighPtr = &tempHigh;
//displayData.sysCorrectedPtr = systolicPressCorrected;
//displayData.diasCorrectedPtr = diastolicPressCorrected ;
//displayData.prCorrectedPtr = pulseRateCorrected;
displayData.batteryStatePtr = &batteryState;
}

void initWarningAlarmData()
{
warningAlarmData.temperatureRawPtr = &temperatureRaw;
warningAlarmData.measurementSelectionPtr = &measurementSelection;
warningAlarmData.tempHighPtr = &tempHigh;
//warningAlarmData.systolicPressRawPtr = &systolicPressRaw;
//warningAlarmData.diastolicPressRawPtr = &diastolicPressRaw;
//warningAlarmData.pulseRateRawPtr = &pulseRateRaw;
warningAlarmData.batteryStatePtr = &batteryState;
}

void initStatusData()
{
statusData.batteryStatePtr = &batteryState;
}

void init()
{
//Measurements
temperatureRaw = 75;
//systolicPressRaw = 80;
//diastolicPressRaw = 80;
//pulseRateRaw = 50;

//TFT Keypad
functionSelect=0; //Select Measurement task
measurementSelection=0; //Select temperature measurement
alarmAcknowledge=1;
//Status
batteryState = 200;
//Alarms
//bpOutOfRange = 0;
tempOutOfRange = 0;
//pulseOutOfRange = 0;
//Warning
//bpHigh = FALSE;
tempHigh = FALSE;
//pulseLow = FALSE;

//initialized the datastruts
initTFTData();
initMeasureData();
initComputeData();
initDisplayData();
initWarningAlarmData();
initStatusData();

//printf("initiate values successfully\n");

}
