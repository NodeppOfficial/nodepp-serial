#include <nodepp/nodepp.h>
#include <serial/serial.h>

using namespace nodepp;

void onMain(){

    auto devices = serial::scan();

    if( !devices.has_value() ){ 
        console::error( "device not found" );
        return;
    }

    for( auto x: devices.value() ){
        console::log( ">>", x );
    }

}