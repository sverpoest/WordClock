/*
 * File:   lib.c
 * Author: sebastiaan.verpoest
 *
 * Created on November 11, 2017, 10:32 PM
 */

#include "lib.h"


void Delay(uint8_t length) {
    uint8_t i = 0;
    for (i = 0; i < length; i++)
        __delay_ms(10);
}

void I2CWrite(uint8_t *pdata,
                uint8_t length,
                uint16_t address)
{
    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;

    for(int i = 0; i==0; )
    {
        I2C_MasterWrite(pdata, length, address, &status);
        while(status == I2C_MESSAGE_PENDING);
        
        if (status == I2C_MESSAGE_COMPLETE)
           break;
        
        //Delay(20);
    }
}

void I2CRead(uint8_t *pdata,
                uint8_t registerAddress,
                uint8_t length,
                uint16_t address)
{
    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
    I2C_TRANSACTION_REQUEST_BLOCK readTRB[2];
    uint8_t     readBuffer[1];
    
    readBuffer[0] = registerAddress;
    
    I2C_MasterWriteTRBBuild(   &readTRB[0],
                                    readBuffer,
                                    1,
                                    address);
    // Build TRB for receiving data
    I2C_MasterReadTRBBuild(    &readTRB[1],
                                    pdata,
                                    2,
                                    address);

    while(status != I2C_MESSAGE_FAIL)
    {
        I2C_MasterTRBInsert(2, readTRB, &status);

        // wait for the message to be sent or status has changed.
        while(status == I2C_MESSAGE_PENDING);

        if (status == I2C_MESSAGE_COMPLETE)
           break;
    }
}