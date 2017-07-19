# Shift Register Library

I decided if I'm going to rewrite all my code, might as well do it in cpp instead of whatever language Arduino calls itself. We want maximum efficiency for such an inefficient process such as bit banging.

I am basing my library off of the SN74HC595 shift register from Texas Instruments. The data sheet is avaliable [here](http://www.ti.com/lit/ds/symlink/sn74hc595.pdf).

# Architecture

## Shift Register Handler Library Class
Represent real-life 74HC595 shift registers daisy-chained together. The public functions in this class will control 
1. LSB (Least significant bit first)
2. MSB (Most significant bit first)

This class works by handling the five input pins:

1. ```SER``` The input value into the Shift Register

2. ```OE BAR``` Output enabled. High = High Impedience Output (off)

3. ```RCLK``` Set Low before data is clocked, High after. (Latch pin)

4. ```SHCLK``` Input for clocking bits. Bits are clocked on the rising edge

5. ```SRCLR BAR``` Clear register. Low = clear


### Public Methods
#### ```LTD_SRL(int SER, int OE, int RCLK, int SHCLK, int SRCLR, int numRegisters, bool MSB, bool LTR);```
Constructor. Setting any of the pins to zero will result in the pin not being used. Also specifies the mode and the number of registers. If inputs into the shift register are tied together, e.g. RCLK and SHCLK, simply pass the same pin number into the constructor. 

#### ```void clear()```
Clear all registers

#### ```bool setOutput(bool on)```
Set OE on/off

#### ```void writeByte(char b)```
Write a byte to the first register. Pushes first register to second, second to third, etc.

#### ```void writeBytes(char *b)```
Fill all registers with these values. Prerequisite: the array we wish to fill values with must be the same size as the number of registers.

#### ```char getValue(int regID)```
Return the value stored in the register. Note: The class keeps track of the value stored, and does not necessarily be the actual value in the register if the register is for any reason disfunctional. Take with a grain of salt. Not a debugging tool.

#### ```char* getValues()```
Return the values stored in the registers. See getValue for details.

### Private Methods
#### ```void clock()```
Sets SHCLK High and then Low

#### ```bool _pinMode(int pin)```
Setup method to set the pinModes if they are not set to zero

#### ```bool _setPin(int pin, bool high)```
Set the pin to low or high, if pin != 0

#### ```void _setRead()```
Release latch pin to see updated contents in shift register

#### ```void _setWrite()```
Pull latch pin to see block outputs from flickering during writing to shift register
