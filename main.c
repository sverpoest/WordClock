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
    ACTION_SETTIME
} ACTION;

typedef enum
{
    STATE_RUNNING,
            
    STATE_SET_HOURS,
    STATE_SET_MINS
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
    
    IOCCF2_SetInterruptHandler(TapTime);
    IOCCF3_SetInterruptHandler(SetTurn);
    
    uint8_t i = 0;
    uint8_t row = 0;
    uint16_t mask = 0x0000;
    while (1)
    {
        row = DISPLAYBANK_row[++i];
        if(i == 10 || row == 0xFF)
        {
            i = 0;
            row = DISPLAYBANK_row[i];
        }
        
        if(blank)
        {
            if(mainState == STATE_SET_HOURS)
            {
                if(row < 4)
                    mask = 0x0000;
                else if(row == 4)
                    mask = 0x0780;
                else if(row == 9)
                    mask = 0x0007;
                else
                    mask = 0xFFFF;
            }
            else
            {
                if(row >= 0 && row < 4)
                    mask = 0xFFFF;
                else if(row == 4)
                    mask = 0x000F;
                else if(row == 9)
                    mask = 0x07E0;
                else
                    mask = 0x0000;
            }
        }
        else
            mask = 0x0000;
        LED_Row(row, DISPLAYBANK_col[i] | mask);
        
        switch(action)
        {
            case ACTION_GETTIME:
                Clock_Display(true);
                break;
            case ACTION_SETTIME:
                Clock_Write();
                break;
            default:
                break;
        }
        
        action = 0;
    }
}

void Tick(void)
{
    if(action > 0)
        return;
    
    switch(mainState)
    {
        case STATE_RUNNING:
            if((tick % (10 * SECOND_MULTIPLIER)) == 0)
                action = ACTION_GETTIME;
            tick++;
            break;
        case STATE_SET_MINS:
            blank = (secondaryTick++ & 0x1);
            if(secondaryTick == 41)
            {
                secondaryTick = 0;
                mainState = STATE_SET_HOURS;
            }
            break;
        case STATE_SET_HOURS:
            blank = (secondaryTick++ & 0x1);
            if(secondaryTick == 41)
            {
                action = ACTION_SETTIME;
                mainState = STATE_RUNNING;
            }
            break;
    }
}

void SetTurn(void)
{
    secondaryTick = 0;
    action = 0;
    mainState = STATE_SET_MINS;
}

void TapTime(void)
{
    if(mainState != STATE_SET_HOURS && mainState != STATE_SET_MINS)
        return;
    
    secondaryTick &= 0x1;
    Clock_Tap(mainState == STATE_SET_HOURS);
}


/**
 End of File
*/