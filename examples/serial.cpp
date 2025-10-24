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