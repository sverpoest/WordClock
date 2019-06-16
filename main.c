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
#include "bluetooth.h"
#include "clock.h"
#include "accelerometer.h"
#include "lib.h"
//#include "mcc_generated_files/mtouch/mtouch_button.h"

/*
                         Main application
 */

uint8_t mainState = 0;
bool settingHours = false;

bool        blank = false;
uint8_t     action = 0;
uint16_t    tick = 240;
uint8_t     secondaryTick = 0;

uint8_t     localHour = 0;
uint8_t     localMins = 0;
uint8_t     SECOND_MULTIPLIER = 4;

typedef enum
{
    ACTION_NONE,
    ACTION_GETTIME,
    ACTION_GETTIME_BT,
    ACTION_SETTIME
} ACTION;

typedef enum
{
    STATE_RUNNING,
    STATE_BTSETTIME,
    STATE_SMS,
    STATE_LOCATING,
    STATE_BT,
            
    STATE_SET_START,
    STATE_SET_HOURS,
    STATE_SET_ON,
    STATE_SET_OFF
} CLOCK_STATE;

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    LED_Initialize();
    LED_Row(0x00, 0b1111111111111110);
    Delay(100);
    
    /*Bluetooth_Initialize();
    LED_Row(0x00, 0b1111111111111101);
    Delay(100);*/
    
    Clock_Initialize(true);
    LED_Row(0x00, 0b1111111111111011);
    Delay(100);
    
    Acc_Initialize();
    LED_Row(0x00, 0b1111111111110111);
    Delay(100);
    
    TMR1_SetInterruptHandler(Tick);
    
    //IOCCF2_SetInterruptHandler(SetTime);
    IOCCF3_SetInterruptHandler(SetTurn);
    
    uint8_t i = 0;
    while (1)
    {
        if(++i == 10 || DISPLAYBANK_row[i] == -1)
            i = 0;
        
        if(blank)
            LED_Row(0x00, 0xFFFF);
        else
            LED_Row(DISPLAYBANK_row[i], DISPLAYBANK_col[i]);
        
        switch(action)
        {
            case ACTION_GETTIME:
                Clock_Display(true);
                break;
            case ACTION_GETTIME_BT:
                Bluetooth_GetTime();
                break;
            case ACTION_SETTIME:
                Clock_SetTime(localHour, localMins);
                break;
            default:
                break;
        }
        
        action = 0;
    }
}

void Tick(void)
{
    switch(mainState)
    {
        case STATE_RUNNING:
            if((tick % (3600 * SECOND_MULTIPLIER)) == 0)
                action = ACTION_GETTIME_BT;
            else if((tick % (60 * SECOND_MULTIPLIER)) == 0)
                action = ACTION_GETTIME;
            tick++;
            break;
        case STATE_BTSETTIME:
            action = ACTION_SETTIME;
            mainState = STATE_RUNNING;
            break;
        case STATE_SMS:
        case STATE_LOCATING:
            blank = (secondaryTick++ & 0x1);
            if(secondaryTick == 15)
            {
                action = ACTION_GETTIME;
                mainState = STATE_RUNNING;
            }
            break;
        case STATE_BT:
            blank = (secondaryTick++ & 0x1);
            if(secondaryTick == 15)
            {
                action = ACTION_GETTIME_BT;
                mainState = STATE_RUNNING;
            }
            break;
    }
    
}

void SetTime(uint8_t hour, uint8_t mins)
{
    if(mainState == STATE_RUNNING)
        mainState = STATE_BTSETTIME;
    localHour = hour;
    localMins = mins;
}

void AlertSMS(void)
{
    secondaryTick = 0;
    if(mainState == STATE_RUNNING)
        mainState = STATE_SMS;
    
    LED_SMS();
}

void SetLocating(void)
{
    secondaryTick = 0;
    if(mainState == STATE_RUNNING)
        mainState = STATE_LOCATING;
    
    LED_Locating();
}

void SetBluetooth(void)
{
    secondaryTick = 0;
    if(mainState == STATE_RUNNING)
        mainState = STATE_BT;
    
    LED_Bluetooth();
}

void SetTurn(void)
{
    Bluetooth_FindPhone();
}


/**
 End of File
*/