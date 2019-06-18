/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15.9
        Device            :  PIC16F1619
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LED_D5 aliases
#define LED_D5_TRIS               TRISAbits.TRISA1
#define LED_D5_LAT                LATAbits.LATA1
#define LED_D5_PORT               PORTAbits.RA1
#define LED_D5_WPU                WPUAbits.WPUA1
#define LED_D5_OD                ODCONAbits.ODA1
#define LED_D5_ANS                ANSELAbits.ANSA1
#define LED_D5_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define LED_D5_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define LED_D5_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define LED_D5_GetValue()           PORTAbits.RA1
#define LED_D5_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define LED_D5_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define LED_D5_SetPullup()      do { WPUAbits.WPUA1 = 1; } while(0)
#define LED_D5_ResetPullup()    do { WPUAbits.WPUA1 = 0; } while(0)
#define LED_D5_SetPushPull()    do { ODCONAbits.ODA1 = 1; } while(0)
#define LED_D5_SetOpenDrain()   do { ODCONAbits.ODA1 = 0; } while(0)
#define LED_D5_SetAnalogMode()  do { ANSELAbits.ANSA1 = 1; } while(0)
#define LED_D5_SetDigitalMode() do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set LED_D6 aliases
#define LED_D6_TRIS               TRISAbits.TRISA2
#define LED_D6_LAT                LATAbits.LATA2
#define LED_D6_PORT               PORTAbits.RA2
#define LED_D6_WPU                WPUAbits.WPUA2
#define LED_D6_OD                ODCONAbits.ODA2
#define LED_D6_ANS                ANSELAbits.ANSA2
#define LED_D6_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LED_D6_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LED_D6_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LED_D6_GetValue()           PORTAbits.RA2
#define LED_D6_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LED_D6_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LED_D6_SetPullup()      do { WPUAbits.WPUA2 = 1; } while(0)
#define LED_D6_ResetPullup()    do { WPUAbits.WPUA2 = 0; } while(0)
#define LED_D6_SetPushPull()    do { ODCONAbits.ODA2 = 1; } while(0)
#define LED_D6_SetOpenDrain()   do { ODCONAbits.ODA2 = 0; } while(0)
#define LED_D6_SetAnalogMode()  do { ANSELAbits.ANSA2 = 1; } while(0)
#define LED_D6_SetDigitalMode() do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set BT_SW_WAKEUP aliases
#define BT_SW_WAKEUP_TRIS               TRISAbits.TRISA5
#define BT_SW_WAKEUP_LAT                LATAbits.LATA5
#define BT_SW_WAKEUP_PORT               PORTAbits.RA5
#define BT_SW_WAKEUP_WPU                WPUAbits.WPUA5
#define BT_SW_WAKEUP_OD                ODCONAbits.ODA5
#define BT_SW_WAKEUP_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define BT_SW_WAKEUP_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define BT_SW_WAKEUP_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define BT_SW_WAKEUP_GetValue()           PORTAbits.RA5
#define BT_SW_WAKEUP_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define BT_SW_WAKEUP_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define BT_SW_WAKEUP_SetPullup()      do { WPUAbits.WPUA5 = 1; } while(0)
#define BT_SW_WAKEUP_ResetPullup()    do { WPUAbits.WPUA5 = 0; } while(0)
#define BT_SW_WAKEUP_SetPushPull()    do { ODCONAbits.ODA5 = 1; } while(0)
#define BT_SW_WAKEUP_SetOpenDrain()   do { ODCONAbits.ODA5 = 0; } while(0)

