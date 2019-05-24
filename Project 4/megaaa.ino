// IMPORTANT: ELEGOO_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Elegoo_TFTLCD.h FOR SETUP.
//Technical support:goodtft@163.com

#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Elegoo_TFTLCD tft;

void setup(void) {
  Serial.begin(9600);
  Serial1.begin(9600);
  //Serial.println(F("TFT LCD test"));


#ifdef USE_Elegoo_SHIELD_PINOUT
  //Serial.println(F("Using Elegoo 2.4\" TFT Arduino Shield Pinout"));
#else
  //Serial.println(F("Using Elegoo 2.4\" TFT Breakout Board Pinout"));
#endif

  //Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

   uint16_t identifier = tft.readID();
   
   if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
      // Serial.println(F("Found 0x9341 LCD driver"));
  }
  else if(identifier==0x1111)
  {     
      identifier=0x9328;
       Serial.println(F("Found 0x9328 LCD driver"));
  }
  else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9328;
  
  }
  tft.begin(identifier);
  tft.setRotation(0);//set the display diretion(0-3)
  tft.fillScreen(BLACK);

}

  
  // declaring tasks;
  void TFTkeypadSubsystemFunction(void *data);
  void MeasureSubsystemFunction(void* data);
  void ComputeSubsystemFunction(void* data);
  void DisplaySubsystemFunction(void* data);
  void WarningAlarmSubsystemFunction(void* data);
  void StatusSubsystemFunction(void* data); 

  // making TCB 
  typedef struct
  {
    void* taskDataPtr; //a pointer to void (void* pointer) used to reference the data for the task.
    void (*taskPtr)(void*);//a pointer to a function taking a void* argument and returning a void.
//    struct Node* next; //pointer that stores the address of the right node
//    struct Node* prev;  //pointer that stores the address of the left node
  } TCB;


 // this is code for the UNO. The UNO will take the measure subsystem task. It will simulate the
 // data given initial variables and communicate with the uno when called.
 //===================================MeasureSubsystem DATA==============================================
  //declaring initial variables
  unsigned int temperatureRaw_uno;
  unsigned int systolicPress_uno;
  unsigned int diastolicPress_uno;
  unsigned int pulseRateRaw_uno;
  unsigned short measurementSelection = 0;
   
  typedef struct MeasureSubsystemData{
    unsigned int *temperatureRawPtr;
    unsigned int *systolicPressRawPtr;
    unsigned int *diastolicPressRawPtr;
    unsigned int *pulseRateRawPtr;
    unsigned long *localTime;
    unsigned short *measurementSelectionPtr;

  } measureSubsystemData;

 //===================================ComputeSubsystem DATA========================================== 

  unsigned char tempCorrected = 75;
  unsigned char systolicPressCorrected = 80;
  unsigned char diastolicPressCorrected = 80;
  unsigned char pulseRateCorrected = 50;  
  
  typedef struct ComputeSubsystemData{
    unsigned int *temperatureRawPtr;
    unsigned int *systolicPressRawPtr;
    unsigned int *diastolicPressRawPtr;
    unsigned int *pulseRateRawPtr;
    unsigned char *tempCorrectedPtr;
    unsigned char *sysPressCorrectedPtr;
    unsigned char *diasCorrectedPtr;
    unsigned char *prCorrectedPtr;
    unsigned long *localTime;
  }computeSubsystemData;
  
  //================================Warning/Alarm Subsystem DATA==============================================

  unsigned int bpOutOfRange = 0;
  unsigned int tempOutOfRange = 0;
  unsigned int pulseOutOfRange = 0;
  
  typedef struct WarningAlarmSubsystemData{
    unsigned int *temperatureRawPtr;
    unsigned int *systolicPressRawPtr;
    unsigned int *diastolicPressRawPtr;
    unsigned int *pulseRateRawPtr;
    unsigned short *batteryStatePtr;
    unsigned int *bpOutOfRangePtr;
    unsigned int *tempOutOfRangePtr;
    unsigned int *pulseOutOfRangePtr;
    unsigned long *localTime;
  }warningAlarmSubsystemData; 

  
 //===================================DisplaySubsystem DATA==============================================
  //declaring initial variables

  //Status
  unsigned short batteryState = 200;
  
  typedef struct DisplaySubsystemData{
    unsigned char* tempCorrectedPtr;
    unsigned char* sysCorrectedPtr;
    unsigned char* diasCorrectedPtr;
    unsigned char* prCorrectedPtr;
    unsigned short* batteryStatePtr;
    unsigned int *bpOutOfRangePtr;
    unsigned int *tempOutOfRangePtr;
    unsigned int *pulseOutOfRangePtr;
    unsigned long *localTime;
  } displaySubsystemData;


  //================================Status Subsystem DATA==============================================
  typedef struct StatusSubsystemData{
    unsigned short* batteryStatePtr;
    unsigned long *localTime;
  }statusSubsystemData;

  //================================TFT Subsystem DATA==============================================
  unsigned short functionSelect = 0;
  unsigned short alarmAcknowledge = 0;
  
  typedef struct TFTkeypadSubsystemData{
    unsigned short *functionSelectPtr;
    unsigned short *measurementSelectionPtr;
    unsigned short *alarmAcknowledgePtr;
  }tftkeypadSubsystemData;

  //================================TFT TASK FUNCTION==============================================

  void TFTkeypadSubsystemFunction(void *data)
{
    //FunctionSelect = 0: Take Measurement task; FunctionSelect = 1: Take Display/Acknowledgement task
    //MeasurementSelectionPtr =0: Take temperature measurement;
    //MeasurementSelectionPtr =1: Take bloodpressure measurement;
    //MeasurementSelectionPtr =2: Take pulserate measurement;
    //MeasurementSelectionPtr =3: Take respiration measurement;
    tftkeypadSubsystemData *tftkeypadData = (tftkeypadSubsystemData*) data;
    if (*(tftkeypadData->functionSelectPtr)==0 ) {
      (*(tftkeypadData->measurementSelectionPtr)) = 1;
      if (*(tftkeypadData->measurementSelectionPtr) == 1) {
        Serial.print(F("Measure selection ptr = "));
        Serial.println(*(tftkeypadData->measurementSelectionPtr));        
      }
    }
}

  
  //================================MEASURESUBSYSTEM FUNCTION=============================================
  void MeasureSubsystemFunction(void *data);
  const byte numChars = 10;
  char receivedChars[numChars] = {0,0,0,0,0,0,0,0,0,0}; //array to store the value
  byte numChars_rev = 0;
  boolean newData = false;
  boolean runUNO = false;
  void showNewData();
  
  void MeasureSubsystemFunction(void *data) {
    unsigned long t1 = millis();
    
    measureSubsystemData* measureData = (measureSubsystemData*) data;
    
    if (*(measureData->measurementSelectionPtr) == 1) {
      Serial1.print('A');
      Serial.println(F("flag sent"));
    } else if (*(measureData->measurementSelectionPtr) == 2) {
      Serial1.print('B');
    }
    //delay(100);
    recvWithEndMarker();
    showNewData();
    
    *(measureData->temperatureRawPtr) = temperatureRaw_uno;
    *(measureData->systolicPressRawPtr) = systolicPress_uno;
    *(measureData->diastolicPressRawPtr) = diastolicPress_uno;
    *(measureData->pulseRateRawPtr) = pulseRateRaw_uno;
    *(measureData->localTime) += 1000; 
    unsigned long t2 = millis();
    unsigned long taskTime = t2-t1;
//    tft.print("Measure Time: ");
//    tft.println(taskTime);
  }


   //Uno Communication Tasks 
      void recvWithEndMarker() {
         static byte ndx = 0;
         char endMarker = '\n';
         char rc;
         
         // if (Serial.available() > 0) {
         while (Serial1.available() > 0 && newData == false) {
         rc = Serial1.read();
        
         if (rc != endMarker) {
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
         }
         }
        }
        // testing method on serial
        
        void showNewData() {
          if (newData == true) {
          // receivedChar_high = int(Serial1.read()-'0');
           ////receivedChar_low = int (Serial1.read()-'0');
           //Serial.print(receivedChar_high*10+receivedChar_low);
          if (newData == true) {
          //Serial.print("This just in ... ");
         // Serial.print("Number of ndx is...");Serial.println (numChars_rev);
          //Serial.println(receivedChars);
          temperatureRaw_uno = (int)(receivedChars[0]-'0')*10 + (int)(receivedChars[1]-'0'); 
          systolicPress_uno = (int)(receivedChars[2]-'0')*10 + (int)(receivedChars[3]-'0');
          diastolicPress_uno = (int)(receivedChars[4]-'0')*10 + (int)(receivedChars[5]-'0');
          pulseRateRaw_uno = (int)(receivedChars[6]-'0')*10 + (int)(receivedChars[7]-'0');
          //testing to serial
          
          Serial.println(receivedChars);
          Serial.print("The temperature is:"); Serial.println(temperatureRaw_uno);
          Serial.print("The systolic pressure is:"); Serial.println(systolicPress_uno);
          Serial.print("The diastolic pressure is:"); Serial.println(diastolicPress_uno);
          Serial.print("The pulse rate is:"); Serial.println(pulseRateRaw_uno);
          Serial.println();
          
           newData = false;
        }
        
 }
    //testing 
    /*
    even = !even;
    tft.setTextColor(GREEN); tft.setTextSize(2);
    tft.println("temperatureRaw:");
    tft.println(*(unsigned int*)(measureData->temperatureRawPtr));
    tft.println("");
    tft.println("systolicPressRaw");
    tft.println(*(unsigned int*)(measureData->systolicPressRawPtr));
    tft.println("");
    tft.println("diastolicPressRaw");
    tft.println(*(unsigned int*)(measureData->diastolicPressRawPtr));
    tft.println("");
    tft.println("pulseRateRaw");
    tft.println(*(unsigned int*)(measureData->pulseRateRawPtr));
    */
}

  //=====================================Compute Task=============================================

  void ComputeSubsystemFunction(void *data)
  {
    unsigned long t1 = millis();
    computeSubsystemData* computeData = (computeSubsystemData*) data;

    *(double*)(computeData->tempCorrectedPtr) = (double)(5+0.75*(*computeData->temperatureRawPtr));
    *(unsigned char*)(computeData->sysPressCorrectedPtr) = (char)(9+2*(*computeData->systolicPressRawPtr));
    *(unsigned char*)(computeData->diasCorrectedPtr) = (char)(6+1.5*(*computeData->diastolicPressRawPtr));
    *(unsigned char*)(computeData->prCorrectedPtr) = (char)(8+3*(*computeData->pulseRateRawPtr));

    //testing
    /*
    tft.setTextColor(GREEN); tft.setTextSize(2);
    tft.println("Temperature");
    tft.print("<");
    tft.print(*(unsigned char*)(computeData->tempCorrectedPtr));
    tft.println(">");
    tft.println("Systolic Pressure");
    tft.print("<");
    tft.print(*(unsigned char*)(computeData->sysPressCorrectedPtr));
    tft.println(">");
    tft.println("Diastolic Pressure");
    tft.print("<");
    tft.print(*(unsigned char*)(computeData->diasCorrectedPtr));
    tft.println(">");
    tft.println("Pulse Rate");
    tft.print("<");
    tft.print(*(unsigned char*)(computeData->prCorrectedPtr));
    tft.println(">");
    */
    unsigned long t2 = millis();
    unsigned long taskTime = t2-t1;
//    tft.print("Compute Time: ");
//    tft.println(taskTime);
  }
  //================================Warning/Alarm Task==============================================
  void WarningAlarmSubsystemFunction(void *data)
{
    unsigned long t1 = millis();
    warningAlarmSubsystemData* warningAlarmData = (warningAlarmSubsystemData*) data;

    //Temperature range 36.1C to 37.8C  //Temperature should not be unsigned int, float is more proper...
    if (*(unsigned int*)(warningAlarmData->temperatureRawPtr) < 36.1 ||
        *(unsigned int*)(warningAlarmData->temperatureRawPtr) > 37.8) {
      *(unsigned int*)(warningAlarmData->tempOutOfRangePtr) = 1; 
    } else {
      *(unsigned int*)(warningAlarmData->tempOutOfRangePtr) = 0;
    }
    if (*(unsigned int*)(warningAlarmData->systolicPressRawPtr) > 120 || 
        *(unsigned int*)(warningAlarmData->diastolicPressRawPtr) < 80) {
      *(unsigned int*)(warningAlarmData->bpOutOfRangePtr) = 1; 
    } else {
      *(unsigned int*)(warningAlarmData->bpOutOfRangePtr) = 0; 
    }
    if (*(unsigned int*)(warningAlarmData->pulseRateRawPtr) > 100 || 
        *(unsigned int*)(warningAlarmData->pulseRateRawPtr) < 60) {
      *(unsigned int*)(warningAlarmData->pulseOutOfRangePtr) = 1; 
    } else {
      *(unsigned int*)(warningAlarmData->pulseOutOfRangePtr) = 0;
    }
    unsigned long t2 = millis();
    unsigned long taskTime = t2-t1;
//    tft.print("Warning Time: ");
//    tft.println(taskTime);
}

  
  //=====================================Display Task=============================================
  void DisplaySubsystemFunction(void* data) {
    unsigned long t1 = millis();
    displaySubsystemData* displayData = (displaySubsystemData*) data;
    tft.setTextColor(GREEN); tft.setTextSize(2);

    // temperature 
    tft.println("Temperature");
    tft.print("<");
    tft.fillRect(10, 15, 65, 20, BLACK);
    if (*(unsigned int*)(displayData->tempOutOfRangePtr) == 1) {
      tft.setTextColor(RED); tft.setTextSize(2);
    }
    tft.print(*(double*)(displayData->tempCorrectedPtr));
    tft.setTextColor(GREEN); tft.setTextSize(2);
    tft.println("> C");
    tft.println(" ");

    //systolic pressure
    tft.println("Systolic Pressure");
    tft.print("<");
    tft.fillRect(10, 63, 200, 20, BLACK);
    if (*(unsigned int*)(displayData->bpOutOfRangePtr) == 1) {
      tft.setTextColor(RED); tft.setTextSize(2);
    }
    tft.print(*(unsigned char*)(displayData->sysCorrectedPtr));
    tft.setTextColor(GREEN); tft.setTextSize(2);
    tft.println("> mm Hg");
    tft.println(" ");

    //diastolic pressure
    tft.println("Diastolic Pressure");
    tft.print("<");
    tft.fillRect(10, 110, 200, 20, BLACK);
    if (*(unsigned int*)(displayData->bpOutOfRangePtr) == 1) {
      tft.setTextColor(RED); tft.setTextSize(2);
    }
    tft.print(*(unsigned char*)(displayData->diasCorrectedPtr));
    tft.setTextColor(GREEN); tft.setTextSize(2);
    tft.println("> mm Hg");
    tft.println(" ");
    
    //pulse rate
    tft.println("Pulse Rate");
    tft.print("<");
    tft.fillRect(10, 160, 200, 25, BLACK);
    if (*(unsigned int*)(displayData->pulseOutOfRangePtr) == 1) {
      tft.setTextColor(RED); tft.setTextSize(2);
    }
    tft.print(*(unsigned char*)(displayData->prCorrectedPtr));
    tft.setTextColor(GREEN); tft.setTextSize(2);
    tft.println("> BMP>");
    tft.println(" ");
    
    //battery state
    tft.println("Battery");
    tft.print("<");
    tft.fillRect(10, 208, 40, 25, BLACK);
    if (*(unsigned int*)(displayData->batteryStatePtr) < 21) {
      tft.setTextColor(RED); tft.setTextSize(2);
    }
    tft.print(*(unsigned char*)(displayData->batteryStatePtr));
    tft.setTextColor(GREEN); tft.setTextSize(2);
    tft.println(">");
    unsigned long t2 = millis();
    unsigned long taskTime = t2-t1;
//    tft.print("Display time: ");
//    tft.println(taskTime);
  }

