#include <Relay.h>
#include "RelayConfig.h"

#if RELAY_SAFETY == true
#include <Avail.h>
#endif // RELAY_SAFETY == true


Relay::Relay(uint8_t pin) {
	this->_pin = pin;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
}

Relay &Relay::on(void) {
	RELAY_STATE &state = this->_currentState;

#if RELAY_SAFETY == true
	uint32_t *safety = &this->_safety;
	uint32_t *last = &this->_lastToggle;

	if (state != RELAY_ON && Avail::millis(safety, last)) {
		*last = millis();
		digitalWrite(this->_pin, LOW);
		state = RELAY_ON;
	}
#else
	if (state != RELAY_ON) {
		digitalWrite(this->_pin, LOW);
		state = RELAY_ON;
	}
#endif // RELAY_SAFETY

	return *this;
}

Relay &Relay::off(void) {
	RELAY_STATE &state = this->_currentState;

#if RELAY_SAFETY == true
	uint32_t *safety = &this->_safety;
	uint32_t *last = &this->_lastToggle;

	if (state != RELAY_OFF && Avail::millis(safety, last)) {
		*last = millis();
		digitalWrite(this->_pin, HIGH);
		state = RELAY_OFF;
	}
#else
	if (state != RELAY_OFF) {
		digitalWrite(this->_pin, HIGH);
		state = RELAY_OFF;
	}
#endif // RELAY_SAFETY

	return *this;
}

Relay &Relay::toggle(void) {
	if (*this->getState() == RELAY_OFF) {
		return this->on();
	} else {
		return this->off();
	}
}

RELAY_STATE *Relay::getState() {
	return &this->_currentState;
}

#if RELAY_SAFETY == true
Relay &Relay::setSafety(uint32_t safety) {
	this->_safety = max(safety, 250);

	return *this;
}
#endif // RELAY_SAFETY == true