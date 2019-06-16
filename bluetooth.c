#include <xc.h>
#include "bluetooth.h"
#include "lib.h"
#include "main.h"


#define BT_RX_BUFFER 128

typedef enum
{
    BT_NONE,
    BT_CMD,
    BT_AOK,
    BT_REBOOT
} REPLY;

typedef enum
{
    BT_STATE_ERROR = 0,
    BT_STATE_START = 1,
    BT_STATE_INITIALIZED = 8,
    BT_STATE_CONNECTING = 9,
    BT_STATE_CONNECTED = 10
} BT_STATE;

volatile uint8_t eusartRxHead = 0;
volatile uint8_t eusartRxBuffer[BT_RX_BUFFER];

uint8_t state = BT_STATE_START;
uint8_t requiredReply = BT_CMD;
bool multireceive = false;
bool BT_Writing = false;

void Bluetooth_Receive_ISR(void)
{
    if(1 == RC1STAbits.OERR)
    {
        // EUSART error - restart
                                                                                      
        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }
    else
    {
        uint8_t tmp = RC1REG;
        if(tmp == '\n' && !multireceive)
        {
            if(state > BT_STATE_INITIALIZED)
                Bluetooth_HandleMessage();
            else
                Bluetooth_StateStep();
            eusartRxHead = 0;
        }
        else
        {
            // buffer overruns are ignored
            eusartRxBuffer[eusartRxHead++] = tmp;
            if(BT_RX_BUFFER <= eusartRxHead)
                eusartRxHead = 0;
        }
    }
}

bool Bluetooth_IsAOK()
{
    if(requiredReply == BT_NONE)
        return true;
    
    switch(requiredReply)
    {
        case BT_AOK:
            return Bluetooth_IsRXString("AOK", 3);
        case BT_CMD:
            return Bluetooth_IsRXString("CMD", 3);
        case BT_REBOOT:
            return Bluetooth_IsRXString("Reboot", 6);
    }
    
    return true;
}

bool Bluetooth_IsRXString(char expected[], int8_t length)
{
    if((eusartRxHead - 1) < length)
        return false;
    
    for(length = length - 1; length >= 0; length--)
        if(eusartRxBuffer[length] != expected[length])
            return false;
    return true;
}

void Bluetooth_GetTime()
{
    if(state >= BT_STATE_CONNECTED)
    {
        Bluetooth_WriteCommand("CURV,2A2B", true);
    }
}

uint8_t Bluetooth_CharToInt(uint8_t character)
{
    if(character > '9')
        return character - 0x37;
    else
        return character - 0x30;
}

void Bluetooth_HandleMessage()
{
    if(!Bluetooth_IsAOK())
    {
        // Error
        state = BT_STATE_ERROR;
        
        requiredReply = BT_REBOOT;
        Bluetooth_WriteCommand("R,1", true);
        
        return;
    }
    
    requiredReply = BT_NONE;
    if(Bluetooth_IsRXString("R,", 2))
    {
        if(eusartRxHead == 24)
        {
            uint8_t hour = (Bluetooth_CharToInt(eusartRxBuffer[10]) << 4) + 
                                Bluetooth_CharToInt(eusartRxBuffer[11]);
            uint8_t mins = (Bluetooth_CharToInt(eusartRxBuffer[12]) << 4) + 
                                Bluetooth_CharToInt(eusartRxBuffer[13]);
            SetTime(hour, mins);
        }
        else if(eusartRxHead == 8)
        {
            SetLocating();
        }
    }
    else if(Bluetooth_IsRXString("Notify,", 7))
    {
        if(eusartRxHead == 18)
            AlertSMS();
    }
    else if(Bluetooth_IsRXString("ERR", 3))
    {
        state = BT_STATE_ERROR;
        
        requiredReply = BT_REBOOT;
        Bluetooth_WriteCommand("R,1", true);
    }
    else if(Bluetooth_IsRXString("CMD", 3))
    {}
    else if(Bluetooth_IsRXString("AOK", 3))
    {
        if(state == BT_STATE_CONNECTING)
        {
            state = BT_STATE_CONNECTED;
            SetBluetooth();
            
            Bluetooth_GetTime();
        }
    }
    else if(Bluetooth_IsRXString("Connection End", 14))
            state = BT_STATE_INITIALIZED;
    else if(Bluetooth_IsRXString("Connected", 9))
    {
        state = BT_STATE_CONNECTING;
        // Set connected
        requiredReply = BT_AOK;
        Bluetooth_WriteCommand("CUWC,2A2B,1", true);
    }
}

void Bluetooth_StateStep()
{
    if(!Bluetooth_IsAOK())
    {
        // Error
        state = BT_STATE_ERROR;
        
        requiredReply = BT_REBOOT;
        Bluetooth_WriteCommand("R,1", true);
    }
    else
    {
        switch(state++)
        {
            case BT_STATE_ERROR:
               requiredReply = BT_CMD;
               break;
            case BT_STATE_START:
               requiredReply = BT_AOK;
               Bluetooth_WriteCommand("SF,1", true);
               break;
            case 2:
               Bluetooth_WriteCommand("SN,WordClockBT", true);
               break;
            case 3:
               Bluetooth_WriteCommand("SDR,0.1", true);
               break;
            case 4:
               Bluetooth_WriteCommand("SS,80000000", true);
               break;
            case 5:
               Bluetooth_WriteCommand("SR,20060000", true);
               break;
            case 6:
               requiredReply = BT_REBOOT;
               Bluetooth_WriteCommand("R,1", true);
               break;
            case 7:
                requiredReply = BT_CMD;
                break;
            case BT_STATE_INITIALIZED:
            default:
                requiredReply = BT_NONE;
        }
    }
}

void Bluetooth_Initialize()
{
    requiredReply = BT_NONE;
    BT_SW_WAKEUP_SetLow();
    BT_HW_WAKEUP_SetLow();
    
    Delay(200);
    
    eusartRxHead = 0;
    state = 1;
    requiredReply = BT_CMD;
    
    BT_SW_WAKEUP_SetHigh();
    BT_HW_WAKEUP_SetHigh();
}

void Bluetooth_WriteCommand_MultiReceive(char s[], bool direct)
{
    Bluetooth_WriteCommand(s, direct);
    multireceive = true;
}

void Bluetooth_WriteCommand(char s[], bool direct)
{
    BT_Writing = true;
    
    eusartRxHead = 0;
    multireceive = false;
    if(direct)
    {
        uint8_t tmp = PIE1bits.TXIE;
        PIE1bits.TXIE = 0;
        
        while (*s)
            EUSART_Write_Direct(*s++);

        EUSART_Write_Direct(0x0d);
        EUSART_Write_Direct(0x0a);
        
        PIE1bits.TXIE = tmp;
    }
    else
    {
        while (*s)
            EUSART_Write(*s++);

        EUSART_Write(0x0d);
        EUSART_Write(0x0a);
    }
    
    BT_Writing = false;
}

void Bluetooth_FindPhone(void)
{
    // We piggy back on to the SUPPORTED_NEW_ALERT_CATEGORY read to sound the alarm
    if(!BT_Writing)
        Bluetooth_WriteCommand("CURV,2A47", true);
}