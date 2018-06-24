# Arduino Relay Library

A way to simplify controlling a relay module board.

Example:

```c++
#include <Relay.h>
    
#define relayOne 2 // the actual pin number
    
Relay relay(relayOne);
    
void setup()
{
    // prevent toggling more than once every 500 microseconds
    relay.setSafety(500);
}
    
void loop()
{
    // toggle every half second while not interrupting entire program
    relay.toggle();
}
```

#### RelayConfig.h
The safety machinsm can be disabled by setting RELAY_SAFETY to `false` in the aforementioned configuration file.  This will also use less memory for the compiled application.