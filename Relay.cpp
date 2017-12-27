#include <Arduino.h>
#include <Relay.h>
#include <Avail.h>

Relay::Relay(RELAY_SIZE size) {
	this->_size = size;
}

RELAY_SIZE *Relay::getSize(void) {
	return &this->_size;
}

Relay &Relay::setPin(uint8_t pin, uint8_t relay) {
	this->_pins[relay - 1] = pin;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	return *this;
}

uint8_t Relay::getRelayByPin(uint8_t pin) {
	for (uint8_t i = 0; i < *this->getSize(); i++) {
		if (this->_pins[i] == pin) { return i + 1; }
	}
	return 0;
}

uint8_t Relay::getPinByRelay(uint8_t relay) {
	return &this->_pins[relay - 1];
}

Relay &Relay::on(uint8_t relay) {
	this->_futurePinState[relay - 1] = RELAY_ON;
	return *this;
}

Relay &Relay::off(uint8_t relay) {
	this->_futurePinState[relay - 1] = RELAY_OFF;
	return *this;
}

Relay &Relay::toggle(uint8_t relay) {
	if (*this->getState(relay) == RELAY_OFF) {
		return this->on(relay);
	} else {
		return this->off(relay);
	}
}

Relay &Relay::commit(void) {
	for (uint8_t i = 0; i < *this->getSize(); i++) {
		RELAY_STATE &c = this->_currentPinState[i];
		RELAY_STATE &f = this->_futurePinState[i];
		uint32_t *l = &this->_lastToggle[i];

		if (c != f && Avail::millis(&this->_safety, l)) {
			c = f;
			*l = millis();
			digitalWrite(this->_pins[i], (c == RELAY_ON ? LOW : HIGH));
		}
	}

	return *this;
}

RELAY_STATE *Relay::getState(uint8_t relay) {
	return &this->_currentPinState[relay - 1];
}

Relay &Relay::setSafety(uint32_t safety) {
	this->_safety = max(safety, 250);
}