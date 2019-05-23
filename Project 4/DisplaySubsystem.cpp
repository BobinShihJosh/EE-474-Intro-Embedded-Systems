#include "DisplaySubsystem.h"
// #include <Arduino.h>
#include "bool.h"

void DisplaySubsystem(void* data) {
    DisplaySubsystemData* displayData = (DisplaySubsystemData*) data;
    if(*(displayData->measurementSelection) == 0) {
        Serial.println(F("TEMPERATURE : "));
        if ((*displayData->tempOutOfRange) == 1){
            Serial.println(F("there is alarm right now(flashing)..."));
            Serial.println(*(displayData->temperatureCorrectedPtr));
        } else if(*(displayData->tempHigh) == TRUE) {
            Serial.println(F("there is warning right now..."));
            Serial.println(*(displayData->temperatureCorrectedPtr));
        } else  {
            Serial.println(F("there is warning or alarm right now..."));
            Serial.println(*(displayData->temperatureCorrectedPtr));
        }
        
    }
}