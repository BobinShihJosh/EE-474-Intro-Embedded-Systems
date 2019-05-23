#ifndef TFTKEYPAD_H_INCLUDED
#define TFTKEYPAD_H_INCLUDED

#include "bool.h"

typedef struct TFTkeypadSubsystemData{
    unsigned int *FunctionSelectPtr;
    unsigned int *MeasurementSelectionPtr;
    unsigned int *AcknowledgePtr;
}tftkeypadSubsystemData;

void TFTkeypadSubsystemFunction(void *data);

#endif // TFTKEYPAD_H_INCLUDED
