// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _LEDARRAY_H
#define	_LEDARRAY_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/mcc.h"


void LED_Initialize();
void LED_Row(uint8_t row, uint16_t mask);

void LED_SMS(void);
void LED_Locating(void);
void LED_Bluetooth(void);

#endif	/* _LEDARRAY_H */

