// IMPORTANT: Elegoo_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Elegoo_TFTLCD.h FOR SETUP.
//Technical support:goodtft@163.com

#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
//#include "globals.h"
Elegoo_GFX_Button buttons[15];


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

// Color definitions
#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F

/******************* UI details */
#define BUTTON_X 50
#define BUTTON_Y 90
#define BUTTON_W 80
#define BUTTON_H 25
#define BUTTON_SPACING_X 30
#define BUTTON_SPACING_Y 8
#define BUTTON_TEXTSIZE 2

// text box where numbers go
#define TEXT_X 0
#define TEXT_Y 10
#define TEXT_W 300
#define TEXT_H 50
#define TEXT_TSIZE 2
#define TEXT_TCOLOR ILI9341_MAGENTA
// the data (phone #) we store in the textfield
#define TEXT_LEN 16
char textfield[TEXT_LEN+1] = "";
uint8_t textfield_i=0;


#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

//Touch For New ILI9341 TP
#define TS_MINX 30
#define TS_MAXX 920

#define TS_MINY 120
#define TS_MAXY 900
// We have a status line for like, is FONA working
#define STATUS_X 65
#define STATUS_Y 10

// Print something in the mini status bar with either flashstring

#define MINPRESSURE 10
#define MAXPRESSURE 1000

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Elegoo_TFTLCD tft;


  
  // declaring tasks;
  void TFTkeypadSubsystemFunction(void *data);
  void MeasureSubsystemFunction(void* data);
  void ComputeSubsystemFunction(void* data);
  void DisplaySubsystemFunction(void* data);
  void WarningAlarmSubsystemFunction(void* data);
  void StatusSubsystemFunction(void* data); 

  // making TCB 
  typedef struct Node
  {
    void* taskDataPtr; //a pointer to void (void* pointer) used to reference the data for the task.
    void (*taskPtr)(void*);//a pointer to a function taking a void* argument and returning a void.
    struct Node* next; //pointer that stores the address of the right node
    struct Node* prev;  //pointer that stores the address of the left node
  } TCB;


 // this is code for the UNO. The UNO will take the measure subsystem task. It will simulate the
 // data given initial variables and communicate with the uno when called.
 //===================================MeasureSubsystem DATA==============================================
  //declaring initial variables
  unsigned int temperatureRaw_uno;
  unsigned int systolicPress_uno;
  unsigned int diastolicPress_uno;
  unsigned int pulseRateRaw_uno;
  //unsigned int respirationRateRaw;
  unsigned short measurementSelection = 0;
  unsigned short functionSelect = 0;
   
  typedef struct MeasureSubsystemData{
    unsigned int *temperatureRawPtr;
    unsigned int *systolicPressRawPtr;
    unsigned int *diastolicPressRawPtr;
    unsigned int *pulseRateRawPtr;
    unsigned long *localTime;
    unsigned short *measurementSelectionPtr;
    unsigned short *functionSelectPtr;

  } measureSubsystemData;

 //===================================ComputeSubsystem DATA========================================== 

  double tempCorrected = 75;
  unsigned char systolicPressCorrected = 80;
  unsigned char diastolicPressCorrected = 80;
  unsigned char pulseRateCorrected = 50;  
  
  typedef struct ComputeSubsystemData{
    unsigned short *functionSelectPtr;
    unsigned int *temperatureRawPtr;
    unsigned int *systolicPressRawPtr;
    unsigned int *diastolicPressRawPtr;
    unsigned int *pulseRateRawPtr;
    double *tempCorrectedPtr;
    unsigned char *sysPressCorrectedPtr;
    unsigned char *diasCorrectedPtr;
    unsigned char *prCorrectedPtr;
    unsigned long *localTime;
  }computeSubsystemData;
  
  //================================Warning/Alarm Subsystem DATA==============================================

  unsigned char bpOutOfRange = 0;
  unsigned char tempOutOfRange = 0;
  unsigned char pulseOutOfRange = 0;
  unsigned char rrOutOfRange = 0;
  bool bpHigh = false;
  bool tempHigh = false;
  bool pulseLow = false;
  bool rrLow = false;
  bool rrHigh = false;
  bool lowBattery = false;
  
  typedef struct WarningAlarmSubsystemData{
    unsigned short *functionSelectPtr;
    // Data Pointers
    unsigned int *temperatureRawPtr;
    unsigned int *systolicPressRawPtr;
    unsigned int *diastolicPressRawPtr;
    unsigned int *pulseRateRawPtr;
    unsigned int *respirationRateRawPtr;
    unsigned short *batteryStatePtr;
    // FOR ALARMS - RED
    unsigned char *bpOutOfRangePtr;
    unsigned char *tempOutOfRangePtr;
    unsigned char *pulseOutOfRangePtr;
    unsigned char *rrOutOfRangePtr;
    bool *lowBatteryPtr;
    // FOR WARNING - ORANGE
    bool *bpHighPtr;
    bool *tempHighPtr;
    bool *pulseLowPtr;
    bool *rrLowPtr;
    bool *rrHighPtr;
    unsigned long *localTime;
    unsigned short *alarmAcknowledgePtr;
  } warningAlarmSubsystemData;

  
 //===================================DisplaySubsystem DATA==============================================
  //declaring initial variables

  //Status
  unsigned short batteryState = 200;
  
  typedef struct DisplaySubsystemData{
    unsigned short *functionSelectPtr;
    double* tempCorrectedPtr;
    unsigned char* sysCorrectedPtr;
    unsigned char* diasCorrectedPtr;
    unsigned char* prCorrectedPtr;
    unsigned short* batteryStatePtr;
    // FOR ALARMS - RED
    unsigned char *bpOutOfRangePtr;
    unsigned char *tempOutOfRangePtr;
    unsigned char *pulseOutOfRangePtr;
    unsigned char *rrOutOfRangePtr;
    unsigned char *lowBatteryPtr;
    // FOR WARNING - ORANGE
    bool *bpHighPtr;
    bool *tempHighPtr;
    bool *pulseLowPtr;
    bool *rrLowPtr;
    bool *rrHighPtr;
    unsigned long *localTime;
    unsigned short *alarmAcknowledgePtr;
  } displaySubsystemData;


  //================================Status Subsystem DATA==============================================
  typedef struct StatusSubsystemData{
    unsigned short* batteryStatePtr;
    unsigned long *localTime;
  }statusSubsystemData;

  //================================TFT Subsystem DATA==============================================
  unsigned short alarmAcknowledge = 0;
  bool enableDisplay = false;
  
  typedef struct TFTkeypadSubsystemData{
    unsigned short *functionSelectPtr;
    unsigned short *measurementSelectionPtr;
    unsigned short *alarmAcknowledgePtr;
    bool *enableDisplayPtr;
  }tftkeypadSubsystemData;

  //================================TFT TASK FUNCTION==============================================
