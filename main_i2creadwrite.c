/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15
        Device            :  PIC16F1619
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"
#include "main.h"
#include "mcc_generated_files/mtouch/mtouch_button.h"

/*
                         Main application
 */
#define MCP23017_ADDRESS 0b0100000

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    uint8_t sending = 0;
    I2C_TRANSACTION_REQUEST_BLOCK readTRB[2];
    uint8_t     writeBufferrow[3];
    uint8_t     writeBufferlat[3];
    uint8_t     readBuffer[1];
    uint8_t     dataBuffer[11];
    uint16_t     rollover = 0x400; 
    uint16_t     rolloverr = 0x4; 

    
    // this initial value is important
    status = I2C_MESSAGE_PENDING;
    
    dataBuffer[0] = 0x00;
    dataBuffer[1] = 0x00;
    dataBuffer[2] = 0x00;
    dataBuffer[3] = 0x00;
    dataBuffer[4] = 0x00;
    dataBuffer[5] = 0x00;
    dataBuffer[6] = 0x00;
    dataBuffer[7] = 0x00;
    dataBuffer[8] = 0x00;
    dataBuffer[9] = 0x00;
    dataBuffer[10] = 0x00;
    
    readBuffer[0] = 0x05;
    LED_D4_LAT = LED_D5_LAT = LED_D6_LAT = LED_D7_LAT = 0;
    


    
    writeBufferrow[0] = 0x14;
    writeBufferrow[1] = 0xFF;
    writeBufferrow[2] = 0xFE;
    
    I2C_MasterWrite(   writeBufferrow,
                            3,
                            MCP23017_ADDRESS,
                            &status);

    while(status == I2C_MESSAGE_PENDING);
    
    writeBufferlat[0] = 0x14;
    writeBufferlat[1] = 0x00;
    writeBufferlat[2] = 0x00;
    
    I2C_MasterWrite(   writeBufferlat,
                            3,
                            MCP23017_ADDRESS,
                            &status);

    while(status == I2C_MESSAGE_PENDING);
    
    writeBufferlat[0] = 0x00;
    writeBufferlat[1] = 0x00;
    writeBufferlat[2] = 0x00;
    
    I2C_MasterWrite(   writeBufferlat,
                            3,
                            MCP23017_ADDRESS,
                            &status);

    while(status == I2C_MESSAGE_PENDING);
    
    I2C_MasterWrite(   writeBufferlat,
                            3,
                            MCP23017_ADDRESS | 1,
                            &status);

    while(status == I2C_MESSAGE_PENDING);
                
    LED_D5_LAT = LED_D6_LAT = LED_D7_LAT = 0;
    LED_D4_LAT = 1;
    
    writeBufferlat[0] = 0x14;
    while (1)
    {
        rollover = rollover << 1;
        
        
        if(rollover == 0x100)
            writeBufferlat[1] = 0;
        if(rollover == 0x800)
        {
            writeBufferlat[2] = 0;
            rollover = 1;
            /*
            rolloverr = rolloverr << 1;
            if(rolloverr == 0x8)
                rolloverr = 1;
            
            if(rolloverr == 1)
            {
                writeBufferrow[1] = 0x00;
                writeBufferrow[2] = 0x7F;
            }
            else if(rolloverr == 2)
            {
                writeBufferrow[1] = 0x00;
                writeBufferrow[2] = 0xBF;
            }
            else if(rolloverr == 4)
            {
                writeBufferrow[1] = 0x00;
                writeBufferrow[2] = 0xDF;
            }*/
        }
            {
                writeBufferrow[1] = 0x00;
                writeBufferrow[2] = 0x00;
            }
            I2C_MasterWrite(   writeBufferrow,
                                    3,
                                    MCP23017_ADDRESS,
                                    &status);

            while(status == I2C_MESSAGE_PENDING);
        
        //if(sending == 0)
        {
            uint16_t temp = rollover;
            
            if(rollover == 0x100)
                writeBufferlat[2] = 0x4;
            else if(rollover == 0x200)
                writeBufferlat[2] = 0x2;
            else if(rollover == 0x400)
                writeBufferlat[2] = 0x1;
            else
                writeBufferlat[1] = rollover;

            I2C_MasterWrite(   writeBufferlat,
                                    3,
                                    MCP23017_ADDRESS | 1,
                                    &status);

            while(status == I2C_MESSAGE_PENDING);

            /*writeBufferlat[0] = 0x00;
            writeBufferlat[1] = 0x00;
            writeBufferlat[2] = 0x00;

            I2C_MasterWrite(   writeBufferlat,
                                    3,
                                    MCP23017_ADDRESS,
                                    &status);

            while(status == I2C_MESSAGE_PENDING);*/
            
           // Delay2000ms();
            /*
            I2C_MasterWriteTRBBuild(   &readTRB[0],
                                            readBuffer,
                                            1,
                                            MCP23017_ADDRESS);
            // Build TRB for receiving data
            I2C_MasterReadTRBBuild(    &readTRB[1],
                                            dataBuffer,
                                            11,
                                            MCP23017_ADDRESS);

            while(status != I2C_MESSAGE_FAIL)
            {
                I2C_MasterTRBInsert(2, readTRB, &status);

                // wait for the message to be sent or status has changed.
                while(status == I2C_MESSAGE_PENDING);

                if (status == I2C_MESSAGE_COMPLETE)
                    break;
            }

            if (status == I2C_MESSAGE_COMPLETE)
            {
                LED_D4_LAT = LED_D5_LAT = LED_D7_LAT = 0;
                LED_D6_LAT = 1;
            }
            else
            {
                LED_D4_LAT = LED_D6_LAT = LED_D5_LAT = 0;
                LED_D7_LAT = 1;
            }*/

            //sending = 0;
        }
    }
}

void WriteLEDArrayRow(uint8_t row, uint16_t mask)
{
    uint8_t     writeBuffer[3];
    I2C_MESSAGE_STATUS status;
    
    writeBuffer[0] = 0x14;
    if(row == 0)
    {
        writeBuffer[1] = 0x00;
        writeBuffer[2] = 0x7F;
    }
    else if(row == 1)
    {
        writeBuffer[1] = 0x00;
        writeBuffer[2] = 0xBF;
    }
    else if(row == 2)
    {
        writeBuffer[1] = 0x00;
        writeBuffer[2] = 0xDF;
    }
    I2C_MasterWrite(writeBuffer, 3, MCP23017_ADDRESS, &status);
    while(status == I2C_MESSAGE_PENDING);
    
    
    writeBuffer[1] = mask & 0xFF;
    writeBuffer[2] = mask >> 8;
    
    I2C_MasterWrite(writeBuffer, 3, MCP23017_ADDRESS | 1, &status);
    while(status == I2C_MESSAGE_PENDING);
}


void Delay2000ms(void) {
    uint8_t i = 0;
    for (i = 0; i < 2; i++)
        __delay_ms(20);
}
/**
 End of File
*/