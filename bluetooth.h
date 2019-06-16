// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _BLUETOOTH_H
#define	_BLUETOOTH_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/mcc.h"


void Bluetooth_Initialize();
void Bluetooth_StateStep();
void Bluetooth_WriteCommand_MultiReceive(char s[], bool direct);
void Bluetooth_WriteCommand(char s[], bool direct);
void Bluetooth_Receive_ISR(void);
bool Bluetooth_IsAOK();
bool Bluetooth_IsRXString(char expected[], int8_t length);
void Bluetooth_HandleMessage(void);
void Bluetooth_GetTime(void);
void Bluetooth_FindPhone(void);
uint8_t Bluetooth_CharToInt(uint8_t character);

#endif	/* _BLUETOOTH_H */

