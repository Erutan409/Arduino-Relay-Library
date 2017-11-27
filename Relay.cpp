#include <Arduino.h>
#include <Relay.h>

Relay::Relay(RELAY_SIZE size) {
    this->_size = size;
}

// instructs the object that it's ready to do work,
// but first checks to make sure everything is
// properly configured
bool Relay::initialize(void) {

    for (int i = 0; i < this->getSize(); i++) {

        if (this->_pins[i] == 0) {
            return false;
        }

    }

    this->_initialized = true;
    this->commit();
    return this->_initialized;

}

RELAY_SIZE Relay::getSize(void) {
    return this->_size;
}

Relay &Relay::setPin(int pinNumber, RELAY_NUM relay) {

    // don't allow any pin setting if alread initialized
    if (this->_initialized || this->_translateRelayNumber(&relay) > this->getSize()) {goto done;}

    // ensure the pin mode is set for input
    pinMode(pinNumber,INPUT);
    //digitalWrite(pinNumber,HIGH);
    this->_pins[(this->_translateRelayNumber(&relay) - 1)] = pinNumber;
    // set default state for pin
    this->_futuePinState[(this->_translateRelayNumber(&relay) - 1)] = OFF_R;

    done:
    return *this;

}

int *Relay::getPin(RELAY_NUM relay) {
    return &this->_pins[(this->_translateRelayNumber(&relay) - 1)];
}

Relay &Relay::on(RELAY_NUM relay) {
    return this->_toggle(relay, ON_R);
}

Relay &Relay::off(RELAY_NUM relay) {
    return this->_toggle(relay, OFF_R);
}

RELAY_STATE *Relay::getState(RELAY_NUM relay) {
    return &this->_currentPinState[(this->_translateRelayNumber(&relay) - 1)];
}

Relay &Relay::_toggle(RELAY_NUM relay, RELAY_STATE state) {

    if (!this->_initialized || this->_translateRelayNumber(&relay) > this->getSize()) {goto done;}

    this->_futuePinState[(this->_translateRelayNumber(&relay) - 1)] = state;

    done:
    return *this;

}

void Relay::commit(void) {

    if (!this->_initialized) {goto done;}

    for (int i = 0; i < this->getSize(); i++) {

        RELAY_STATE &c = this->_currentPinState[i];
        RELAY_STATE &f = this->_futuePinState[i];

        if (c != f) {

            c = f;
            digitalWrite(this->_pins[i],(c == ON_R? LOW : HIGH));

        }

    }

    done:
    return;

}

unsigned short int Relay::_translateRelayNumber(RELAY_NUM *relay) {

    switch (*relay) {

        case FIRST_R: return 1;
        case SECOND_R: return 2;
        case THIRD_R: return 3;
        case FOURTH_R: return 4;
        case FIFTH_R: return 5;
        case SIXTH_R: return 6;
        case SEVENTH_R: return 7;
        case EIGHTH_R: return 8;
        case NINTH_R: return 9;
        case TENTH_R: return 10;
        case ELEVENTH_R: return 11;
        case TWELFTH_R: return 12;
        case THIRTEENTH_R: return 13;
        case FOURTEENTH_R: return 14;
        case FIFTEENTH_R: return 15;
        case SIXTEENTH_R: return 16;

    }

}