#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include "RelayConfig.h"

#if RELAY_SAFETY == true
#include <Avail.h>
#endif // RELAY_SAFETY == true


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

#if RELAY_SAFETY == true
		Relay &setSafety(uint32_t safety);
#endif // RELAY_SAFETY == true
		
	private:
		uint8_t _pin;
		RELAY_STATE _currentState = RELAY_OFF;
#if RELAY_SAFETY == true
		uint32_t _lastToggle = 0;
		uint32_t _safety = 250;
#endif // RELAY_SAFETY == true

};

#endif