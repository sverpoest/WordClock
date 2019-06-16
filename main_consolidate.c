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
#include "LEDArray.h"
#include "RN4020.h"
#include "clock.h"
#include "accelerometer.h"
#include "lib.h"
//#include "mcc_generated_files/mtouch/mtouch_button.h"

/*
                         Main application
 */

uint8_t state = 0;
bool settingHours = false;
typedef enum
{
    STATE_RUNNING,
    STATE_SET_START,
    STATE_SET_HOURS,
    STATE_SET_ON,
    STATE_SET_OFF
} CLOCK_STATE;

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
    
    /*BT_SW_WAKEUP_SetLow();
    BT_HW_WAKEUP_SetLow();
    
    Delay(0x10);
    
    
    BT_SW_WAKEUP_SetHigh();
    BT_HW_WAKEUP_SetHigh();*/
    
    RN4020_Initialize();
    
    /*
    Delay(0x30);
    BT_HW_WAKEUP_SetLow();
    Delay(0x30);
    BT_HW_WAKEUP_SetHigh();
    Delay(0x30);
    BT_HW_WAKEUP_SetLow();
    Delay(0x30);
    BT_HW_WAKEUP_SetHigh();
    Delay(0x30);
    BT_HW_WAKEUP_SetLow();
    Delay(0x30);
    BT_HW_WAKEUP_SetHigh();
    Delay(0x30);
    BT_HW_WAKEUP_SetLow();
    Delay(0x30);
    BT_HW_WAKEUP_SetHigh();
    Delay(0x30);
    BT_HW_WAKEUP_SetLow();
    Delay(0x30);
    BT_HW_WAKEUP_SetHigh();
    Delay(0x30);
    BT_HW_WAKEUP_SetLow();
    Delay(0x30);
    BT_HW_WAKEUP_SetHigh();
    Delay(0x30);
    BT_HW_WAKEUP_SetLow();
    Delay(0x30);
    BT_HW_WAKEUP_SetHigh();
    */
    /*
    
    uint8_t     writeBuffer[3];
    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
    
    bool testClock = true, testArr = true;
    
    while(true)
    {
        if(testClock)
        {
            writeBuffer[0] = 0x07;
            writeBuffer[1] = 0x43;

            I2C_MasterWrite(writeBuffer, 2, 0b1101111, &status);
            while(status == I2C_MESSAGE_PENDING);
        }

        if(testArr)
        {
            writeBuffer[0] = 0x00;
            writeBuffer[1] = 0xFF;
            I2C_MasterWrite(writeBuffer, 2, 0b0100000, &status);
            while(status == I2C_MESSAGE_PENDING);
            testArr = true;
            
            writeBuffer[0] = 0x00;
            writeBuffer[1] = 0xFF;
            I2C_MasterWrite(writeBuffer, 2, 0b0100001, &status);
            while(status == I2C_MESSAGE_PENDING);
            testArr = true;
        }
        Delay(0x10);
    }
    */
    
    LEDSetup();
    Delay(0x10);
    ClockStart(true);
    TMR1_SetInterruptHandler(SetCheckClock);
    AccInit();
    Delay(0x10);
    IOCCF2_SetInterruptHandler(SetTime);
    IOCCF3_SetInterruptHandler(SetTurn);
    TMR3_SetInterruptHandler(CheckTurn);
    /*
    while(1)
    {
        AccRead();
        Delay(20);
    }*/
    
    ClockTap(true);ClockTap(true);ClockTap(true);ClockTap(true);
    uint8_t i = 0;
    while (1)
    {
        if(++i == 10 || DISPLAYBANK_row[i] == -1)
            i = 0;
        
        uint8_t row = DISPLAYBANK_row[i];
        if(state == STATE_SET_OFF && 
                ((!settingHours && row > 0 && row < 4) || (settingHours && row > 3)))
            LEDArrayRow(0x00, 0xFFFF);
        else
        {
            LEDArrayRow(DISPLAYBANK_row[i], DISPLAYBANK_col[i]);
        
            if(checkClock && state < STATE_SET_START)
            {
                ClockDisplay(true);
                checkClock = false;
                TMR1_StartTimer();
            }
            if(writeClock)
            {
                ClockWrite();
                writeClock = false;
                TMR1_StartTimer();
            }
        }
    }
}

