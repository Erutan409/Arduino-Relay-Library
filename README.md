# Arduino Relay Library

A way to simplify controlling a relay module board.

Example:

```c++
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
```