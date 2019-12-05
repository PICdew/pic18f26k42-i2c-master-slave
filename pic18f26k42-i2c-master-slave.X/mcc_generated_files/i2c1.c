/**
  I2C1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c1.c

  @Summary
    This is the generated header file for the I2C1 driver using 
    PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for I2C1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC18F26K42
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.10	
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
/*
 This file provides some basic blocking helper functions for common operations on the i2c API
 */
#include <xc.h>
#include <stdbool.h>
#include "i2c1.h"
#include "mcc.h"
//static i2c_error lastError = I2C1_GOOD;

void I2C1_Initialize(void)
{
    I2C1CON1 = 0x80;                                                            // CSD Clock Stretching enabled; ACKDT ACK; ACKCNT NACK; 
    I2C1CON2 = 0x00;                                                            // ABD enabled; SDAHT 300 ns; BFRET 8 I2C Clocks; FME disabled; 
    I2C1CLK = 0x03;                                                             // CLK MFINTOSC; 
    I2C1CON0 = 0x04;                                                            // CSTR Enable clocking; S Cleared by hardware after Start; MODE 7-bit address;
    I2C1PIR = 0;                                                                // Clear all the error flags
    I2C1ERR = 0;
    I2C1CON0bits.EN = 1;
}

static inline void wait4Stop(void)
{
    while(!I2C1PIRbits.PCIF);                                                   // Wait for Stop condition to be recognized
    
    I2C1PIRbits.PCIF = 0;                                                       // Clear Stop condition IF                                        
    I2C1PIRbits.SCIF = 0;                                                       // Clear Start condition IF
    I2C1STAT1bits.CLRBF = 1;                                                    // Ensure all data is removed from buffers
}

void i2c1_readDataBlock(uint8_t address, uint8_t reg, char *data, uint8_t len)
{
    I2C1ADB1 = (uint8_t)(address << 1);                                         // Load slave address and shift
    I2C1TXB = reg;                                                              // Load slave starting register address 
    I2C1CNT = 1;                                                                // Load count
    I2C1CON0bits.RSEN = 1;                                                      // Set RSEN for master read
    I2C1CON0bits.S = 1;                                                         // Set Start to get things going
    while(!I2C1CON0bits.MDR);                                                   // Wait until master is ready to receive data
    
    address = (uint8_t)(address << 1);
    I2C1ADB1 = (uint8_t)(address | 0x01);                                       // Load address with Read enabled
    I2C1CNT = len;                                                              // Load length of expected packet in bytes
    I2C1CON0bits.S = 1;                                                         // Set Start to begin Restart condition
    I2C1CON0bits.RSEN = 0;                                                      // Clear RSEN 
    while(I2C1CNT)                                                              // While there is a count
    {
        while(!I2C1STAT1bits.RXBF);                                             // Wait until buffer receives data
        *data++ = I2C1RXB;                                                      // Transfer data into array, hardware decrements count
    }
    wait4Stop();                                                                // Wait for hardware to issue a Stop
}

void i2c1_writeNBytesRegister(uint8_t address, uint8_t reg, void* data, uint8_t len)
{
    uint8_t *dataPointer = data;

    I2C1ADB1 = (uint8_t)(address << 1);                                         // Load address with write = 0
    I2C1TXB = reg;                                                              // Load beginning slave register address to write
    I2C1CNT = len;                                                              // Load with size of array to write
    I2C1CON0bits.S = 1;                                                         // Set Start to get things going
    while(I2C1CNT)                                                              // While count is true
    {
        while(!I2C1STAT1bits.TXBE);                                             // Wait until buffer is empty before loading
        I2C1TXB = *dataPointer++;                                               // Load next byte to transmit, hardware decrements count
    }
    wait4Stop();                                                                // Wait for hardware to issue Stop                                                               
}




