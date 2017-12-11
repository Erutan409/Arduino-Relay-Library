# Arduino-Relay-Library

A way to simplify controlling a relay module board.

Example:

    Relay relay(FOUR_R); // create instance of relay for a 4 relay module component
    
    // configure instance
    relay.setPin(8,FIRST_R)
    .setPin(9,SECOND_R)
    .setPin(10,THIRD_R)
    .setPin(11,FOURTH_R)
    .initialize();
    
    // do work
    relay.on(FIRST_R)
    .on(THIRD_R)
    .commit();
    
    // turns relays 1 & 3 to on
    
    relay.off(FIRST_R)
    .commit();
    
    // turns off relay 1

#include <Relay.h>

Relay relay(FOUR_RELAY);

#define relayOne 2 // the actual pin number

void setup()
{
	relay.setPin(relayOne, 1);
}

void loop()
{
	delay(3000);

	if (*relay.getState(relay.getRelayByPin(relayOne)) == RELAY_ON) {
		relay.off(relay.getRelayByPin(relayOne));
	} else {
		relay.on(relay.getRelayByPin(relayOne));
	}

	relay.commit();
}
