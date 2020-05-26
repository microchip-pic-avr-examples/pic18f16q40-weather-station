/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
        Device            :  PIC18F16Q40
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.35	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 procedures
#define RA0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define RA0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define RA0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define RA0_GetValue()              PORTAbits.RA0
#define RA0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define RA0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define RA0_SetPullup()             do { WPUAbits.WPUA0 = 1; } while(0)
#define RA0_ResetPullup()           do { WPUAbits.WPUA0 = 0; } while(0)
#define RA0_SetAnalogMode()         do { ANSELAbits.ANSELA0 = 1; } while(0)
#define RA0_SetDigitalMode()        do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set oledC_EN aliases
#define oledC_EN_TRIS                 TRISAbits.TRISA2
#define oledC_EN_LAT                  LATAbits.LATA2
#define oledC_EN_PORT                 PORTAbits.RA2
#define oledC_EN_WPU                  WPUAbits.WPUA2
#define oledC_EN_OD                   ODCONAbits.ODCA2
#define oledC_EN_ANS                  ANSELAbits.ANSELA2
#define oledC_EN_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define oledC_EN_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define oledC_EN_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define oledC_EN_GetValue()           PORTAbits.RA2
#define oledC_EN_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define oledC_EN_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define oledC_EN_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define oledC_EN_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define oledC_EN_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define oledC_EN_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define oledC_EN_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define oledC_EN_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set oledC_RST aliases
#define oledC_RST_TRIS                 TRISAbits.TRISA4
#define oledC_RST_LAT                  LATAbits.LATA4
#define oledC_RST_PORT                 PORTAbits.RA4
#define oledC_RST_WPU                  WPUAbits.WPUA4
#define oledC_RST_OD                   ODCONAbits.ODCA4
#define oledC_RST_ANS                  ANSELAbits.ANSELA4
#define oledC_RST_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define oledC_RST_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define oledC_RST_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define oledC_RST_GetValue()           PORTAbits.RA4
#define oledC_RST_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define oledC_RST_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define oledC_RST_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define oledC_RST_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define oledC_RST_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define oledC_RST_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define oledC_RST_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define oledC_RST_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode()         do { ANSELBbits.ANSELB4 = 1; } while(0)
#define RB4_SetDigitalMode()        do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set AMBIENT aliases
#define AMBIENT_TRIS                 TRISBbits.TRISB5
#define AMBIENT_LAT                  LATBbits.LATB5
#define AMBIENT_PORT                 PORTBbits.RB5
#define AMBIENT_WPU                  WPUBbits.WPUB5
#define AMBIENT_OD                   ODCONBbits.ODCB5
#define AMBIENT_ANS                  ANSELBbits.ANSELB5
#define AMBIENT_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define AMBIENT_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define AMBIENT_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define AMBIENT_GetValue()           PORTBbits.RB5
#define AMBIENT_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define AMBIENT_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define AMBIENT_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define AMBIENT_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define AMBIENT_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define AMBIENT_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define AMBIENT_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define AMBIENT_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set RB6 procedures
#define RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define RB6_GetValue()              PORTBbits.RB6
#define RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define RB6_SetPullup()             do { WPUBbits.WPUB6 = 1; } while(0)
#define RB6_ResetPullup()           do { WPUBbits.WPUB6 = 0; } while(0)
#define RB6_SetAnalogMode()         do { ANSELBbits.ANSELB6 = 1; } while(0)
#define RB6_SetDigitalMode()        do { ANSELBbits.ANSELB6 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()              PORTBbits.RB7
#define RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()             do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()           do { WPUBbits.WPUB7 = 0; } while(0)
#define RB7_SetAnalogMode()         do { ANSELBbits.ANSELB7 = 1; } while(0)
#define RB7_SetDigitalMode()        do { ANSELBbits.ANSELB7 = 0; } while(0)

// get/set RC0 procedures
#define RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RC0_GetValue()              PORTCbits.RC0
#define RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define RC0_SetPullup()             do { WPUCbits.WPUC0 = 1; } while(0)
#define RC0_ResetPullup()           do { WPUCbits.WPUC0 = 0; } while(0)
#define RC0_SetAnalogMode()         do { ANSELCbits.ANSELC0 = 1; } while(0)
#define RC0_SetDigitalMode()        do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set RC1 procedures
#define RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RC1_GetValue()              PORTCbits.RC1
#define RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define RC1_SetPullup()             do { WPUCbits.WPUC1 = 1; } while(0)
#define RC1_ResetPullup()           do { WPUCbits.WPUC1 = 0; } while(0)
#define RC1_SetAnalogMode()         do { ANSELCbits.ANSELC1 = 1; } while(0)
#define RC1_SetDigitalMode()        do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set oledC_RW aliases
#define oledC_RW_TRIS                 TRISCbits.TRISC2
#define oledC_RW_LAT                  LATCbits.LATC2
#define oledC_RW_PORT                 PORTCbits.RC2
#define oledC_RW_WPU                  WPUCbits.WPUC2
#define oledC_RW_OD                   ODCONCbits.ODCC2
#define oledC_RW_ANS                  ANSELCbits.ANSELC2
#define oledC_RW_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define oledC_RW_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define oledC_RW_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define oledC_RW_GetValue()           PORTCbits.RC2
#define oledC_RW_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define oledC_RW_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define oledC_RW_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define oledC_RW_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define oledC_RW_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define oledC_RW_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define oledC_RW_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define oledC_RW_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set oledC_DC aliases
#define oledC_DC_TRIS                 TRISCbits.TRISC5
#define oledC_DC_LAT                  LATCbits.LATC5
#define oledC_DC_PORT                 PORTCbits.RC5
#define oledC_DC_WPU                  WPUCbits.WPUC5
#define oledC_DC_OD                   ODCONCbits.ODCC5
#define oledC_DC_ANS                  ANSELCbits.ANSELC5
#define oledC_DC_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define oledC_DC_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define oledC_DC_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define oledC_DC_GetValue()           PORTCbits.RC5
#define oledC_DC_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define oledC_DC_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define oledC_DC_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define oledC_DC_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define oledC_DC_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define oledC_DC_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define oledC_DC_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define oledC_DC_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set oledC_nCS aliases
#define oledC_nCS_TRIS                 TRISCbits.TRISC6
#define oledC_nCS_LAT                  LATCbits.LATC6
#define oledC_nCS_PORT                 PORTCbits.RC6
#define oledC_nCS_WPU                  WPUCbits.WPUC6
#define oledC_nCS_OD                   ODCONCbits.ODCC6
#define oledC_nCS_ANS                  ANSELCbits.ANSELC6
#define oledC_nCS_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define oledC_nCS_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define oledC_nCS_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define oledC_nCS_GetValue()           PORTCbits.RC6
#define oledC_nCS_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define oledC_nCS_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define oledC_nCS_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define oledC_nCS_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define oledC_nCS_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define oledC_nCS_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define oledC_nCS_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define oledC_nCS_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSELC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSELC7 = 0; } while(0)

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



#endif // PIN_MANAGER_H
/**
 End of File
*/