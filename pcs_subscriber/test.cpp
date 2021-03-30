#include <iostream>

#include "pcs.h"

#include "transport_udp.h"

#include <unistd.h>

#include "dataType.h"


using namespace pcs;


void test( sensors::LidarScan scan )
{
	/*std::cout<<"angle_min: "<<scan.angle_min<<std::endl;
	std::cout<<"angle_max: "<<scan.angle_max<<std::endl;
	std::cout<<"angle_increment: "<<scan.angle_increment<<std::endl;
	std::cout<<"range_min: "<<scan.range_min<<std::endl;
	std::cout<<"range_max: "<<scan.range_max<<std::endl;*/
	
	printf( "angle_min: %lf\r\n", scan.angle_min);
	printf( "angle_max: %lf\r\n", scan.angle_max );
}

int main()
{
	std::cout<<"Program begins ..."<<std::endl;

	pcs::PCS pcs;
	
	Subscriber<sensors::LidarScan> sub = pcs.subscribe<sensors::LidarScan>( "192.168.72.129", 5555, test );


	while(1){
	
		sleep(1);
	}
	return 0;
}
