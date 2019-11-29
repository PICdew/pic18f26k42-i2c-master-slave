/**
  I2C1 Generated Driver API Header File
  
  @Company
    Microchip Technology Inc.

  @File Name
    i2c1.h
	
  @Summary
    This is the generated header file for the I2C1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

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
#ifndef _I2C1_H
#define _I2C1_H

#include <stdint.h>
/**
 Section: Data Type Definitions
*/

/**
  @Summary
    Initializes the I2C1

  @Description
    This routine initializes the I2C1.
    This routine must be called before any other i2c1 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment

  
  @Example
    <code>
    I2C1_Initialize();
    </code>
*/
void I2C1_Initialize(void);

 /**
  @Summary
    Read n bytes of data block from a register/address of an I2C slave having 7 bit Address.

  @Description
    This routine reads n bytes of data from a register/address of an I2C slave.

  @Preconditions
  None

  @Param
    address - The address of the i2c slave to be accessed
 
  @Param
    *data - A pointer to the memory location where received data will be stored 

  @Param
    len - The length of the data block to be read
  
  @Returns
    None
*/
void i2c1_readDataBlock(uint8_t address, uint8_t reg, char *data, uint8_t len);
void i2c1_writeNBytesRegister(uint8_t address, uint8_t reg, void* data, uint8_t len);

#endif	/* _I2C1_H */

