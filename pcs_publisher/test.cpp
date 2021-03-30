#include <iostream>

#include "pcs.h"

#include "transport_udp.h"

#include <unistd.h>


unsigned char buffer[32];

using namespace pcs;

int a = 40;

typedef struct {
	int a1;
	int a2;
	int a3;
	int a4;
}D;

Publisher<D> pub;

int main()
{
	std::cout<<"Program begins ..."<<std::endl;

	pcs::PCS pcs;
	pub = pcs.advertise<D>( "192.168.72.129", 5555 );

	D d;
	d.a1 = 100;
	d.a2 = 200;
	d.a3 = 300;
	d.a4 = 400;

	/*Transport *t = new TransportUDP;

	t->initSocketServer( 5555 );
	
	std::cout<<"fd = "<<t->getServerFd()<<std::endl;

	while(1){
		t->read( t->getServerFd(), buffer, sizeof( buffer ) );
	}*/

	while(1){
		pub.publish( d );			
	
		sleep(1);
	}
	return 0;
}
