/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC18F26K42
        Driver Version    :  2.00
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

#define SLAVE_ADDRESS     0x20                                                  // Slave address, will be right-shifted by I2C driver = 0x40
#define PACKET_SIZE       0x80                                                  // 128 bytes in array
#define SLAVE_EE_ADD      0x00                                                  // Slave's beginning array address location
#define TRANS_CNT         0x81                                                  // Transfer counter value for TX


uint8_t transArray[PACKET_SIZE] =                                               // Array that is written to the slave device
{
   0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0, 0xA1, 0xB1, 0xC1, 0xD1, 0xE1, 0xF1,
   0xA2, 0xB2, 0xC2, 0xD2, 0xE2, 0xF2, 0xA3, 0xB3, 0xC3, 0xD3, 0xE3, 0xF3,
   0xA4, 0xB4, 0xC4, 0xD4, 0xE4, 0xF4, 0xA5, 0xB5, 0xC5, 0xD5, 0xE5, 0xF5,
   0xA6, 0xB6, 0xC6, 0xD6, 0xE6, 0xF6, 0xA7, 0xB7, 0xC7, 0xD7, 0xE7, 0xF7,
   0xA8, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8, 0xA9, 0xB9, 0xC9, 0xD9, 0xE9, 0xF9,
   0xAA, 0xBA, 0xCA, 0xDA, 0xEA, 0xFA, 0xAB, 0xBB, 0xCB, 0xDB, 0xEB, 0xFB,
   0xAC, 0xBC, 0xCC, 0xDC, 0xEC, 0xFC, 0xAD, 0xBD, 0xCD, 0xDD, 0xED, 0xFD,
   0xAE, 0xBE, 0xCE, 0xDE, 0xEE, 0xFE, 0xAF, 0xBF, 0xCF, 0xDF, 0xEF, 0xFF,
   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
   0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
   0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
};
uint8_t RXArray[PACKET_SIZE];                                                   // Array to store received slave data

void main(void)
{
    SYSTEM_Initialize();                                                        // Initialize the device
    INTERRUPT_GlobalInterruptEnable();                                          // Enable the Global Interrupts macro
    //INTERRUPT_GlobalInterruptDisable();                                       // Disable the Global Interrupts macro

    while (1)
    {
        i2c1_writeNBytesRegister(SLAVE_ADDRESS, SLAVE_EE_ADD, &transArray[0], TRANS_CNT);
        NOP();                                                                              
        i2c1_readDataBlock(SLAVE_ADDRESS, SLAVE_EE_ADD, &RXArray[0], PACKET_SIZE);
        NOP();
        __delay_ms(500);                                                        // Breakpoint for debugger to examine arrays in memory
    }
}
/**
 End of File
*/