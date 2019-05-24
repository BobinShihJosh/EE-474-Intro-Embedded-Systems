#include "TFTkeypadSubsystem.h"
//#include <Arduino.h>
#include "bool.h"
//#include "circularBuffer.h"
#include <stdio.h>

void TFTkeypadSubsystemFunction(void *data)
{
    //FunctionSelect = 0: Take Measurement task; FunctionSelect = 1: Take Display/Acknowledgement task
    //MeasurementSelectionPtr =0: Take temperature measurement;
    //MeasurementSelectionPtr =1: Take bloodpressure measurement;
    //MeasurementSelectionPtr =2: Take pulserate measurement;
    //MeasurementSelectionPtr =3: Take respiration measurement;
    tftkeypadSubsystemData *tftkeypadData = (tftkeypadSubsystemData*) data;
    if (*(tftkeypadData->functionSelectPtr)==0 )
        switch (*(tftkeypadData->measurementSelectionPtr))
    {
        case 1:
            printf("Start to measure blood pressure.\n");
        break;
        case 2:
            printf("Start to measure pulse rate.\n");
        break;
        case 3:
            printf("Start to measure respiration.\n ");
        default:
            printf("TFT_Start to measure temperature.\n");

    }
}
