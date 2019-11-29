[![MCHP](https://cldup.com/U0qhLwBijF.png)](https://www.microchip.com)
## Objective:
The PIC18F26K42 microcontroller contains two independent I2C serial communications ports: I2C1 and I2C2. I2C1 is configured as an I2C Master, while I2C2 is configured as an I2C Slave. The I2C Master writes a block of data into a simulated EEPROM array, and then reads the data back and stores it in a new array. 

## Demo Configuration:
The Curiosity High Pin Count (HPC) Development Board (DM164136) is used as the test platform. Two jumper wires connect the two I2C bus lines; connect pin RC3 (SCL1) to pin RB1 (SCL2), and pin RC4 (SDA1) to pin RB2 (SDA2). No pull-up resistors are required; the dedicated I2C pins have been designed with stronger internal pull-up resistors that can be used instead of external resistors. 
This code example requires the use of the MPLABX IDE’s debugging feature. Using the debugger allows the user to halt the program and check the file registers to ensure accurate communication. A breakpoint has been added in the main while loop that will halt code execution after the Master has completed the transfer and reception of data. 
### Curiosity HPC with jumper wires connecting the two I2C ports: 
![](http://static.transim.com/img/42018/4d7ca3c9e42e43979ed382cda00d0746-qk1mm.jpg){width=auto height=auto align=center}










### Breakpoint set in Main:
![](http://static.transim.com/img/42018/3cbcf0a7c6c343bf90b265680318bb42-qzct8.png){width=auto height=auto align=center} 
## I2C Module Configuration:
The I2C modules can easily be configured using the Microchip Code Configurator (MCC) plug-in tool found in the MPLABX IDE. The I2C1 module is configured for Master mode, while I2C2 is configured as a slave. The Master is configured for a 100 kHz clock for this example. The I2C1 module uses the dedicated I2C pins RC3 and RC4, and I2C2 uses the dedicated RB1 and RB2 pins. These dedicated pins utilize special registers, RC3I2C, RC4I2C, RB1I2C, and RB2I2C, that are used to configure the input logic levels, internal pull-up configuration, and slew rate. For this example, the internal pull-ups are configured for the ‘10x current of standard weak pull-up’ level, which is strong enough to handle the slow bus speeds effectively. The pins must be configured as open-drain via the ODxCON registers, and set as outputs via the TRISx registers.
### MCC Configuration for I2C1:
![](https://static.transim.com/img/42018/a779c2b2dc164e1686392ecd199b928d-b8g5s.png){width=auto height=auto align=center} 
### MCC Configuration for I2C2:
![](https://static.transim.com/img/42018/559a4d9eb1b54389b09e5c0cca2692bd-151yz.png){width=auto height=auto align=center} 
## Running the Demo in MPLAB:
This demo must be run in debug mode in MPLAB. Once the project is open, simply press the ‘Debug Project’ button in the IDE’s toolbar. The debugger will execute code until the breakpoint is reached. Once the program has halted due to the breakpoint, press the ‘Window’ tab. Run your curser over the ‘PIC Memory Views’ tab, and click on the ‘File Registers’ selection. This will cause the File Registers window to appear. 
The File Registers window can be used to verify communication. The Master device’s ‘transArray[PACKET_SIZE]’, which contains the block of data that is transmitted to the Slave, is located beginning at address 0180, and ends at address 01FF. 
The Master’s transmitted data is received and stored in the Slave’s ‘EEPROM_Buffer[0x80]’ data array, which begins at address 0060, and ends at 00DF.
The data received back from the Slave is stored in the RXArray[PACKET_SIZE] data array, which begins at address 0100, and ends at address 017F.
To verify a complete and correct transfer, check the values between addresses 0060 and 00DF (for correct slave reception) and between addresses 0100 and 017F (for correct Master reception). The values in each register contained in each address range should match. For example, address 0060 and 0100 should both contain the value ‘A0’.
### Drop-down Menu Selection for the ‘File Registers’ Window:
![](https://static.transim.com/img/42018/5dc6586fdcdc4fc0856a0597c4386784-pkcmw.png){width=auto height=auto align=center} 

### File Registers Before Communication:
![](https://static.transim.com/img/42018/3d3e1b61839b4c79b8e3b8542f9d23ca-j9c5s.png){width=auto height=auto align=center} 
### File Registers at Breakpoint:
![](https://static.transim.com/img/42018/55c56e5076114c8887b66ee5dce12eba-3qblr.png){width=auto height=auto align=center} 



## Conclusion:
The demo provides an example of I2C communication in both Master mode and Slave mode. Please refer to the PIC18F26K42 datasheet for more information or specifications.
External Links:




