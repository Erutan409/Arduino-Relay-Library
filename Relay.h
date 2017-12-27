#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>

enum RELAY_SIZE {
    ONE_RELAY      = 0x01
    ,TWO_RELAY     = 0x02
    ,FOUR_RELAY    = 0x04
    ,EIGHT_RELAY   = 0x08
    ,SIXTEEN_RELAY = 0x10
};

enum RELAY_STATE {
	RELAY_ON   = 0x01
    ,RELAY_OFF = 0x00
};

class Relay {

	public:
		Relay(RELAY_SIZE size);
		RELAY_SIZE *getSize(void);
		Relay &setPin(uint8_t pin, uint8_t relay);
		uint8_t getRelayByPin(uint8_t pin);
		uint8_t getPinByRelay(uint8_t relay);
		Relay &on(uint8_t relay);
		Relay &off(uint8_t relay);
		Relay &toggle(uint8_t relay);
		Relay &commit(void);
		RELAY_STATE *getState(uint8_t relay);
		Relay &setSafety(uint32_t safety);

	private:
		RELAY_SIZE _size;
		uint8_t _pins[16] = { 0 };
		RELAY_STATE _currentPinState[16] = { RELAY_OFF };
		RELAY_STATE _futurePinState[16] = { RELAY_OFF };
		uint32_t _lastToggle[16] = { 0 };
		uint32_t _safety = 250;

};

#endif