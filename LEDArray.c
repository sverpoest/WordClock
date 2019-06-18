/*
 * File:   LEDArray.c
 * Author: sebastiaan.verpoest
 *
 * Created on October 24, 2017, 10:09 PM
 */


#include <xc.h>
#include "LEDArray.h"
#include "lib.h"

#define MCP23017_ADDRESS_COL 0b0100000
#define MCP23017_ADDRESS_ROW 0b0100001

uint8_t prevRow = 255;

void LED_Row(uint8_t row, uint16_t mask)
{
    uint8_t     writeBuffer[3];
    
    // Clear the previous data from the LEDs
    if(row != prevRow)
    {
        writeBuffer[0] = (prevRow>7?0x01:0x00);
        writeBuffer[1] = 0xFF;
        I2CWrite(writeBuffer, 2, MCP23017_ADDRESS_ROW);
    }
    
    // Write the new row to the LEDs
    writeBuffer[0] = 0x00;
    writeBuffer[1] = mask & 0xFF;
    writeBuffer[2] = mask >> 8;
    I2CWrite(writeBuffer, 3, MCP23017_ADDRESS_COL);
    
    if(row != prevRow)
    {
        if(row > 7)
        {
            writeBuffer[0] = 0x01;
            writeBuffer[1] = 0xFF - (1 << (row-8));
        }
        else
        {
            writeBuffer[0] = 0x00;
            writeBuffer[1] = 0xFF - (1 << row);
        }
        I2CWrite(writeBuffer, 2, MCP23017_ADDRESS_ROW);
    }
    
    prevRow = row;
    
}

void LED_Initialize()
{
    uint8_t     writeBuffer[3];
    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
    
    writeBuffer[0] = 0x00;
    writeBuffer[1] = 0xFF;
    writeBuffer[2] = 0xFF;
    I2CWrite(writeBuffer, 3, MCP23017_ADDRESS_ROW);
    I2CWrite(writeBuffer, 3, MCP23017_ADDRESS_COL);
    
    writeBuffer[0] = 0x14;
    I2CWrite(writeBuffer, 3, MCP23017_ADDRESS_COL);
}