// get/set SDA aliases
#define SDA_TRIS               TRISBbits.TRISB4
#define SDA_LAT                LATBbits.LATB4
#define SDA_PORT               PORTBbits.RB4
#define SDA_WPU                WPUBbits.WPUB4
#define SDA_OD                ODCONBbits.ODB4
#define SDA_ANS                ANSELBbits.ANSB4
#define SDA_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define SDA_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define SDA_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define SDA_GetValue()           PORTBbits.RB4
#define SDA_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define SDA_SetPullup()      do { WPUBbits.WPUB4 = 1; } while(0)
#define SDA_ResetPullup()    do { WPUBbits.WPUB4 = 0; } while(0)
#define SDA_SetPushPull()    do { ODCONBbits.ODB4 = 1; } while(0)
#define SDA_SetOpenDrain()   do { ODCONBbits.ODB4 = 0; } while(0)
#define SDA_SetAnalogMode()  do { ANSELBbits.ANSB4 = 1; } while(0)
#define SDA_SetDigitalMode() do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set SCL aliases
#define SCL_TRIS               TRISBbits.TRISB6
#define SCL_LAT                LATBbits.LATB6
#define SCL_PORT               PORTBbits.RB6
#define SCL_WPU                WPUBbits.WPUB6
#define SCL_OD                ODCONBbits.ODB6
#define SCL_ANS                ANSELBbits.ANSB6
#define SCL_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define SCL_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define SCL_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define SCL_GetValue()           PORTBbits.RB6
#define SCL_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define SCL_SetPullup()      do { WPUBbits.WPUB6 = 1; } while(0)
#define SCL_ResetPullup()    do { WPUBbits.WPUB6 = 0; } while(0)
#define SCL_SetPushPull()    do { ODCONBbits.ODB6 = 1; } while(0)
#define SCL_SetOpenDrain()   do { ODCONBbits.ODB6 = 0; } while(0)
#define SCL_SetAnalogMode()  do { ANSELBbits.ANSB6 = 1; } while(0)
#define SCL_SetDigitalMode() do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set BT_HW_WAKEUP aliases
#define BT_HW_WAKEUP_TRIS               TRISCbits.TRISC0
#define BT_HW_WAKEUP_LAT                LATCbits.LATC0
#define BT_HW_WAKEUP_PORT               PORTCbits.RC0
#define BT_HW_WAKEUP_WPU                WPUCbits.WPUC0
#define BT_HW_WAKEUP_OD                ODCONCbits.ODC0
#define BT_HW_WAKEUP_ANS                ANSELCbits.ANSC0
#define BT_HW_WAKEUP_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define BT_HW_WAKEUP_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define BT_HW_WAKEUP_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define BT_HW_WAKEUP_GetValue()           PORTCbits.RC0
#define BT_HW_WAKEUP_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define BT_HW_WAKEUP_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define BT_HW_WAKEUP_SetPullup()      do { WPUCbits.WPUC0 = 1; } while(0)
#define BT_HW_WAKEUP_ResetPullup()    do { WPUCbits.WPUC0 = 0; } while(0)
#define BT_HW_WAKEUP_SetPushPull()    do { ODCONCbits.ODC0 = 1; } while(0)
#define BT_HW_WAKEUP_SetOpenDrain()   do { ODCONCbits.ODC0 = 0; } while(0)
#define BT_HW_WAKEUP_SetAnalogMode()  do { ANSELCbits.ANSC0 = 1; } while(0)
#define BT_HW_WAKEUP_SetDigitalMode() do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set ACC_INT1 aliases
#define ACC_INT1_TRIS               TRISCbits.TRISC2
#define ACC_INT1_LAT                LATCbits.LATC2
#define ACC_INT1_PORT               PORTCbits.RC2
#define ACC_INT1_WPU                WPUCbits.WPUC2
#define ACC_INT1_OD                ODCONCbits.ODC2
#define ACC_INT1_ANS                ANSELCbits.ANSC2
#define ACC_INT1_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define ACC_INT1_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define ACC_INT1_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define ACC_INT1_GetValue()           PORTCbits.RC2
#define ACC_INT1_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define ACC_INT1_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define ACC_INT1_SetPullup()      do { WPUCbits.WPUC2 = 1; } while(0)
#define ACC_INT1_ResetPullup()    do { WPUCbits.WPUC2 = 0; } while(0)
#define ACC_INT1_SetPushPull()    do { ODCONCbits.ODC2 = 1; } while(0)
#define ACC_INT1_SetOpenDrain()   do { ODCONCbits.ODC2 = 0; } while(0)
#define ACC_INT1_SetAnalogMode()  do { ANSELCbits.ANSC2 = 1; } while(0)
#define ACC_INT1_SetDigitalMode() do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set ACC_INT2 aliases
#define ACC_INT2_TRIS               TRISCbits.TRISC3
#define ACC_INT2_LAT                LATCbits.LATC3
#define ACC_INT2_PORT               PORTCbits.RC3
#define ACC_INT2_WPU                WPUCbits.WPUC3
#define ACC_INT2_OD                ODCONCbits.ODC3
#define ACC_INT2_ANS                ANSELCbits.ANSC3
#define ACC_INT2_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define ACC_INT2_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define ACC_INT2_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define ACC_INT2_GetValue()           PORTCbits.RC3
#define ACC_INT2_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define ACC_INT2_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define ACC_INT2_SetPullup()      do { WPUCbits.WPUC3 = 1; } while(0)
#define ACC_INT2_ResetPullup()    do { WPUCbits.WPUC3 = 0; } while(0)
#define ACC_INT2_SetPushPull()    do { ODCONCbits.ODC3 = 1; } while(0)
#define ACC_INT2_SetOpenDrain()   do { ODCONCbits.ODC3 = 0; } while(0)
#define ACC_INT2_SetAnalogMode()  do { ANSELCbits.ANSC3 = 1; } while(0)
#define ACC_INT2_SetDigitalMode() do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set IO_RC4 aliases
#define IO_RC4_TRIS               TRISCbits.TRISC4
#define IO_RC4_LAT                LATCbits.LATC4
#define IO_RC4_PORT               PORTCbits.RC4
#define IO_RC4_WPU                WPUCbits.WPUC4
#define IO_RC4_OD                ODCONCbits.ODC4
#define IO_RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define IO_RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define IO_RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define IO_RC4_GetValue()           PORTCbits.RC4
#define IO_RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define IO_RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define IO_RC4_SetPullup()      do { WPUCbits.WPUC4 = 1; } while(0)
#define IO_RC4_ResetPullup()    do { WPUCbits.WPUC4 = 0; } while(0)
#define IO_RC4_SetPushPull()    do { ODCONCbits.ODC4 = 1; } while(0)
#define IO_RC4_SetOpenDrain()   do { ODCONCbits.ODC4 = 0; } while(0)

