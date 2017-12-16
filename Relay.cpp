#include <Arduino.h>
#include <Relay.h>

#ifdef RelaySafety

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

	void Relay::commit(void) {
		for (unsigned short int i = 0; i < *this->getSize(); i++) {
			RELAY_STATE &c = this->_currentPinState[i];
			RELAY_STATE &f = this->_futurePinState[i];
			unsigned long &l = this->_lastToggle[i];

			if (c != f && this->_check(l)) {
				c = f;
				digitalWrite(this->_pins[i], (c == RELAY_ON ? LOW : HIGH));
			}
		}
	}

	RELAY_STATE *Relay::getState(unsigned int relay) {
		return &this->_currentPinState[relay - 1];
	}

	unsigned long Relay::_getSafety(void) {
		static unsigned short safety = nullptr;
		if (safety == nullptr) { safety = max(atoi(RelaySafety), 166); /* in milliseconds */ }

		return safety;
	}

	bool Relay::_check(unsigned long &lastToggle) {
		unsigned long millis = millis();
		unsigned long diff = millis - lastToggle;
		bool rollover = diff > millis;

		if (rollover) { // rollover
			lastToggle = 4294967295 - lastToggle;
			return false;
		} else if (diff == 0 || diff > this->_getSafety()) {
			return true;
		} else {
			return false;
		}
	}

#else

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

	void Relay::commit(void) {
		for (unsigned short int i = 0; i < *this->getSize(); i++) {
			RELAY_STATE &c = this->_currentPinState[i];
			RELAY_STATE &f = this->_futurePinState[i];

			if (c != f) {
				c = f;
				digitalWrite(this->_pins[i], (c == RELAY_ON ? LOW : HIGH));
			}
		}
	}

	RELAY_STATE *Relay::getState(unsigned int relay) {
		return &this->_currentPinState[relay - 1];
	}

#endif // RelaySafety