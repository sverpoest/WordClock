// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _CLOCK_H
#define	_CLOCK_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/mcc.h"

void Clock_Initialize(bool start);
void Clock_SetTime(uint8_t hourIn, uint8_t minsIn);
void Clock_Display(bool fetchTime);
void Clock_Write();
void Clock_Tap(bool hours);

#endif	/* _CLOCK_H */

