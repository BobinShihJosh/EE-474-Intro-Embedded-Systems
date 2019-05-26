#include "MeasureSubsystem.h"
#include <Arduino.h>
//#include <circularBuffer.h>
boolean newData = false;
boolean runUNO = false;
const byte numChars = 32;
char receivedChars[numChars]; //array to store the value
byte numChars_rev = 0;
int temperatureRaw_uno;
int temperatureRaw_uno_store=0; //stored last value
int systolicPress_uno;
int systolicPress_uno_store=0; //stored last value
int diastolicPress_uno;
int diastolicPress_uno_store=0; //stored last value
int pulseRateRaw_uno;
int pulseRateRaw_uno_store=0; //stored last value
int respirationRateRaw_uno;
int respirationRateRaw_uno_store=0; //stored last value
int measurementSelection_t;

//define hardware delay time
unsigned long long startMillis;
unsigned long long currentMillis;
const unsigned long period = 100; //delay 100ms

//define alarm acknowledge and counter
unsigned int counter = 0;
unsigned short alarmAcknowledge =0; //may need to add alarmAcknowledge flag in the MeasurementSubsystemData struct
unsigned short tempOutOfRange =0;

void MeasureSubsystemFunction(void* data) {
    measureSubsystemData* measureData = (measureSubsystemData*) data;
    measurementSelection_t = *(measureData->measurementSelectionPtr); //record the measurementSelection flag
//**************************************************************
    if (tempOutOfRange == 1 && alarmAcknowledge ==0)
     {counter ++;
     if(counter==5)
     {alarmAcknolwedge=1;
     counter = 0;}
     }
//***************************************************************     
   //store Temperature Measurement Results in the circular buffer if the current measurement is more than 15% different higher or lower than the previous measurement
  if(measurementSelection_t==0)
  {
    Serial1.print(measurementSelection_t);  
    //delay(100);
    startMillis=millis(); //get the initial "time" 
    currentMillis=millis(); //get the current "time"
    while (currentMillis-startMillis<period)
    {currentMillis =millis();}
    
    recvWithEndMarker();
    showNewData();
  }
  
   //store blood pressure
  if(measurementSelection_t==1)
  {Serial1.print(measurementSelection_t);  
    //delay(100);
    startMillis=millis(); //get the initial "time" 
    currentMillis=millis(); //get the current "time"
    while (currentMillis-startMillis<period)
    {currentMillis =millis();}
   
    recvWithEndMarker();
    showNewData();
    }

   //store Pulserate Measurement Results in the circular buffer if the current measurement is more than 15% different higher or lower than the previous measurement
   //limit 200 beats/min ~10 beats/min  (use 10~200Hz signal to mimic)
   if(measurementSelection_t==2)
   {Serial1.print(measurementSelection_t);  
    //delay(100);
    startMillis=millis(); //get the initial "time" 
    currentMillis=millis(); //get the current "time"
    while (currentMillis-startMillis<period)
    {currentMillis =millis();}
    
    recvWithEndMarker();
    showNewData();
    }

   //store Respiration Measurement Results in the circular buffer if the current measurement is more than 15% different higher or lower than the previous measurement
   //limit 50 beats/min~10 beats/min (use 10~50Hz signal to mimic)
   if(measurementSelection_t==3)
   {Serial1.print(measurementSelection_t);  
    //delay(100);
    startMillis=millis(); //get the initial "time" 
    currentMillis=millis(); //get the current "time"
    while (currentMillis-startMillis<period)
    {currentMillis =millis();}
    
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
    {
      temperatureRaw_uno = (int)(receivedChars[0]-'0')*10 + (int)(receivedChars[1]-'0'); 
    if (temperatureRaw_uno>=temperatureRaw_uno_store*0.85 &&temperatureRaw_uno<=temperatureRaw_uno_store*1.15)
      temperatureRaw_uno_store=temperatureRaw_uno;
    }

//read out pressure value
if (numChars_rev==5 && measurementSelection_t==1) //receive new temperature data, in 2 digits
{
  systolicPress_uno = (int)(receivedChars[0]-'0')*100 + (int)(receivedChars[1]-'0')*10+(int)(receivedChars[2]-'0');
  diastolicPress_uno =  (int)(receivedChars[3]-'0')*10+(int)(receivedChars[4]-'0');
  if (systolicPress_uno>=systolicPress_uno_store*0.85 &&systolicPress_uno<=systolicPress_uno_store*1.15)
     systolicPress_uno_store=systolicPress_uno;
  if (diastolicPress_uno>=diastolicPress_uno_store*0.85 &&diastolicPress_uno<=diastolicPress_uno_store*1.15)
      diastolicPress_uno_store=diastolicPress_uno;
}

 //read out pulse rate
if (numChars_rev==2 && measurementSelection_t==2) //receive new pulse rate data, in 2 digits
{
  pulseRateRaw_uno = (int)(receivedChars[0]-'0')*10 + (int)(receivedChars[1]-'0');
  if (pulseRateRaw_uno>=pulseRateRaw_uno_store*0.85 &&pulseRateRaw_uno<=pulseRateRaw_uno_store*1.15)
     pulseRateRaw_uno_store=pulseRateRaw_uno;
}
if (numChars_rev==3 && measurementSelection_t==2) //receive new pulse rate, in 3 digits
{
  pulseRateRaw_uno = (int)(receivedChars[0]-'0')*100 + (int)(receivedChars[1]-'0')*10+(int)(receivedChars[2]-'0');
    if (pulseRateRaw_uno>=pulseRateRaw_uno_store*0.85 &&pulseRateRaw_uno<=pulseRateRaw_uno_store*1.15)
     pulseRateRaw_uno_store=pulseRateRaw_uno;
}
//read out respiration rate
if (numChars_rev==2 && measurementSelection_t==0) //receive new respiration data, in 2 digits
{
  respirationRateRaw_uno = (int)(receivedChars[0]-'0')*10 + (int)(receivedChars[1]-'0');
  if (respirationRateRaw_uno>=respirationRateRaw_uno_store*0.85 &&respirationRateRaw_uno<=respirationRateRaw_uno_store*1.15)
    respirationRateRaw_uno_store=respirationRateRaw_uno;
}


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
