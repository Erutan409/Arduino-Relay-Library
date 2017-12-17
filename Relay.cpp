#include <Arduino.h>
#include <Relay.h>
#include <Avail.h>

Relay::Relay(RELAY_SIZE size) {
	this->_size = size;
}

RELAY_SIZE *Relay::getSize(void) {
	return &this->_size;
}

Relay &Relay::setPin(unsigned int pin, unsigned int relay) {
	this->_pins[relay - 1] = pin;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	return *this;
}

int Relay::getRelayByPin(unsigned int pin) {
	for (unsigned short int i = 0; i < *this->getSize(); i++) {
		if (this->_pins[i] == pin) { return i + 1; }
	}
	return 0;
}

int Relay::getPinByRelay(unsigned int relay) {
	return &this->_pins[relay - 1];
}

Relay &Relay::on(unsigned int relay) {
	this->_futurePinState[relay - 1] = RELAY_ON;
	return *this;
}

Relay &Relay::off(unsigned int relay) {
	this->_futurePinState[relay - 1] = RELAY_OFF;
	return *this;
}

Relay &Relay::toggle(unsigned int relay) {
	if (*this->getState(relay) == RELAY_OFF) {
		return this->on(relay);
	} else {
		return this->off(relay);
	}
}

Relay &Relay::commit(void) {
	for (unsigned short int i = 0; i < *this->getSize(); i++) {
		RELAY_STATE &c = this->_currentPinState[i];
		RELAY_STATE &f = this->_futurePinState[i];
		unsigned long *l = &this->_lastToggle[i];

		if (c != f && avail(&this->_safety, l) == true) {
			c = f;
			*l = millis();
			digitalWrite(this->_pins[i], (c == RELAY_ON ? LOW : HIGH));
		}
	}

	return *this;
}

RELAY_STATE *Relay::getState(unsigned int relay) {
	return &this->_currentPinState[relay - 1];
}

Relay &Relay::setSafety(unsigned long safety) {
	this->_safety = max(safety, 250);
}