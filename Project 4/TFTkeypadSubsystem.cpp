#include "TFTkeypadSubsystem.h"
#include <Arduino.h>
#include "bool.h"
#include "circularBuffer.h"
#include <Arduino.h>

void TFTkeypadSubsystemFunction(void *data)
{
    //FunctionSelect = 0: Take Measurement task; FunctionSelect = 1: Take Display/Acknowledgement task
    //MeasurementSelectionPtr =0: Take temperature measurement;
    //MeasurementSelectionPtr =1: Take bloodpressure measurement;
    //MeasurementSelectionPtr =2: Take pulserate measurement;
    //MeasurementSelectionPtr =3: Take respiration measurement;
    tftkeypadSubsystemData *tftkeypadData = tftkeypadSubsystemData *data;
    if (*(tftkeypadData->FunctionSelectPtr)==0 )
        switch (*(tftkeypadData->MeasurementSelectionPtr))
    {
        case 1:
            Serial.println("Start to measure blood pressure.\n");
        break;
        case 2:
            Serial.println("Start to measure pulse rate.\n");
        break;
        case 3:
            Serial.println("Start to measure respiration.\n ");
        default:
            Serial.println("Start to measure temperature.\n");

    }
}
