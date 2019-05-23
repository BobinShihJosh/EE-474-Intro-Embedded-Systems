#include "ComputeSubsystem.h"
#include <Arduino.h>
#include "bool.h"
// #include "circularBuffer.h"


void ComputeSubsystemFunction(void *data)
{
    unsigned int temperatureRaw_t;
    // unsigned int systolicPressCorrected_t;
    // unsigned int diastolicPressCorrected_t;
    // unsigned int pulseRateCorrected_t;
    // unsigned int index_temperature;
    // unsigned int index_systolicPressure;
    // unsigned int index_diastolicPressure;
    // unsigned int index_pulseRate;
    unsigned short measurementSelection_t;
    
    computeSubsystemData* computeData = (computeSubsystemData*) data;
    measurementSelection_t = *(computeData->measurementSelection);

    if (measurementSelection_t == 0) {
        temperatureRaw_t = *(computeData->temperatureRawPtr);
        *(computeData->tempCorrectedPtr) = 5 + 0.75*temperatureRaw_t;;  
    }
    
}