// get/set LED_D7 aliases
#define LED_D7_TRIS               TRISCbits.TRISC5
#define LED_D7_LAT                LATCbits.LATC5
#define LED_D7_PORT               PORTCbits.RC5
#define LED_D7_WPU                WPUCbits.WPUC5
#define LED_D7_OD                ODCONCbits.ODC5
#define LED_D7_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define LED_D7_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define LED_D7_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define LED_D7_GetValue()           PORTCbits.RC5
#define LED_D7_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define LED_D7_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define LED_D7_SetPullup()      do { WPUCbits.WPUC5 = 1; } while(0)
#define LED_D7_ResetPullup()    do { WPUCbits.WPUC5 = 0; } while(0)
#define LED_D7_SetPushPull()    do { ODCONCbits.ODC5 = 1; } while(0)
#define LED_D7_SetOpenDrain()   do { ODCONCbits.ODC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF2 pin functionality
 * @Example
    IOCCF2_ISR();
 */
void IOCCF2_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF2 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF2 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF2_SetInterruptHandler(void* InterruptHandler);

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF2 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF2_SetInterruptHandler() method.
    This handler is called every time the IOCCF2 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(IOCCF2_InterruptHandler);

*/
extern void (*IOCCF2_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF2 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF2_SetInterruptHandler() method.
    This handler is called every time the IOCCF2 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(IOCCF2_DefaultInterruptHandler);

*/
void IOCCF2_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF3 pin functionality
 * @Example
    IOCCF3_ISR();
 */
void IOCCF3_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF3 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF3 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF3_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF3_SetInterruptHandler(void* InterruptHandler);

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF3 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF3_SetInterruptHandler() method.
    This handler is called every time the IOCCF3 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF3_SetInterruptHandler(IOCCF3_InterruptHandler);

*/
extern void (*IOCCF3_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF3 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF3_SetInterruptHandler() method.
    This handler is called every time the IOCCF3 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF3_SetInterruptHandler(IOCCF3_DefaultInterruptHandler);

*/
void IOCCF3_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/