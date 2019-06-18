/*
 * File:   clock.c
 * Author: sebastiaan.verpoest
 *
 * Created on October 25, 2017, 10:15 PM
 */


#include "clock.h"
#include "lib.h"

#define MCP79410_ADDRESS 0b1101111

uint8_t DISPLAYBANK_row_l[12] = 
            {
                0, 1, 
                0, 1, 
                0, 1, 
                0, 1, 
                0, 1, 
                0, 1
            };
uint16_t DISPLAYBANK_col_l[20] = 
            {
                0x0001, 0x0001,
                0x0002, 0x0002,
                0x0003, 0x0003,
                0x0004, 0x0004,
                0x0005, 0x0005,
                0x0006, 0x0006,
                0x001B, 0x000F, 0x000F, 0x07E0,
                0x001B, 0x000F, 0x000F, 0x07E0
            };

uint8_t sec = 0;
uint8_t min = 0;
uint8_t hour = 0;

void Clock_Initialize(bool start)
{
    uint8_t     writeBuffer[5];
    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
    
    if(start)
        Clock_Read();
    
    writeBuffer[0] = 0x00;
    if(start)
       writeBuffer[1] = 0x80;
    else
       writeBuffer[1] = 0x00;
    writeBuffer[2] =  min;
    writeBuffer[3] = (0x40 | hour);
    writeBuffer[4] = 0x08;
    I2CWrite(writeBuffer, 5, MCP79410_ADDRESS);
    
    Delay(0x10);
    
    writeBuffer[0] = 0x07;
    // mfp clock off to reduce noise, set to 0x43 to turn on at 32678hz
    writeBuffer[1] = 0x03;
    I2CWrite(writeBuffer, 2, MCP79410_ADDRESS);

}

uint8_t IncHour(uint8_t in)
{
    if(in == 0x09)
        return 0x10;
    else if(in == 0x12)
        return 0x01;
    else
        return in + 1;
}

void Clock_Tap(bool hours)
{
    if(hours)
        hour = IncHour(hour);
    else
    {
        if(min >= 0x55)
            min = 0x00;
        else if((min & 0xf) >= 0x5)
            min = ((min & 0xf0) + 0x10);
        else
            min = ((min & 0xf0) + 0x05);
    }
    
    Clock_Display(false);
}

void Clock_Write()
{
    uint8_t     writeBuffer[4];
    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
    
    writeBuffer[0] = 0x00;
    writeBuffer[1] = 0x80;
    writeBuffer[2] = min;
    writeBuffer[3] = (hour | 0x40);
    I2CWrite(writeBuffer, 4, MCP79410_ADDRESS);
}

void Clock_Read()
{
    uint8_t     dataBuffer[3];

    I2CRead(dataBuffer, 0x00, 3, MCP79410_ADDRESS);
    sec = (dataBuffer[0] & 0x7f);
    min = dataBuffer[1];
    hour = (dataBuffer[2] & 0x1F);
}

void Clock_Display(bool fetchTime)
{
    if(fetchTime)
        Clock_Read();
    
    int8_t*     row = DISPLAYBANK_row;
    uint16_t*   col = DISPLAYBANK_col;
    
    *(row++) = 0;
    *(col++) = 0x7E4;       // IT IS
    
    uint8_t hourDisplay = hour;
    
    if(min >= 0x05)
    {
        if(min < 0x10 || min >= 0x55)
        {
            *(row++) = 2;
            *(col++) = 0x43F;       // FIVE
        }
        else if(min < 0x15 || min >= 0x50)
        {
            if(min >= 0x50)
            {
                *(row++) = 3;
                *(col++) = 0x11F;   // TEN TO  
            }
            else
            {
                *(row++) = 3;
                *(col++) = 0x71F;   // TEN
            }
        }
        else if(min < 0x20 || min >= 0x45)
        {
            *(row++) = 1;
            *(col++) = 0x602;       // A QUARTER
        }
        else if(min < 0x25 || min >= 0x40)
        {
            *(row++) = 2;
            *(col++) = 0x7C0;       // TWENTY
        }
        else if(min < 0x30 || min >= 0x35)
        {
            *(row++) = 2;
            *(col++) = 0x400;       // TWENTYFIVE
        }
        else
        {
            *(row++) = 3;
            *(col++) = 0x7F0;       // HALF
        }
        if(min >= 0x35)
        {
            if(min < 0x50 || min >= 0x55)
            {
                *(row++) = 3;
                *(col++) = 0x1FF;       // TO  
            }
            hourDisplay = IncHour(hourDisplay);
        }
        else
        {
            if(hourDisplay == 0x09)
            {
                hourDisplay = 13;
                *(row++) = 4;
                *(col++) = 0x070;       // PAST NINE
            }
            else
            {
                *(row++) = 4;
                *(col++) = 0x7F0;       // PAST
            }
        }
    }
    
    if(min < 0x05)
    {
        if(hourDisplay == 10)
        {
            *(row++) = 9;
            *(col++) = 0x018;       // TEN O'CLOCK
        }
        else
        {
            *(row++) = 9;
            *(col++) = 0x01F;       // O'CLOCK
        }
    }
    
    switch(hourDisplay)
    {
        case 0x00:
        case 0x12:
            *(row++) = 8;
            *(col++) = 0x01F;       // TWELVE
            break;
        case 0x01:
            *(row++) = 5;
            *(col++) = 0x7F8;       // ONE
            break;
        case 0x02:
            *(row++) = 6;
            *(col++) = 0x0FF;       // TWO
            break;
        case 0x03:
            *(row++) = 5;
            *(col++) = 0x03F;       // THREE
            break;
        case 0x04:
            *(row++) = 6;
            *(col++) = 0x7F0;       // FOUR
            break;
        case 0x05:
            *(row++) = 6;
            *(col++) = 0x70F;       // FIVE
            break;
        case 0x06:
            *(row++) = 5;
            *(col++) = 0x7C7;       // SIX
            break;
        case 0x07:
            *(row++) = 8;
            *(col++) = 0x7E0;       // SEVEN
            break;
        case 0x08:
            *(row++) = 7;
            *(col++) = 0x7E0;       // EIGHT
            break;
        case 0x09:
            *(row++) = 4;
            *(col++) = 0x07F;       // NINE
            break;
        case 0x10:
            *(row++) = 9;
            *(col++) = 0x7F8;       // TEN
            break;
        case 0x11:
            *(row++) = 7;
            *(col++) = 0x01F;       // ELEVEN
            break;
    }
    
    *(row++) = -1;
}