#include "display.h"

void DisplaySubsystemFunction(void* data) {
    // unsigned long t1 = millis();
    displaySubsystemData* displayData = (displaySubsystemData*) data;
    tft.setTextColor(GREEN); tft.setTextSize(1);tft.setCursor(0, 0);


    // temperature 
    tft.println("Temperature");
    tft.print("<");
    tft.fillRect(5, 7, 35, 10, BLACK);
    if (*(displayData->tempHighPtr)) {
        tft.setTextColor(ORANGE);
        if (*(unsigned int*)(displayData->tempOutOfRangePtr) == 1 && *(displayData->alarmAcknowledgePtr) == 0) {
          tft.setTextColor(RED); //tft.setTextSize(2);
        }
    }
    
    tft.print(*(unsigned char*)(displayData->tempCorrectedPtr));
    tft.setTextColor(GREEN); //tft.setTextSize(2);
    tft.println("> C");
    tft.println(" ");

    //systolic pressure
    tft.println("Systolic Pressure");
    tft.print("<");
    tft.fillRect(5, 32, 70, 10, BLACK);
    if (*(displayData->bpHighPtr)) {
        tft.setTextColor(ORANGE);
        if (*(unsigned int*)(displayData->bpOutOfRangePtr) == 1 && *(displayData->alarmAcknowledgePtr) == 0) {
            tft.setTextColor(RED); //tft.setTextSize(2);
        }
    }
    
    tft.print(*(unsigned char*)(displayData->sysCorrectedPtr));
    tft.setTextColor(GREEN); //tft.setTextSize(2);
    tft.println("> mm Hg");
    tft.println(" ");

    //diastolic pressure
    tft.println("Diastolic Pressure");
    tft.print("<");
    tft.fillRect(5, 55, 70, 10, BLACK);
    if (*(displayData->bpHighPtr)) {
        tft.setTextColor(ORANGE);
        if (*(unsigned int*)(displayData->bpOutOfRangePtr) == 1 && *(displayData->alarmAcknowledgePtr) == 0) {
            tft.setTextColor(RED); //tft.setTextSize(2);
        }
    }
    tft.print(*(unsigned char*)(displayData->diasCorrectedPtr));
    tft.setTextColor(GREEN); //tft.setTextSize(2);
    tft.println("> mm Hg");
    tft.println(" ");
    
    //pulse rate
    tft.println("Pulse Rate");
    tft.print("<");
    tft.fillRect(5, 79, 60, 10, BLACK);
    if (*(displayData->pulseLowPtr)) {
        tft.setTextColor(ORANGE);
        if (*(unsigned int*)(displayData->pulseOutOfRangePtr) == 1 && *(displayData->alarmAcknowledgePtr) == 0) {
            tft.setTextColor(RED); //tft.setTextSize(2);
        }
    }
    tft.print(*(unsigned char*)(displayData->prCorrectedPtr));
    tft.setTextColor(GREEN); //tft.setTextSize(2);
    tft.println("> BPM");
    tft.println(" ");
    
    //respiration rate
    tft.println("Respiration Rate");
    tft.print("<");
    tft.fillRect(5, 104, 70, 10, BLACK);
    if (*(displayData->rrLowPtr) || *(displayData->rrHighPtr)) {
        tft.setTextColor(ORANGE);
        if (*(unsigned int*)(displayData->rrOutOfRangePtr) == 1 && *(displayData->alarmAcknowledgePtr) == 0) {
            tft.setTextColor(RED); //tft.setTextSize(2);
        }
    }
    tft.print(*(unsigned char*)(displayData->rrCorrectedPtr));
    tft.setTextColor(GREEN); //tft.setTextSize(2);
    tft.println("> BPM");
    tft.println(" ");
    
    //battery state
    tft.println("Battery");
    tft.print("<");
    tft.fillRect(5, 130, 50, 10, BLACK);
    if (*(unsigned int*)(displayData->batteryStatePtr) < 40) {
      tft.setTextColor(RED); //tft.setTextSize(2);
    }
    tft.print(*(unsigned char*)(displayData->batteryStatePtr));
    tft.setTextColor(GREEN); //tft.setTextSize(2);
    tft.println(">");
    unsigned long t2 = millis();
    unsigned long taskTime = t2-t1;
//    tft.print("Display time: ");
//    tft.println(taskTime);
  }