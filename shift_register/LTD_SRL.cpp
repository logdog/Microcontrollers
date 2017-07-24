
#include "Arduino.h"
#include "LTD_SRL.h"
#include <cmath>
#include <stdlib.h>
// #define LOW false
// #define HIGH true
// #define OUTPUT true

// private methods

void LTD_SRL::_clock() {
	_setPin(SHCLK, HIGH);
	// delay?
	_setPin(SHCLK, LOW);
}

bool LTD_SRL::_pinMode(int pin, bool output) {
	if (pin == 0) return false;
	pinMode(pin, OUTPUT);
	return true;
}


bool LTD_SRL::_setPin(int pin, bool high) {
	if (pin == 0)return false;
	if (high) digitalWrite(pin, HIGH);
	else digitalWrite(pin, LOW);
	return true;
}

void LTD_SRL::_setRead() {
	_setPin(RCLK, LOW);
}

void LTD_SRL::_setWrite() {
	_setPin(RCLK, HIGH);
}

void LTD_SRL::_writeByte(char value) {
	for(int i = 0; i < 8; i++) {
		if(MSB) {
			// MSB first (decimal 1 -> 0000 0001)
			_setPin(SER, bool(std::abs(float(value % 2))));
			value >>= 1;
			
		} else {
			// LSB first (decimal 1 -> 1000 0000)
			_setPin(SER, bool(std::abs(float((value / 128) % 2))));
			value <<= 1;
		}
		_clock();
	}
}

// public methods
void LTD_SRL::clear() {
	_setPin(SRCLR, LOW);
	_setWrite();
	// delay?
	_setRead();
	_setPin(SRCLR, HIGH);
}

bool LTD_SRL::setOutput(bool on) {
	if (on) {
		_setPin(OE, LOW);
		return true; // on
	} else {
		_setPin(OE, HIGH);
		return false; // off
	}
}

void LTD_SRL::writeByte(char b) {
	// update vector
	if(LTR) {
		values.insert(values.begin(), b);
		values.pop_back();
	} else {
		values.push_back(b);
		values.erase(values.begin());
	}

	_setWrite();
	_writeByte(b); // not in if statement because this will be executed every time
	_setRead();
	
}

void LTD_SRL::writeBytes(char *b) {
	// update values in reverse order if LTR true
	_setWrite();
	if (LTR) {
		for(int i = numRegisters-1; i >= 0; i--) {
			values.insert(values.begin(), b[i]);
			values.pop_back();
			_writeByte(b[i]);
		}
	} else {
		for(int i = 0; i < numRegisters; i++) {
			values.push_back(b[i]);
			values.erase(values.begin());
			_writeByte(b[i]);
		}
	}
	_setRead();
}

char LTD_SRL::getValue(int regID) {
	return values.at(regID);
}

char* LTD_SRL::getValues() {
	char* cval = (char*) malloc(numRegisters * sizeof(char)); //use heap, not stack
	for(int i = 0; i < numRegisters; i++) {
		cval[i] = char(values.at(i));
	}
	return cval;
}

// constructor
LTD_SRL::LTD_SRL(int SER, int OE, int RCLK, int SHCLK, int SRCLR, int numRegisters, bool MSB, bool LTR) {
	this->SER = SER;     // serial data in
	this->OE = OE;     	 // LOW = output enabled
	this->RCLK = RCLK; 	 // "latch" pin (register clock)
	this->SHCLK = SHCLK; // flip flop clock
	this->SRCLR = SRCLR; // LOW = clear

	this->numRegisters = numRegisters;
	this->MSB = MSB; // Should be true by default
	this->LTR = LTR; // Should be true by default

	_pinMode(SER, OUTPUT);
	_pinMode(OE, OUTPUT);
	_pinMode(RCLK, OUTPUT);
	_pinMode(SHCLK, OUTPUT);
	_pinMode(SRCLR, OUTPUT);

	for(int i = 0; i < numRegisters; i++) {
		this->values.push_back(0); // all registers start with the value of zero
	}
}
