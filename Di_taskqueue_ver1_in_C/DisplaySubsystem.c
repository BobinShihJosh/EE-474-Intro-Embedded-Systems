#include "DisplaySubsystem.h"
// #include <Arduino.h>
#include "bool.h"
#include <stdio.h>

void DisplaySubsystemFunction(void* data) {
    displaySubsystemData* displayData = (displaySubsystemData*) data;
    if(*(displayData->measurementSelectionPtr) == 0) {
        //Serial.println(F("TEMPERATURE : "));
        printf("TEMPERATURE : /n");
        if ((*displayData->tempOutOfRangePtr) == 1){
            //Serial.println(F("there is alarm right now(flashing)..."));
            //Serial.println(*(displayData->temperatureCorrectedPtr));
        printf("there is alarm right now(flashing)... %d \n",*(displayData->tempCorrectedPtr));
        } else if(*(displayData->tempHighPtr) == TRUE) {
          //  Serial.println(F("there is warning right now..."));
           // Serial.println(*(displayData->temperatureCorrectedPtr));
        printf("there is warning right now... %d \n",*(displayData->tempCorrectedPtr));
        } else  {
           // Serial.println(F("there is warning or alarm right now..."));
           // Serial.println(*(displayData->temperatureCorrectedPtr));
        printf("there is warning or alarm right now...  \n %d \n",*(displayData->tempCorrectedPtr));
        }

    }
    //printf("running display successfully.\n");
}
