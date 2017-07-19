
#include "Arduino.h"
#include "LTD_SRL.h"

// private methods

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
	return;
}

void LTD_SRL::_setWrite() {
	return;
}

// public methods
void LTD_SRL::clear() {
	return;
}

bool LTD_SRL::setOutput(bool on) {
	return true;
}

void LTD_SRL::pushByte(char b) { // "writeByte"
	return;
}

void LTD_SRL::pushBytes(char *b) {
	return;
}

char LTD_SRL::getValue(int regID) {
	return values.at(regID);
}

char* LTD_SRL::getValues() {
	char cval[values.size()];
	for(int i = 0; i < values.size(); i++) {
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
	this->MSB = MSB; // Not Implemented
	this->LTR = LTR; // Not Implemented

	_pinMode(SER, OUTPUT);
	_pinMode(OE, OUTPUT);
	_pinMode(RCLK, OUTPUT);
	_pinMode(SHCLK, OUTPUT);
	_pinMode(SRCLR, OUTPUT);

	for(int i = 0; i < numRegisters; i++) {
		this->values.push(0); // all registers start with the value of zero
	}
}

