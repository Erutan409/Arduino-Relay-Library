#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>

enum RELAY_SIZE {
    ONE_R       = 0x01
    ,TWO_R      = 0x02
    ,FOUR_R     = 0x04
    ,EIGHT_R    = 0x08
    ,SIXTEEN_R  = 0x10
};

enum RELAY_NUM {
    FIRST_R         = 0x02
    ,SECOND_R       = 0x04
    ,THIRD_R        = 0x08
    ,FOURTH_R       = 0x10
    ,FIFTH_R        = 0x20
    ,SIXTH_R        = 0x40
    ,SEVENTH_R      = 0x80
    ,EIGHTH_R       = 0x100
    ,NINTH_R        = 0x200
    ,TENTH_R        = 0x400
    ,ELEVENTH_R     = 0x800
    ,TWELFTH_R      = 0x1000
    ,THIRTEENTH_R   = 0x2000
    ,FOURTEENTH_R   = 0x4000
    ,FIFTEENTH_R    = 0x8000
    ,SIXTEENTH_R    = 0x10000
};

enum RELAY_STATE {
    ON_R       = 0
    ,OFF_R     = 1
};

class Relay {

    public:
        Relay(RELAY_SIZE size);
        bool initialize(void);
        RELAY_SIZE getSize(void);
        Relay &setPin(int pinNumber, RELAY_NUM relay);
        int *getPin(RELAY_NUM rela);
        Relay &on(RELAY_NUM relay);
        Relay &off(RELAY_NUM relay);
        void commit(void);
        RELAY_STATE *getState(RELAY_NUM relay);

    private:
        bool _initialized = false;
        RELAY_SIZE _size;
        int _pins[16];
        RELAY_STATE _currentPinState[16];
        RELAY_STATE _futuePinState[16];
        int _translateRelayNumber(RELAY_NUM *relay);
        Relay &_toggle(RELAY_NUM relay, RELAY_STATE state);

};

#endif