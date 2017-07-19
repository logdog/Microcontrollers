
#include "Arduino.h"
#include "LTD_SRL.h"

// private methods

void LTD_SRL::_clock() {
	_setPin(SHCLK, HIGH);
	// delay?
	_setPin(SHCLK, LOW);
}

bool LTD_SRL::_pinMode(int pin) {
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
	values.insert(values.begin(), b);
	values.pop_back();

	_setWrite();
	for(int i = 0; i < 8; i++) {
		if(MSB) {
			// MSB first (decimal 1 -> 1000 0000)
			_setPin(SER, bool(abs(  (b / 128) % 2 )));
			b <<= 1;
		} else {
			// LSB first (decimal 1 -> 0000 0001)
			_setPin(SER, bool(abs(b % 2)));
			b >>= 1;
		}
		_clock();
	}
	_setRead();
}

void LTD_SRL::writeBytes(char *b) {
	// update values in reverse order
	for(int i = numRegisters-1; i >= 0; i--) {
		values.insert(values.begin(), b[i]);
		values.pop_back();
	}

	_setWrite();
	for(int i = numRegisters-1; i >= 0; i--) {
		char v = b[i];
		for(int j = 0; j < 8; j++) {
			if(MSB) {
				// MSB first (decimal 1 -> 1000 0000)
				_setPin(SER, bool(abs(  (v / 128) % 2 )));
				v <<= 1;
			} else {
				// LSB first (decimal 1 -> 0000 0001)
				_setPin(SER, bool(abs(v % 2)));
				v >>= 1;
			}
			_clock();
		}
	}
	_setRead();
}

char LTD_SRL::getValue(int regID) {
	return values.at(regID);
}

char* LTD_SRL::getValues() {
	char cval[values.size()];
	for(int i = 0; i < numRegisters; i++) {
		cval[i] = values.at(i);
	}
	return &cval;
}

// constructor
LTD_SRL::LTD_SRL(int SER, int OE, int RCLK, int SHCLK, int SRCLR, int numRegisters, bool MSB, bool LTR) {
	this->SER = SER;
	this->OE = OE; // Not Implemented
	this->RCLK = RCLK; // "latch"
	this->SHCLK = SHCLK;
	this->SRCLR = SRCLR;

	this->numRegisters = numRegisters;
	this->MSB = MSB;
	this->LTR = LTR; // Not implemented

	_pinMode(SER, OUTPUT);
	_pinMode(OE, OUTPUT);
	_pinMode(RCLK, OUTPUT);
	_pinMode(SHCLK, OUTPUT);
	_pinMode(SRCLR, OUTPUT);

	for(int i = 0; i < numRegisters; i++) {
		this->values.push(0); // all registers start with the value of zero
	}
}

