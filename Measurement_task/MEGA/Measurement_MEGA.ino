#include "MeasureSubsystem.h"

unsigned int temperatureRaw;
unsigned int bloodPressRaw;
unsigned int pulseRateRaw;
unsigned int respirationRateRaw;
unsigned short measurementSelection =1;

measureSubsystemData measuredata;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  init_all();
}



void loop()
{
  MeasureSubsystemFunction(&measuredata);
  delay(1000);
}

void init_all()
{
  measuredata.temperatureRawPtr=&temperatureRaw;
  measuredata.bloodPressRawPtr=&bloodPressRaw;
  measuredata.pulseRateRawPtr=&pulseRateRaw;
  measuredata.respirationRateRawPtr=&respirationRateRaw;
  measuredata.measurementSelectionPtr=&measurementSelection;

}
