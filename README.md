# Serial Port Communication for Nodepp Applications

nodepp-serial is a powerful and easy-to-use library that brings robust serial port communication capabilities to your Nodepp applications. Leveraging Nodepp's asynchronous architecture, nodepp-serial allows you to interact with serial devices seamlessly, making it ideal for IoT, embedded systems, and hardware control projects developed with Nodepp.

## Key Features:
- **Asynchronous Operations:** Fully integrated with Nodepp's event loop for non-blocking serial port access.
- **Cross-Platform:** Designed to work across various operating systems supported by Nodepp.
- **Simple API:** An intuitive and Node.js-like API for opening, closing, reading from, and writing to serial ports.
- **Event-Driven:** Emits events for data reception, errors, and port status changes, simplifying event handling.

## Example
```cpp
#include <nodepp/nodepp.h>
#include <nodepp/serial.h>

using namespace nodepp;

void onMain(){

    auto x = serial::connect( "/dev/ttyUSB0", 9600 );

    x.onConnect([]( serial_t cli ){

        console::log( "connected" );

        cli.onData([]( string_t chunk ){
            console::log( chunk );
        });

        cli.write("hello World!");

    });

}
```

## Compilation
```bash
g++ -o main main.cpp -I ./include ; ./main
```