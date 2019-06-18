/*
 * File:   accelerometer.c
 * Author: sebastiaan.verpoest
 *
 * Created on April 15, 2018, 8:03 PM
 */


#include "accelerometer.h"
#include "lib.h"
#define LIS2DH12_ADDRESS 0b0011000

void Acc_Initialize(void)
{
    uint8_t     writeBuffer[8];
    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
    
    writeBuffer[0] = 0xA0;
    writeBuffer[1] = 0x57; // 0x20
    writeBuffer[2] = 0x04; // 0x21
    writeBuffer[3] = 0x80; // 0x22
    writeBuffer[4] = 0x80; // 0x23
    writeBuffer[5] = 0x08; // 0x24
    writeBuffer[6] = 0x20; // 0x25
    I2CWrite(writeBuffer, 7, LIS2DH12_ADDRESS);
    
    uint8_t     dataBuffer[6];
    I2CRead(dataBuffer, 0x31, 1, LIS2DH12_ADDRESS);
    
    writeBuffer[0] = 0x30;
    writeBuffer[1] = 0x00; // 0x30
    I2CWrite(writeBuffer, 2, LIS2DH12_ADDRESS);
    
    writeBuffer[0] = 0xB4;
    writeBuffer[1] = 0x04; // 0x34
    I2CWrite(writeBuffer, 2, LIS2DH12_ADDRESS);
    
    writeBuffer[0] = 0xB6;
    writeBuffer[1] = 0x1f; // 0x36
    writeBuffer[2] = 0x10; // 0x37
    writeBuffer[3] = 0x01; // 0x38
    writeBuffer[4] = 0x10; // 0x39
    writeBuffer[5] = 0x40; // 0x3A
    writeBuffer[6] = 0x05; // 0x3B
    writeBuffer[7] = 0x10; // 0x3C
    I2CWrite(writeBuffer, 8, LIS2DH12_ADDRESS);
    
}

void Acc_ProcessClickSrc(bool hours)
{
    uint8_t     dataBuffer[6];
    I2CRead(dataBuffer, 0x39, 1, LIS2DH12_ADDRESS);
}