//Elegoo_GFX_Button buttons[15];

  void TFTkeypadSubsystemFunction(void *data)
{
    //FunctionSelect = 0: Take Measurement task; FunctionSelect = 1: Take Display/Acknowledgement task
    //MeasurementSelectionPtr =0: Take temperature measurement;
    //MeasurementSelectionPtr =1: Take bloodpressure measurement;
    //MeasurementSelectionPtr =2: Take pulserate measurement;
    //MeasurementSelectionPtr =3: Take respiration measurement;
    tftkeypadSubsystemData *TFTData = (tftkeypadSubsystemData*) data;
    //*(TFTData->measurementSelectionPtr) = 1;
        unsigned long t1 = millis();
    int out = 1;
    while (out == 1) {

    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    pinMode(XP, OUTPUT);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(YM, OUTPUT);

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
      p.x = (tft.width() - map(p.x, TS_MINX, TS_MAXX, tft.width(), 0));
      p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));//
     }
    for (uint8_t b=0; b<10; b++) {
      if (buttons[b].contains(p.x, p.y)) {
        buttons[b].press(true);  // tell the button it is pressed
        
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }
    // now we can ask the buttons if their state has changed
    for (uint8_t b=0; b<10; b++) {
      if (buttons[b].justReleased()) {
        buttons[b].drawButton();  // draw normal
      }
      if (buttons[b].justPressed()) {
          buttons[b].drawButton(true);  // draw invert!
          if (b == 2) {
            Serial.println(F("clicked on display"));
            *(TFTData->enableDisplayPtr) = true;
            out = 2;
          }
          if (b == 1) {
            *(TFTData->functionSelectPtr) = 2;
          buttons[7].initButton(&tft, 250, 40, 150, 25, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
                        "Acknowledge", 2); 
          buttons[7].drawButton();
            //Serial.println(F("annunciation mode"));
            out = 2;
          }
          
          // clr button! delete char
          if (b == 0) {
            *(TFTData->functionSelectPtr) = 1;
            Serial.println(F("functionselectptr in TFT"));
            Serial.println(*(TFTData->functionSelectPtr));
            //Serial.println(F("Menu mode"));
            tft.setTextColor(GREEN); tft.setTextSize(1);tft.setCursor(210, 100);
            tft.println(F("Take a Measurement"));
            buttons[4].initButton(&tft, 270, 160, 150, 20, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
                        "Temp", 1); 
            buttons[4].drawButton();
  
            buttons[5].initButton(&tft, 270, 190, 150, 20, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
                        "Blood.P", 1); 
            buttons[5].drawButton();
  
            buttons[6].initButton(&tft, 270, 220, 150, 20, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
                        "Pulse.R", 1); 
            buttons[6].drawButton();

            buttons[9].initButton(&tft, 270, 130, 150, 20, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
                        "Resp.R", 1); 
            buttons[9].drawButton();
            out = 2;
          }
          if (b == 4) {
                Serial.println(F("measure temperature"));
                *(TFTData->functionSelectPtr) = 1;
                *(TFTData->measurementSelectionPtr) = 1;
                Serial.println(*(TFTData->measurementSelectionPtr));
                out = 2;
              }
      
          if (b == 5) {
                Serial.println(F("measure blood pressure"));
                *(TFTData->functionSelectPtr) = 1;
                *(TFTData->measurementSelectionPtr) = 2;
                Serial.println(*(TFTData->measurementSelectionPtr));
                out = 2;
              }
    
          if (b == 6) {
                Serial.println(F("measure pulse rate"));
                *(TFTData->functionSelectPtr) = 1;
                *(TFTData->measurementSelectionPtr) = 3;
                Serial.println(*(TFTData->measurementSelectionPtr));
                out = 2;
              }
          if (b == 9) {
                Serial.println(F("measure respiration rate"));
                *(TFTData->functionSelectPtr) = 1;
                *(TFTData->measurementSelectionPtr) = 4;
                Serial.println(*(TFTData->measurementSelectionPtr));
                out = 2;
              }
          
          if (b == 7) {
            *(TFTData->alarmAcknowledgePtr) = 1;
            out = 2;
          }

          

          //delay(100); // UI debouncing
      }
      
    }
    //Serial.println(F("scanning button press"));
    }
    unsigned long t2 = millis();
    unsigned long tasktime = t2-t1;
    Serial.print(F("task time : "));
    Serial.println(tasktime);

   
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
    Serial.println(F("functionselectptr in measure"));
    Serial.println(*(measureData->functionSelectPtr));
    Serial.println(F("measureselectptr in measure"));
            Serial.println(*(measureData->measurementSelectionPtr));
     
      if (*(measureData->measurementSelectionPtr) == 1) {
        Serial1.print('A');
        Serial.println(F("flag sent"));
      } else if (*(measureData->measurementSelectionPtr) == 2) {
        Serial1.print('A');
        Serial.println(F("flag sent"));
      } else if (*(measureData->measurementSelectionPtr) == 3) {
        Serial1.print('A');
        Serial.println(F("flag sent"));
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
//          Serial.print("The temperature is:"); Serial.println(temperatureRaw_uno);
//          Serial.print("The systolic pressure is:"); Serial.println(systolicPress_uno);
//          Serial.print("The diastolic pressure is:"); Serial.println(diastolicPress_uno);
//          Serial.print("The pulse rate is:"); Serial.println(pulseRateRaw_uno);
//          Serial.println();
          
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
    //*(computeData->measurementSelectionPtr) = 0;
    *(computeData->functionSelectPtr) = 0;
    //Serial.println(F("functionselectptr in compute"));
    //Serial.println(*(computeData->functionSelectPtr));
  }
  //================================Warning/Alarm Task==============================================
  void WarningAlarmSubsystemFunction(void *data)
{
        warningAlarmSubsystemData* warningAlarmData = (warningAlarmSubsystemData*) data;
    unsigned int temp = *warningAlarmData->temperatureRawPtr;
    unsigned int systolicPress = *warningAlarmData->systolicPressRawPtr;
    unsigned int diastolicPress = *warningAlarmData->diastolicPressRawPtr;
    unsigned int pulseRate = *warningAlarmData->pulseOutOfRangePtr;
    unsigned int respirationRate = *warningAlarmData->respirationRateRawPtr;
    unsigned int battery = *warningAlarmData->batteryStatePtr;
    unsigned short acknowledge = *warningAlarmData->alarmAcknowledgePtr;

    // Temp warning & alarm
    if (temp < 36.1 * 0.95 || temp > 37.8 * 1.05) {
        *warningAlarmData->tempHighPtr = true; // need to be orange and falsh at 1 sec rate
        if ((temp < 36.1 * 0.85 || temp > 37.8 * 1.15) && acknowledge == 0) {
            *warningAlarmData->tempOutOfRangePtr = 1; // need to be red and flash at 1 sec rate    
        }
    } else {
        *warningAlarmData->tempOutOfRangePtr = 0;
        *warningAlarmData->tempHighPtr = false;
    } 
    // BP warning & alarm
    if (systolicPress < 120 * 0.95 || systolicPress > 130 * 1.05 || diastolicPress < 70 * 0.95 || diastolicPress > 80 * 1.05) {
        *warningAlarmData->bpHighPtr = true; // need to be orange and flash at 0.5 sec rate
        if ((systolicPress < 120 * 0.8 || systolicPress > 130 * 1.2) && acknowledge == 0) {
            *warningAlarmData->bpOutOfRangePtr = 1; // need to be red and flash at 0.5 sec rate
        }
    } else {
        *warningAlarmData->bpHighPtr = false;
        *warningAlarmData->bpOutOfRangePtr = 0;
    }
    // PR warning & alarm
    if (pulseRate < 60 * 0.95 || pulseRate > 100 * 1.05) {
        *warningAlarmData->pulseLowPtr = true; // Oragne & flash 2 sec rate
        if ((pulseRate < 60 * 0.85 || pulseRate > 100 * 1.15) && acknowledge == 0) {
            *warningAlarmData->pulseOutOfRangePtr = 1; // Red & flash 2 sec rate
        }
    } else {
        *warningAlarmData->pulseLowPtr = false;
        *warningAlarmData->pulseOutOfRangePtr = 0;
    }
    // RR warning & alarm
    if (respirationRate < 12 * 0.95) {
        *warningAlarmData->rrLowPtr = true; // Orange but no flash
        if ((respirationRate < 12 * 0.85) && acknowledge == 0) {
            *warningAlarmData->rrOutOfRangePtr = 1; // Red but no flash
        }
    } else if (respirationRate > 25 * 1.05) {
        *warningAlarmData->rrHighPtr = true; // Orange but no flash
        if ((respirationRate > 25 * 1.15) && acknowledge == 0) {
            *warningAlarmData->rrOutOfRangePtr = 1; // Red but no flash
        }
    } else {
        *warningAlarmData->rrLowPtr = false;
        *warningAlarmData->rrHighPtr = false;
        *warningAlarmData->rrOutOfRangePtr = 0;
    }
    // Battery warning & alarm
    if (battery < 40) {
        *warningAlarmData->lowBatteryPtr = 1; // Red but no flash
    }
}

  
  //=====================================Display Task=============================================
  void DisplaySubsystemFunction(void* data) {
    unsigned long t1 = millis();
    displaySubsystemData* displayData = (displaySubsystemData*) data;
    tft.setTextColor(GREEN); tft.setTextSize(1);tft.setCursor(0, 0);


    // temperature 
    tft.println("Temperature");
    tft.print("<");
    tft.fillRect(5, 7, 35, 10, BLACK);
    if (*(unsigned int*)(displayData->tempOutOfRangePtr) == 1) {
      tft.setTextColor(RED); //tft.setTextSize(2);
    }
    tft.print(*(double*)(displayData->tempCorrectedPtr));
    tft.setTextColor(GREEN); //tft.setTextSize(2);
    tft.println("> C");
    tft.println(" ");

    //systolic pressure
    tft.println("Systolic Pressure");
    tft.print("<");
    tft.fillRect(5, 32, 70, 10, BLACK);
    if (*(unsigned int*)(displayData->bpOutOfRangePtr) == 1) {
      tft.setTextColor(RED); //tft.setTextSize(2);
    }
    tft.print(*(unsigned char*)(displayData->sysCorrectedPtr));
    tft.setTextColor(GREEN); //tft.setTextSize(2);
    tft.println("> mm Hg");
    tft.println(" ");

    //diastolic pressure
    tft.println("Diastolic Pressure");
    tft.print("<");
    tft.fillRect(5, 55, 70, 10, BLACK);
    if (*(unsigned int*)(displayData->bpOutOfRangePtr) == 1) {
      tft.setTextColor(RED); //tft.setTextSize(2);
    }
    tft.print(*(unsigned char*)(displayData->diasCorrectedPtr));
    tft.setTextColor(GREEN); //tft.setTextSize(2);
    tft.println("> mm Hg");
    tft.println(" ");
    
    //pulse rate
    tft.println("Pulse Rate");
    tft.print("<");
    tft.fillRect(5, 79, 60, 10, BLACK);
    if (*(unsigned int*)(displayData->pulseOutOfRangePtr) == 1) {
      tft.setTextColor(RED); //tft.setTextSize(2);
    }
    tft.print(*(unsigned char*)(displayData->prCorrectedPtr));
    tft.setTextColor(GREEN); //tft.setTextSize(2);
    tft.println("> BMP>");
    tft.println(" ");
    
    //battery state
    tft.println("Battery");
    tft.print("<");
    tft.fillRect(5, 104, 50, 10, BLACK);
    if (*(unsigned int*)(displayData->batteryStatePtr) < 21) {
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
    unsigned short *measurementSelectionPtr;
    unsigned short *functionSelectPtr;
    bool *enableDisplayPtr;
    //unsigned int addMeasureTask = 0;
    //unsigned int addComputeTask = 0;
  }SchedulerSubsystemData;
  
  struct Node* head;
  struct Node* tail;

//  struct Node* GetNewNode(){
//    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//    newNode->taskDataPtr = ;
//    newNode->
//  }
  
  void insert(TCB* Node);
  void insert(TCB* Node) {
    if (head == NULL) {
      head = Node;
      tail = Node;
    } else {
      tail->next = Node;
      Node->prev = tail;
      tail = Node;
    }
    return;
  }

  void deleteNode(TCB* Node);
  void deleteNode(TCB* Node) {
    struct Node* tempNode = Node;
    tempNode = tempNode->prev;
    tempNode->next = NULL;
    tail->prev = NULL;
    tail = tempNode;
  }
  

//======================================Scheduler task============================================

  void schedulerSubsystemFunction(void* data) {
    //declaring initial variables
        unsigned long t1 = millis();

    SchedulerSubsystemData* scheduleData = (SchedulerSubsystemData*) data;

     //===============================MEASURE============================
     
      measureSubsystemData mstd;
    
      mstd.temperatureRawPtr = &temperatureRaw_uno;
      mstd.systolicPressRawPtr = &systolicPress_uno;
      mstd.diastolicPressRawPtr = &diastolicPress_uno;
      mstd.pulseRateRawPtr = &pulseRateRaw_uno;
      mstd.measurementSelectionPtr = &measurementSelection;
      mstd.functionSelectPtr = &functionSelect;
      
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
      csd.functionSelectPtr = &functionSelect;
    
      //==================================WARNING/ALARM================================
      warningAlarmSubsystemData wasd;
      
      wasd.functionSelectPtr = &functionSelect;
      wasd.temperatureRawPtr = &temperatureRaw_uno;
      wasd.systolicPressRawPtr = &systolicPress_uno;
      wasd.diastolicPressRawPtr = &diastolicPress_uno;
      wasd.pulseRateRawPtr = &pulseRateRaw_uno;
      //wasd.respirationRateRawPtr = &respirationRaw;
      wasd.batteryStatePtr = &batteryState;
      
      wasd.bpOutOfRangePtr = &bpOutOfRange;
      wasd.tempOutOfRangePtr = &tempOutOfRange;
      wasd.pulseOutOfRangePtr = &pulseOutOfRange;
      wasd.rrOutOfRangePtr = &rrOutOfRange;
      wasd.lowBatteryPtr = &lowBattery;
      
      wasd.bpHighPtr = &bpHigh;
      wasd.tempHighPtr = &tempHigh;
      wasd.pulseLowPtr = &pulseLow;
      wasd.rrLowPtr = &rrLow;
      wasd.rrHighPtr = &rrHigh;
      wasd.alarmAcknowledgePtr = &alarmAcknowledge;
      //wasd.localTime = &
    

      
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
      dsd.rrOutOfRangePtr = &rrOutOfRange;
      //dsd.lowerBatteryPtr = &lowBattery;
      
      dsd.bpHighPtr = &bpHigh;
      dsd.tempHighPtr = &tempHigh;
      dsd.pulseLowPtr = &pulseLow;
      dsd.rrLowPtr = &rrLow;
      dsd.rrHighPtr = &rrHigh;
      dsd.alarmAcknowledgePtr = &alarmAcknowledge;
      
      dsd.functionSelectPtr = &functionSelect;
      
    //==================================Status================================
      statusSubsystemData ssd;
    
      ssd.batteryStatePtr = &batteryState;
    
    //==================================TFT================================
    
      TFTkeypadSubsystemData TFTd; 
    
      TFTd.functionSelectPtr = &functionSelect;
      TFTd.measurementSelectionPtr = &measurementSelection;
      TFTd.alarmAcknowledgePtr = &alarmAcknowledge;
      TFTd.enableDisplayPtr = &enableDisplay;
      //unsigned long start = micros();
    
      
      //  Declare task TCBs
      TCB TFTTask = {(void*)&TFTd, TFTkeypadSubsystemFunction, NULL, NULL};
      TCB measureTask = {(void*)&mstd, MeasureSubsystemFunction, NULL, NULL}; 
      TCB computeTask = {(void*)&csd, ComputeSubsystemFunction, NULL, NULL};
      TCB warningAlarmTask = {(void*)&wasd, WarningAlarmSubsystemFunction, NULL, NULL};
      TCB displayTask = {(void*)&dsd, DisplaySubsystemFunction, NULL, NULL};
      TCB statusTask = {(void*)&ssd, StatusSubsystemFunction, NULL, NULL};
    
    //  insert(&TFTTask);
    //  insert(&measureTask);
    //  insert(&computeTask);
    //  insert(&warningAlarmTask);
    //  insert(&displayTask);
    //  insert(&statusTask);
      head = NULL;
      tail = NULL;
    
      insert(&TFTTask);
      struct Node* temp = head;
      tail->taskPtr((void*)&TFTd);
      Serial.println(F("Just inserted and executed TFT in SCHEDULER"));
    
      // flag to check if want to add measure to the list and execute it or not.
      if (*(scheduleData->functionSelectPtr) == 1 && *(scheduleData->measurementSelectionPtr)!=0) {
        insert(&measureTask);
        temp = temp->next;
        tail->taskPtr((void*)&mstd);
        deleteNode(&measureTask);
        Serial.println(F("Just inserted, executed, and deleted measure in SCHEDULER"));
        //*(scheduleData->measurementSelectionPtr)=0;
      }
    
      if (*(scheduleData->functionSelectPtr) == 1&& *(scheduleData->measurementSelectionPtr)!=0) {
        insert(&computeTask);
        temp = temp->next;
        tail->taskPtr((void*)&csd);
        deleteNode(&computeTask);
        Serial.println(F("Just inserted, executed, and deleted compute in SCHEDULER"));
        *(scheduleData->measurementSelectionPtr)=0;
      }
      
      insert(&warningAlarmTask);
      temp = temp->next;
      tail->taskPtr((void*)&wasd);
      Serial.println(F("Just inserted and executed warning/alarm in SCHEDULER"));

      if (*(scheduleData->enableDisplayPtr) == true) {
      insert(&displayTask);
      temp = temp->next;
      tail->taskPtr((void*)&dsd);
      Serial.println(F("Just inserted and executed display in SCHEDULER"));
      }
      
      insert(&statusTask);
      temp = temp->next;
      tail->taskPtr((void*)&ssd);
      Serial.println(F("Just inserted and executed status in SCHEDULER"));
    unsigned long t2 = millis();
      unsigned long tasktime = t2-t1;
      Serial.print(F("total task time"));
      Serial.print(tasktime);
      Serial.println(F("================================finished oneround================================"));
  }
void setUp() {
  tft.reset();

  uint16_t identifier = tft.readID();
  if(identifier==0x0101)
  {     
      identifier=0x9341;
  }else {
    identifier=0x9341;
  }

  tft.begin(identifier);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
}

void setup(void) {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println(F("TFT LCD test"));

#ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.8\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Elegoo 2.8\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());
  setUp();
  //NOT COOL BUTTONS
//      buttons[0].initButton(&tft, 70, 170, 50, 20, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
//                          "menu", 1); 
//    buttons[0].drawButton();
//    
//    buttons[1].initButton(&tft, 70, 200, 50, 20, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
//                          "annunciation", 1); 
//    buttons[1].drawButton();
//  
//    buttons[2].initButton(&tft, 70, 140, 50, 20, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
//                          "-", 1); 
//    buttons[2].drawButton();
//    
//    buttons[3].initButton(&tft, 70, 230, 50, 20, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
//                          "-", 1); 
//    buttons[3].drawButton();


//COOL BUTTONS
  buttons[0].initButton(&tft, 80, 175, 40, 40, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
                          "M", 2); 
  buttons[0].drawButton();
    
  buttons[1].initButton(&tft, 30, 175, 30, 30, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
                          "A", 1); 
  buttons[1].drawButton();
  
  buttons[2].initButton(&tft, 130, 175, 30, 30, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
                         "D", 1); 
  buttons[2].drawButton();
    
  buttons[3].initButton(&tft, 80, 220, 30, 30, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
                          "-", 1); 
  buttons[3].drawButton();

  buttons[8].initButton(&tft, 80, 130, 30, 30, ILI9341_GREEN, ILI9341_LIGHTGREY, ILI9341_GREEN,
                          "-", 1); 
  buttons[8].drawButton();

}
 
void loop(void) {
  unsigned long start = micros();
  SchedulerSubsystemData SSSD;
  SSSD.measurementSelectionPtr = &measurementSelection;
  SSSD.functionSelectPtr = &functionSelect;
  SSSD.enableDisplayPtr = &enableDisplay;

  schedulerSubsystemFunction((void*)&SSSD);
  delay(100);
}
