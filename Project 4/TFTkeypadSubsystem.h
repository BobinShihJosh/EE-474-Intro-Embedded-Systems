#ifndef TFTKEYPAD_H_INCLUDED
#define TFTKEYPAD_H_INCLUDED

#include "bool.h"

typedef struct TFTkeypadSubsystemData{
    unsigned int *functionSelectPtr;
    unsigned int *measurementSelectionPtr;
    unsigned int *alarmAcknowledgePtr;
}tftkeypadSubsystemData;

void TFTkeypadSubsystemFunction(void *data);

#endif // TFTKEYPAD_H_INCLUDED
