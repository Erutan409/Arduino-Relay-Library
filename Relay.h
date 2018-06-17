#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>

enum RELAY_STATE {
	RELAY_ON   = 0x01,
	RELAY_OFF = 0x00
};

class Relay {

	public:
		Relay(uint8_t pin);
		Relay &on(void);
		Relay &off(void);
		Relay &toggle(void);
		RELAY_STATE *getState(void);
		Relay &setSafety(uint32_t safety);

	private:
		uint8_t _pin;
		RELAY_STATE _currentState = RELAY_OFF;
		uint32_t _safety = 250;
		uint32_t _lastToggle = 0;

};

#endif