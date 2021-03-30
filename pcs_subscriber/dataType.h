#ifndef __DATATYPE_H_
#define __DATATYPE_H_

#include "stdint.h"

namespace sensors{

struct LidarScan{
	LidarScan(){}
	~LidarScan(){}

	LidarScan( const LidarScan& obj ) : angle_min( obj.angle_min ),
					    angle_max( obj.angle_max ),
					    angle_increment( obj.angle_increment ),
					    scan_time( obj.scan_time ),
					    time_increment( obj.time_increment ),
					    range_min( obj.range_min ),
					    range_max( obj.range_max )
	{
		memcpy( this->ranges, obj.ranges, 360 );
		memcpy( this->intensities, obj.intensities, 360 );
	}

	LidarScan& operator=( const LidarScan& other )
	{
		angle_min = other.angle_min;
		angle_max = other.angle_max;
		angle_increment = other.angle_increment;
		scan_time = other.scan_time;
		time_increment = other.time_increment;
		range_min = other.range_min;
		range_max = other.range_max;
		memcpy( this->ranges, other.ranges, 360 );
                memcpy( this->intensities, other.intensities, 360 );
	}

	const int size()
	{
		return 360;
	}
	const int size() const{
		return 360;
	}
	
	float angle_min;
        float angle_max;
        float angle_increment;
        float scan_time;
        float time_increment;
        float range_min;
        float range_max;
        float ranges[360];
        float intensities[360];
};
typedef struct LidarScan LidarScan;

}

#endif


