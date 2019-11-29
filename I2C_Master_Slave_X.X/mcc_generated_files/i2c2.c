/**
  I2C2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c2.c

  @Summary
    This is the generated header file for the I2C2 driver using 
    PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for I2C2.
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
 This file provides some basic functions for common operations on the i2c API
 */
#include <xc.h>
#include <stdbool.h>
#include "i2c2.h"
#include "mcc.h"


uint8_t EEPROM_Buffer[0x80] =
{
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
    0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
    0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
    0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
    0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
    0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
    0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f
};
uint8_t dataAddressByte = 0;
volatile uint8_t eepromAddress = 0;


void I2C2_Initialize(void)
{
    I2C2ADR0 = 0x40;                                                            // Slave address 
    I2C2ADR1 = 0x40;
    I2C2ADR2 = 0x40;
    I2C2ADR3 = 0x40;
    I2C2CON1 = 0x00;                                                            // CSD Clock Stretching enabled; ACKDT Acknowledge; ACKCNT Not Acknowledge;  
    I2C2CON2 = 0x00;                                                            // ABD enabled; SDAHT 300 ns; BFRET 8 I2C Clocks; FME disabled;
    I2C2CLK = 0x00;                                                             // Slave doesn't use I2CCLK
    I2C2CNT = 0x00;
    I2C2CON0 = 0x00;                                                            // CSTR Enable clocking; S Cleared by hardware after Start; MODE four 7-bit address; 
   
    PIR5bits.I2C2RXIF = 0;
    PIR5bits.I2C2TXIF = 0;
    PIR6bits.I2C2IF = 0;
    I2C2PIRbits.PCIF = 0;
    I2C2PIRbits.ADRIF = 0;
    
    PIE5bits.I2C2RXIE = 1;
    PIE5bits.I2C2TXIE = 1;
    PIE6bits.I2C2IE = 1;
    I2C2PIEbits.PCIE = 1;
    I2C2PIEbits.ADRIE = 1;
    
    I2C2CON0bits.EN = 1;   
}

void I2C2_ISR(void)
{
	if((PIR6bits.I2C2IF == 1) || (PIR5bits.I2C2RXIF == 1) || (PIR5bits.I2C2TXIF == 1))
	{
		if(I2C2STAT0bits.SMA == 1)
		{
			if(I2C2STAT0bits.R == 1)
			{
				if((I2C2PIRbits.ADRIF == 1) && (I2C2STAT0bits.D == 0))
				{
                    I2C2CNT = sizeof(EEPROM_Buffer);
                    I2C2PIRbits.ADRIF = 0;
                    I2C2PIRbits.SCIF = 0;
                    I2C2CON0bits.CSTR = 0;
                    if(I2C2STAT1bits.TXBE == 1)
                    {
                        I2C2TXB = EEPROM_Buffer[eepromAddress++];
                    }	
				}
				if((PIR5bits.I2C2TXIF == 1) && (I2C2STAT0bits.D == 1))
				{    
                    if(I2C2CNT)
					{
                        if(eepromAddress < sizeof(EEPROM_Buffer))
                        {
                            I2C2TXB = EEPROM_Buffer[eepromAddress++];
                        }
                        else
                        {
                            eepromAddress = 0;
                            I2C2TXB = EEPROM_Buffer[eepromAddress++];
                        }	
					}
					else
					{
						eepromAddress = 0;
					}
					I2C2CON0bits.CSTR = 0;
				}
			}
			if(I2C2STAT0bits.R == 0)
			{
				if((I2C2PIRbits.ADRIF == 1) && (I2C2STAT0bits.D == 0))
				{
					I2C2PIRbits.ADRIF = 0;
                    I2C2PIRbits.SCIF = 0;
                    I2C2PIRbits.WRIF = 0;
                    I2C2STAT1bits.CLRBF = 1;
					I2C2CON0bits.CSTR = 0;
				}	
				if((PIR5bits.I2C2RXIF == 1) && (I2C2STAT0bits.D == 1))
				{
					if(dataAddressByte == 0)
					{
						eepromAddress = I2C2RXB;
                        I2C2PIRbits.WRIF = 0;
						dataAddressByte = 1;
					}
					else
					{
						if(eepromAddress <= sizeof(EEPROM_Buffer))
						{
                            while(I2C2STAT1bits.RXBF == 0);
							EEPROM_Buffer[eepromAddress++] = I2C2RXB;
                            I2C2PIRbits.WRIF = 0;
						}
						else
						{
							eepromAddress = 0;
                            EEPROM_Buffer[eepromAddress++] = I2C2RXB;
                            I2C2PIRbits.WRIF = 0;
						}
					}
					I2C2CON0bits.CSTR = 0;				
				}
			}
		}
		else
		{
			if(I2C2PIRbits.PCIF)
            {
                I2C2PIRbits.PCIF = 0;
                I2C2PIRbits.SCIF = 0;
                I2C2PIRbits.CNTIF = 0;
                I2C2PIRbits.WRIF = 0;
                I2C2STAT1bits.CLRBF = 1;
                I2C2CNT = 0;
                dataAddressByte = 0;
                eepromAddress = 0;
            }	
		}	
	}
	if(PIR6bits.I2C2EIF == 1)
	{
		if(I2C2ERRbits.NACKIF)
        {
            I2C2ERRbits.NACKIF=0;
            I2C2STAT1bits.CLRBF=1;
            dataAddressByte = 0;
            eepromAddress = 0;
        }	
	}	
}