void SetCheckClock(void)
{
    TMR1_StopTimer();
    if(state > STATE_RUNNING)
    {
        TMR3_StopTimer();
        settingHours = false;
        state = STATE_RUNNING;
        writeClock = true;
    }
    else
        checkClock = true;
}
void SetTurn(void)
{
    TMR3_StopTimer();
    TMR3_Reload();
    if(state > STATE_SET_START)
    {
        if(settingHours)
            state = STATE_RUNNING;
        else
            state = STATE_SET_HOURS;
        settingHours = !settingHours;
    }
    TMR3_StartTimer();
}

void SetTime(void)
{
    if(state > STATE_SET_START)
    {
        TMR1_Reload();
        ClockTap(settingHours);
    }
}

void CheckTurn(void)
{
    switch(state)
    {
        case STATE_RUNNING:
            if(ACC_INT2_GetValue() == 1)
            {
                TMR1_StopTimer();
                state = STATE_SET_START;
            }
            break;
        case STATE_SET_HOURS:
            TMR1_StopTimer();
            state = STATE_SET_START;
            settingHours = (ACC_INT2_GetValue() == 1);
            break;
        case STATE_SET_START:
            if(ACC_INT2_GetValue() == 0)
            {
                TMR1_Reload();
                TMR1_StartTimer();
                state = STATE_SET_ON;
            }
            break;
        case STATE_SET_ON:
            state = STATE_SET_OFF;
            break;
        case STATE_SET_OFF:
            state = STATE_SET_ON;
            break;
    }
}

/*
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
    TMR1_StartTimer();
    WriteLEDSetup();
    bool tmp = false;
    
    
    BT_SW_WAKEUP_SetLow();
    BT_HW_WAKEUP_SetLow();
    
        Delay(0xff);
    
    BT_SW_WAKEUP_SetHigh();
    BT_HW_WAKEUP_SetHigh();
    
    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
    I2C_TRANSACTION_REQUEST_BLOCK readTRB[2];
    uint8_t     dataBuffer[10];
    uint8_t     writeBuffer[10];
    
    writeBuffer[0] = 0x20;
    writeBuffer[1] = 0x57;
    I2C_MasterWrite(writeBuffer, 2, 0x18, &status);
    while(status == I2C_MESSAGE_PENDING);
    
    writeBuffer[0] = 0x22;
    writeBuffer[1] = 0x40;
    I2C_MasterWrite(writeBuffer, 2, 0x18, &status);
    while(status == I2C_MESSAGE_PENDING);
    
    writeBuffer[0] = 0x30;
    writeBuffer[1] = 0x08;
    I2C_MasterWrite(writeBuffer, 2, 0x18, &status);
    while(status == I2C_MESSAGE_PENDING);
    
    
    
    writeBuffer[0] = 0x32;
    writeBuffer[1] = 0x0f;
    I2C_MasterWrite(writeBuffer, 2, 0x18, &status);
    while(status == I2C_MESSAGE_PENDING);
    
    writeBuffer[0] = 0x33;
    writeBuffer[1] = 0x03;
    I2C_MasterWrite(writeBuffer, 2, 0x18, &status);
    while(status == I2C_MESSAGE_PENDING);
    
    
    //writeBuffer[0] = 0x38;
    //writeBuffer[1] = 0x01;
    //I2C_MasterWrite(writeBuffer, 2, 0x18, &status);
    //while(status == I2C_MESSAGE_PENDING);
    
    //writeBuffer[0] = 0x39;
    //writeBuffer[1] = 0x54;
    //I2C_MasterWrite(writeBuffer, 2, 0x18, &status);
   // while(status == I2C_MESSAGE_PENDING);
    
    
    writeBuffer[0] = 0x31;
    
    I2C_MasterWriteTRBBuild(   &readTRB[0],
                                    writeBuffer,
                                    1,
                                    0x18);
    // Build TRB for receiving data
    I2C_MasterReadTRBBuild(    &readTRB[1],
                                    dataBuffer,
                                    1,
                                    0x18);

    while(status != I2C_MESSAGE_FAIL)
    {
        if(ACC_INT1_PORT == 1)
            status = I2C_MESSAGE_PENDING;
        
        I2C_MasterTRBInsert(2, readTRB, &status);

        // wait for the message to be sent or status has changed.
        while(status == I2C_MESSAGE_PENDING);

        
        if (status == I2C_MESSAGE_COMPLETE)
            status = I2C_MESSAGE_PENDING;
    }
    
    
    
    uint8_t     writeBuffer[3];

    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
    writeBuffer[0] = 0x14;

    writeBuffer[1] = 0x00;
    writeBuffer[2] = 0x00;
    I2C_MasterWrite(writeBuffer, 2, 0b0100001, &status);
    while(status == I2C_MESSAGE_PENDING);

    while (1)
    {
        
        WriteLEDArrayRow(row, mask);
        mask = mask << 1;
        if(mask == 0x800)
        {
            mask = 0x01;
            row++;
        }
        if(row == 10)
            row = 0;
        
        Delay(1);
    }
    
    uint16_t mask = 1;
    uint8_t row = 0;
    mask = 0xFFFF;
    while (1)
    {
        
        WriteLEDArrayRow(row++, mask);
        if(row == 10)
            row = 0;
        
        Delay(1);
    }
}
 * 
 * */
