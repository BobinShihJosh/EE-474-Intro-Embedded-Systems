#include "MeasureSubsystem.h"
#include <Arduino.h>
//#include <circularBuffer.h>
boolean newData = false;
boolean runUNO = false;
const byte numChars = 32;
char receivedChars[numChars]; //array to store the value
byte numChars_rev = 0;
int temperatureRaw_uno;
int systolicPress_uno;
int diastolicPress_uno;
int pulseRateRaw_uno;
int respirationRateRaw_uno;
int measurementSelection_t;

void MeasureSubsystemFunction(void* data) {
    measureSubsystemData* measureData = (measureSubsystemData*) data;
    measurementSelection_t = *(measureData->measurementSelectionPtr); //record the measurementSelection flag
   
   //store Temperature Measurement Results in the circular buffer if the current measurement is more than 15% different higher or lower than the previous measurement
  if(measurementSelection_t==0)
  {
    Serial1.print(measurementSelection_t);  
    delay(100);
    recvWithEndMarker();
    showNewData();
  }
  
   //store blood pressure
  if(measurementSelection_t==1)
  {Serial1.print(measurementSelection_t);  
    delay(100);
    recvWithEndMarker();
    showNewData();
    }

   //store Pulserate Measurement Results in the circular buffer if the current measurement is more than 15% different higher or lower than the previous measurement
   //limit 200 beats/min ~10 beats/min  (use 10~200Hz signal to mimic)
   if(measurementSelection_t==2)
   {Serial1.print(measurementSelection_t);  
    delay(100);
    recvWithEndMarker();
    showNewData();
    }

   //store Respiration Measurement Results in the circular buffer if the current measurement is more than 15% different higher or lower than the previous measurement
   //limit 50 beats/min~10 beats/min (use 10~50Hz signal to mimic)
   if(measurementSelection_t==3)
   {Serial1.print(measurementSelection_t);  
    delay(100);
    recvWithEndMarker();
    showNewData();
    }
}

void recvWithEndMarker(){
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 
while (Serial1.available() > 0 && newData == false) {
 rc = Serial1.read();

 if (rc != endMarker && rc!='\t') {
 receivedChars[ndx] = rc;
 ndx++;
 if (ndx >= numChars) {
 ndx = numChars - 1;
 }
 }
 else {
 receivedChars[ndx] = '\0'; // terminate the string
 numChars_rev = ndx-1;
 ndx = 0;
 newData = true;
 //read out temperature value
 if (numChars_rev==2 && measurementSelection_t==0) //receive new temperature data, in 2 digits
temperatureRaw_uno = (int)(receivedChars[0]-'0')*10 + (int)(receivedChars[1]-'0'); 
//read out pressure value
if (numChars_rev==5 && measurementSelection_t==1) //receive new temperature data, in 2 digits
systolicPress_uno = (int)(receivedChars[0]-'0')*100 + (int)(receivedChars[1]-'0')*10+(int)(receivedChars[2]-'0');
diastolicPress_uno =  (int)(receivedChars[3]-'0')*10+(int)(receivedChars[4]-'0');

 //read out pulse rate
if (numChars_rev==2 && measurementSelection_t==2) //receive new pulse rate data, in 2 digits
pulseRateRaw_uno = (int)(receivedChars[0]-'0')*10 + (int)(receivedChars[1]-'0');
if (numChars_rev==3 && measurementSelection_t==2) //receive new pulse rate, in 3 digits
pulseRateRaw_uno = (int)(receivedChars[0]-'0')*100 + (int)(receivedChars[1]-'0')*10+(int)(receivedChars[2]-'0');

//read out respiration rate
if (numChars_rev==2 && measurementSelection_t==0) //receive new respiration data, in 2 digits
respirationRateRaw_uno = (int)(receivedChars[0]-'0')*10 + (int)(receivedChars[1]-'0');
 }
 }
}

void showNewData() {
 if (newData == true) {
    if (newData == true) {
    if(measurementSelection_t==0)
    {Serial.println(receivedChars);
    Serial.print("The temperature is:"); Serial.println(temperatureRaw_uno);}

     if(measurementSelection_t==1)
    {Serial.println(receivedChars);
    Serial.print("The systolic pressure is:"); Serial.println(systolicPress_uno);
    Serial.print("The diastolic pressure is:"); Serial.println(diastolicPress_uno);
    }

     if(measurementSelection_t==2)
    {Serial.println(receivedChars);
    Serial.print("The pulse rate is:"); Serial.println(pulseRateRaw_uno);}

     if(measurementSelection_t==3)
    {Serial.println(receivedChars);
    Serial.print("The respiration rate is:"); Serial.println(respirationRateRaw_uno);}
    
     newData = false;
    }
 }
}
