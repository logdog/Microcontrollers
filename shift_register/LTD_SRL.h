/*
Shift Register Library
Author: Logan Dihel
Date: July 19, 2017

Library is an interface in which Arduino (and other microcontrollers)
can talk to the daisy-chained shift registers with easy-to-use methods.

See README.md for details on the class itself.
*/

#ifndef LTD_SRL_H
#define LTD_SRL_H

// #include "Arduino.h"
#include <vector>

class LTD_SRL {
private:
	int SER, OE, RCLK, SHCLK, SRCLR, numRegisters;
	bool MSB, LTR;
	std::vector<char> values;

	void _clock();
	bool _pinMode(int pin, bool output);
	bool _setPin(int pin, bool high);
	void _setRead();
	void _setWrite();
	void _writeByte(char value);

public:
	LTD_SRL(int SER, int OE, int RCLK, int SHCLK, int SRCLR, int numRegisters, bool MSB, bool LTR);

	void clear();
	bool setOutput(bool on);

	void writeByte(char b);
	void writeBytes(char *b);

	char getValue(int regID);
	char* getValues();
};
#endif // LTD_SRL_H
