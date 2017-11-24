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

    // ensure the pin mode is set for output
    pinMode(pinNumber,OUTPUT);
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

int Relay::_translateRelayNumber(RELAY_NUM *relay) {

    int num;

    switch (*relay) {

        case FIRST_R: num = 1; break;
        case SECOND_R: num = 2; break;
        case THIRD_R: num = 3; break;
        case FOURTH_R: num = 4; break;
        case FIFTH_R: num = 5; break;
        case SIXTH_R: num = 6; break;
        case SEVENTH_R: num = 7; break;
        case EIGHTH_R: num = 8; break;
        case NINTH_R: num = 9; break;
        case TENTH_R: num = 10; break;
        case ELEVENTH_R: num = 11; break;
        case TWELFTH_R: num = 12; break;
        case THIRTEENTH_R: num = 13; break;
        case FOURTEENTH_R: num = 14; break;
        case FIFTEENTH_R: num = 15; break;
        case SIXTEENTH_R: num = 16; break;

    }

    return num;

}