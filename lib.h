#ifndef XC_LIBBER_H
#define	XC_LIBBER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/mcc.h"


int8_t DISPLAYBANK_row[11] = { 1, 2, -1, 0, 0, 0, 0, 0, 0, 0 };
uint16_t DISPLAYBANK_col[10] = { 0x00, 0x00, 0, 0, 0, 0, 0, 0, 0, 0 };
bool checkClock = true;
bool writeClock = false;
bool setClock = false;
bool setDir = false;

void Delay(uint8_t length);
void I2CWrite(uint8_t *pdata, uint8_t length, uint16_t address);
void I2CRead(uint8_t *pdata, uint8_t registerAddress, uint8_t length, uint16_t address);

#endif	/* XC_LIBBER_H */

