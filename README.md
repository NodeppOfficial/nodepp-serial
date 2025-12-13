# Serial Port Communication for Nodepp Applications

nodepp-serial is a powerful and easy-to-use library that brings robust serial port communication capabilities to your Nodepp applications. Leveraging Nodepp's asynchronous architecture, nodepp-serial allows you to interact with serial devices seamlessly, making it ideal for IoT, embedded systems, and hardware control projects developed with Nodepp.

## Dependencies & Cmake Integration
```bash
include(FetchContent)

FetchContent_Declare(
	nodepp
	GIT_REPOSITORY   https://github.com/NodeppOfficial/nodepp
	GIT_TAG          origin/main
	GIT_PROGRESS     ON
)
FetchContent_MakeAvailable(nodepp)

FetchContent_Declare(
	nodepp-serial
	GIT_REPOSITORY   https://github.com/NodeppOfficial/nodepp-serial
	GIT_TAG          origin/main
	GIT_PROGRESS     ON
)
FetchContent_MakeAvailable(nodepp-serial)

#[...]

target_link_libraries( #[...]
	PUBLIC nodepp nodepp-serial #[...]
)
```

## Key Features:
- **Asynchronous Operations:** Fully integrated with Nodepp's event loop for non-blocking serial port access.
- **Cross-Platform:** Designed to work across various operating systems supported by Nodepp.
- **Simple API:** An intuitive and Node.js-like API for opening, closing, reading from, and writing to serial ports.
- **Event-Driven:** Emits events for data reception, errors, and port status changes, simplifying event handling.

## Example
```cpp
#include <nodepp/nodepp.h>
#include <serial/serial.h>

using namespace nodepp;

void onMain(){

    auto device = serial::get_devices();

    if( device.empty() ){ 
        process::error("Not Serial Device Found"); 
    } else {
        console::log( device[0] );
    }

    serial::connect( device[0], 9600 )
    
    .then([]( serial_t cli ){

        console::done( "connected" );

        cli.onData([]( string_t chunk ){
            console::log( chunk );
        });

        stream::pipe( cli );

    })

    .fail([=]( except_t err ){
        console::log( "something went wrong" );
        console::error( err );
    });

}
```

## Compilation
```bash
g++ -o main main.cpp -I ./include ; ./main
```

## License
**Nodepp-Serial** is distributed under the MIT License. See the LICENSE file for more details.
