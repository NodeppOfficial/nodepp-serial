/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#pragma once
#include <termios.h>

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class serial_t : public file_t {
protected:

	int GETBAUD( uint baud ) const noexcept {
		switch( baud ){
			case 110:     return B110;    break;
			case 300:     return B300;    break;
			case 600:     return B600;    break;
			case 1200:    return B1200;   break;
			case 2400:    return B2400;   break;
			case 4800:    return B4800;   break;
			case 9600:    return B9600;   break;
			case 19200:   return B19200;  break;
			case 38400:   return B38400;  break;
			case 57600:   return B57600;  break;
			case 115200:  return B115200; break;
			default:      return B9600;   break;
		}
	}

	void set_baud_rate( const int& fd, uint baud ) const noexcept {
        struct termios options; tcgetattr( fd, &options );

        options.c_cflag = GETBAUD(baud) | CS8 | CLOCAL | CREAD;
        options.c_iflag = IGNPAR;
        options.c_oflag = 0;
        options.c_lflag = 0;

        tcflush( fd, TCIFLUSH ); tcsetattr( fd, TCSANOW, &options );
	}

public:

	serial_t( const string_t& path, uint baud=0, const ulong& _size=CHUNK_SIZE )
	: file_t( path, nullptr ){ 
		auto self = type::bind(this); set_baud_rate( this->get_fd(), baud );
		process::add([=](){ this->onOpen.emit(); return -1; });
	}

	serial_t() noexcept : file_t() {}

};}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace serial {

    template <class... T>
    promise_t<serial_t,except_t> connect( const T&... args ){ 
	return promise_t<serial_t,except_t>([=]( function_t<void,serial_t> res, function_t<void,except_t> rej ){
	try  { serial_t socket( args... ); res( socket ); } 
	catch( except_t err ) { rej( err ); } }); }

    template <class... T>
    serial_t await( const T&... args ){ return serial_t( args... ); }

	array_t<string_t> get_devices(){
		queue_t<string_t> result; for( auto x : fs::read_folder("/dev") ){
			if( strncmp(x.data(),"ttyUSB",6)==0 ||
				strncmp(x.data(),"ttyACM",6)==0 ||
				strncmp(x.data(),"ttyS"  ,4)==0
			){  result.push( "/dev/" + x );  }
		}	return result.data();
	}

}}

/*────────────────────────────────────────────────────────────────────────────*/
