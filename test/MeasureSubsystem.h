#ifndef MEASURE_H_INCLUDED
#define MEASURE_H_INCLUDED

typedef struct MeasureSubsystemData{
    unsigned int *temperatureRawPtr;
    unsigned int *bloodPressRawPtr;
    unsigned int *pulseRateRawPtr;
    unsigned int *respirationRateRawPtr;
    unsigned short *measurementSelectionPtr;

} measureSubsystemData;

void MeasureSubsystemFunction(void *data);
void showNewData();
void recvWithEndMarker();

#endif // MEASURE_H_INCLUDED