//==========================================Status Task================================================
  void StatusSubsystemFunction(void* data)
  {
    unsigned long t1 = millis();
    statusSubsystemData* statusData = (statusSubsystemData*) data;
    *(unsigned short*)(statusData->batteryStatePtr) -= 1;
    unsigned long t2 = millis();
    unsigned long taskTime = t2-t1;
//    tft.print("Status Time: ");
//    tft.println(taskTime);
  }

  TCB* queue[5]; //initialize four pointers of type TCB

  
  // void execute(TCB** queue, unsigned long globalTime);

//======================================Scheduler Data============================================
  typedef struct SchedulerSubsystemData{
    unsigned int addMeasureTask = 0;
    unsigned int addComputeTask = 0;
    
    
  }SchedulerSubsystemData;


//======================================Scheduler Data============================================

  void schedulerSubsystemFunction(void* data) {
  
    
  }

 
void loop(void) {
  //declaring initial variables
  
     
 //===============================MEASURE============================
 
  measureSubsystemData mstd;

  mstd.temperatureRawPtr = &temperatureRaw_uno;
  mstd.systolicPressRawPtr = &systolicPress_uno;
  mstd.diastolicPressRawPtr = &diastolicPress_uno;
  mstd.pulseRateRawPtr = &pulseRateRaw_uno;
  mstd.measurementSelectionPtr = &measurementSelection;
  

//================================== COMPUTE==============================
  computeSubsystemData csd;

  csd.temperatureRawPtr = &temperatureRaw_uno;
  csd.systolicPressRawPtr = &systolicPress_uno;
  csd.diastolicPressRawPtr = &diastolicPress_uno;
  csd.pulseRateRawPtr = &pulseRateRaw_uno;
  csd.tempCorrectedPtr = &tempCorrected;
  csd.sysPressCorrectedPtr = &systolicPressCorrected;
  csd.diasCorrectedPtr = &diastolicPressCorrected;
  csd.prCorrectedPtr = &pulseRateCorrected;

  //==================================WARNING/ALARM================================
  warningAlarmSubsystemData wasd;

  wasd.temperatureRawPtr = &temperatureRaw_uno;
  wasd.systolicPressRawPtr = &systolicPress_uno;
  wasd.diastolicPressRawPtr = &diastolicPress_uno;
  wasd.pulseRateRawPtr = &pulseRateRaw_uno;
  wasd.batteryStatePtr = &batteryState;
  wasd.bpOutOfRangePtr = &bpOutOfRange;
  wasd.tempOutOfRangePtr = &tempOutOfRange;
  wasd.pulseOutOfRangePtr = &pulseOutOfRange;
  
 //================================= DISPLAY===========================
  displaySubsystemData dsd;

  dsd.tempCorrectedPtr = &tempCorrected;
  dsd.sysCorrectedPtr = &systolicPressCorrected;
  dsd.diasCorrectedPtr = &diastolicPressCorrected;
  dsd.prCorrectedPtr = &pulseRateCorrected;
  dsd.batteryStatePtr = &batteryState;
  dsd.bpOutOfRangePtr = &bpOutOfRange;
  dsd.tempOutOfRangePtr = &tempOutOfRange;
  dsd.pulseOutOfRangePtr = &pulseOutOfRange;
  
//==================================Status================================
  statusSubsystemData ssd;

  ssd.batteryStatePtr = &batteryState;

//==================================TFT================================

  TFTkeypadSubsystemData TFTd; 

  TFTd.functionSelectPtr = &functionSelect;
  TFTd.measurementSelectionPtr = &measurementSelection;
  TFTd.alarmAcknowledgePtr = &alarmAcknowledge;
  
  unsigned long start = micros();
  tft.setCursor(0, 0);

  TCB* queue[6]; //initialize five pointers of type TCB
  
  //  Declare task TCBs
  TCB TFTTask = {(void*)&TFTd, TFTkeypadSubsystemFunction};
  TCB measureTask = {(void*)&mstd, MeasureSubsystemFunction}; 
  TCB computeTask = {(void*)&csd, ComputeSubsystemFunction};
  TCB warningAlarmTask = {(void*)&wasd, WarningAlarmSubsystemFunction};
  TCB displayTask = {(void*)&dsd, DisplaySubsystemFunction};
  TCB statusTask = {(void*)&ssd, StatusSubsystemFunction};
  
  TCB* aTCBPtr;// declares a pointer of type TCB aTCBPtr.
    //   Initialize the task queue
  queue[0] = &TFTTask; 
  queue[1] = &measureTask; 
  queue[2] = &computeTask;
  queue[3] = &warningAlarmTask; 
  queue[4] = &displayTask; 
  queue[5] = &statusTask;
  aTCBPtr = queue[0]; //pointers of type TCB set to queue[0] which is input

  
  queue[0]->taskPtr((void*)&TFTd);
  queue[1]->taskPtr((void*)&mstd);
  queue[2]->taskPtr((void*)&csd); 
  queue[3]->taskPtr((void*)&wasd);
  queue[4]->taskPtr((void*)&dsd);
  queue[5]->taskPtr((void*)&ssd);

  
  
  
//  measureSubsystemData* mPtr;
//  computeSubsystemData* cPtr;
//  warningAlarmSubsystemData* wPtr;
//  displaySubsystemData* dPtr;
//  statusSubsystemData *sPtr;
  
//  unsigned long globalTime = millis();
//  if (globalTime - *mPtr->localTime > 5000) {
//    queue[0]->taskPtr((void*)&mstd);
//  } 
//  if (globalTime - *cPtr->localTime > 5000) {
//    queue[1]->taskPtr((void*)&csd); 
//  }
//  if (globalTime - *wPtr->localTime > 5000) {
//    queue[2]->taskPtr((void*)&wasd);
//  }
//  queue[3]->taskPtr((void*)&dsd); 
//  if (globalTime - *sPtr->localTime > 5000) {
//    queue[4]->taskPtr((void*)&ssd);
//  }

//  //  ============EXCECUTION=============
//  queue[0]->taskPtr((void*)&mstd);
//  tft.println("Compute Time: ");
//  unsigned long t1 = micros();
//  queue[1]->taskPtr((void*)&csd); 
//  unsigned long t2 = micros();
//  tft.println(t2-t1);
//
//  tft.println("warning time:");
//  unsigned long t3 = micros();
//  queue[2]->taskPtr((void*)&wasd);
//  unsigned long t4 = micros();
//  tft.println(t4-t3);
//  queue[3]->taskPtr((void*)&dsd);
//  tft.println("status time:");
//  unsigned long t7 = micros();
//  queue[4]->taskPtr((void*)&ssd);
//  unsigned long t8 = micros();
//  tft.println(t8-t7);    
//  
  delay(1000);

}
