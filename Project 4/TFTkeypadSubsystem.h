#ifndef TFTKEYPAD_H_INCLUDED
#define TFTKEYPAD_H_INCLUDED

#include "bool.h"

typedef struct TFTkeypadSubsystemData{
    unsigned short *functionSelectPtr;
    unsigned short *measurementSelectionPtr;
    unsigned short *alarmAcknowledgePtr;
}tftkeypadSubsystemData;

void TFTkeypadSubsystemFunction(void *data);

#endif // TFTKEYPAD_H_INCLUDED
