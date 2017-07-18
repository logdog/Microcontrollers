# Shift Register Library

I decided if I'm going to rewrite all my code, might as well do it in cpp instead of whatever language Arduino calls itself. We want maximum efficiency for such an inefficient process such as bit banging.

I am basing my library off of the SN74HC595 shift register from Texas Instruments. The data sheet is avaliable [here](http://www.ti.com/lit/ds/symlink/sn74hc595.pdf).

# Architecture
## Shift Register Class
Represents a real-life 74HC595 shift register. The methods in this class are to be used exclusively by the Handler class. There are no public methods for this reason. Can be put in two modes: 
1. LSB (Least significant bit first)
2. MSB (Most significant bit first)

This class works by handling the five input pins:

1. ```SER``` The input value into the SR

2. ```OE BAR``` Output enabled. High = High Impedience Output (off)

3. ```RCLK``` Set Low before data is clocked, High after

4. ```SHCLK``` Input for clocking bits. Bits are clocked on the rising edge

5. ```SRCLR BAR``` Clear register. Low = clear

### Methods
#### ```LTD_SR LTD_SR(int SER, int OE, int RCLK, int SHCLK, int SRCLR, bool MSB)```
Constructor. Setting any of the pins to zero will result in the pin not being used. Also specifies the mode.

#### ```void clear()```
Clear the shift register

#### ```void clock()```
Pulse SRCLK High and then Low

#### ```void setBit(bool high)```
Set the SER pin High or Low

#### ```void setOutput(bool on)```
Set output on or off
on = Low, off = High

#### ```void setRead()```
Put register in read mode: RCLK HIGH

#### ```void writeByte(byte b)```
Write to the shift register

#### ```void setWrite()```
Put register in write mode: RCLK LOW

## Daisy Chained Shift Register Handler Class
Holds an array (vector subject to change) of LTD_SRs and manages all operations of the Shift Registers themselves. This should be created even if you only have one shift register, as all of the public methods are located in this class.

### Public Methods
#### ```LTD_DCSR LTD_DCSR(int SER, int OE, int RCLK, int SHCLK, int SRCLR, bool MSB, int numRegisters)```
Constructor. Setting any of the pins to zero will result in the pin not being used. Also specifies the mode and the number of registers.

#### ```void clear()```
Clear all registers

#### ```void setOutput(bool on)```
Set the SER pin High or Low

#### ```void writeByte(byte b)```
Write to the shift register
