/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.35
        Device            :  PIC18F26K42
        Driver Version    :  1.02
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

#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"

void PIN_MANAGER_Initialize(void)
{
    // LATx registers 
    LATA = 0x00;    
    LATB = 0x00;    
    LATC = 0x00;    

    // TRISx registers  
    TRISA = 0xBF;
    TRISB = 0xF9;
    TRISC = 0xE7;

    // ANSELx registers  
    ANSELC = 0x00;
    ANSELB = 0x00;
    ANSELA = 0x00;

    // WPUx registers
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    // ODx registers   
    ODCONA = 0x00;
    ODCONB = 0x06;
    ODCONC = 0x18;
    
    // I2C Pad register settings
    RC3I2C = 0x61;                                                              
    RC4I2C = 0x61;                                                              // I2C slew rate limiting, 10x pull-ups, I2C thresholds
    RB1I2C = 0x61;
    RB2I2C = 0x61;

    // PPS settings
    I2C2SDAPPSbits.I2C2SDAPPS = 0x0A;                                           // RB2->I2C2:SDA2;
    RB1PPS = 0x23;                                                              // RB1->I2C2:SCL2;
    RC3PPS = 0x21;                                                              // RC3->I2C1:SCL1;
    RB2PPS = 0x24;                                                              // RB2->I2C2:SDA2;
    RC4PPS = 0x22;                                                              // RC4->I2C1:SDA1;
    I2C1SDAPPSbits.I2C1SDAPPS = 0x14;                                           // RC4->I2C1:SDA1;
    I2C2SCLPPSbits.I2C2SCLPPS = 0x09;                                           // RB1->I2C2:SCL2;
    I2C1SCLPPSbits.I2C1SCLPPS = 0x13;                                           // RC3->I2C1:SCL1;
}       

/**
 End of File
*/