/*
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

    
    // this initial value is important
    
    LED_D4_LAT = LED_D5_LAT = LED_D6_LAT = LED_D7_LAT = 0;
    
    TMR1_StartTimer();
    WriteLEDSetup();
    StartClock(false);
    
    uint8_t countDisplay = (displaySize - 1);
    uint8_t countClock = 0;
    uint8_t offset = 0;
    while (1)
    {
        // Communicate with clock if needed
        if(TMR1IF)
        {
            if(countClock++ == 0)
            {
                countClock = 0;
                DisplayClockValue(DISPLAYBANK_row, DISPLAYBANK_col);
            }
            TMR1_Reload();
            TMR1IF = 0;
        }
        //WriteLEDArrayRow(0, 0x40);
        WriteLEDArrayRow(countDisplay, offset==0?0x5555:0xAAAA);
        
        // Set LED display
        // WriteLEDArrayRow(DISPLAYBANK_row[countDisplay], DISPLAYBANK_col[countDisplay]);
  
        if((countDisplay--) == 0)
            countDisplay = (displaySize - 1);
        offset = (offset==0?1:0);
        Delay2000ms();
    }
}
 */

/*
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    LED_D4_LAT = LED_D5_LAT = LED_D6_LAT = LED_D7_LAT = 0;
    
    RN4020_Initialize();
    
    
    //putsUSART((char*)"SF,1");
   // putsUSART((char*)"SS,F0000000");
   // putsUSART((char*)"SR,22000000");
   // Delay2000ms();
   // Delay2000ms();
   // Delay2000ms();
    //putsUSART((char*)"SUW,2A37,1F5300BB00EE00");
    
    WriteLEDSetup();
    LED_D4_LAT = 1;
    
    uint8_t tmp = 0;
    while (1)
    {
        if(tmp == 1)
        {
            if(IO_RC4_PORT == HIGH)
            {
                tmp = 0;
                RN4020_WriteCommand_MultiReceive("LC", true);
                //RN4020_WriteCommand("CURV,2A44", true);
            }
        }
        else if(IO_RC4_PORT == LOW)
            tmp = 1;
        Delay(10);
    }
}*/
/**
 End of File
*/