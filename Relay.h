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
        Relay &setPin(unsigned int pin, unsigned int relay);
        int getRelayByPin(unsigned int pin);
		int getPinByRelay(unsigned int relay);
        Relay &on(unsigned int relay);
        Relay &off(unsigned int relay);
        void commit(void);
        RELAY_STATE *getState(unsigned int relay);

    private:
        RELAY_SIZE _size;
        int _pins[16] = {0};
		RELAY_STATE _currentPinState[16] = {RELAY_OFF};
		RELAY_STATE _futurePinState[16] = {RELAY_OFF};

};

#endif