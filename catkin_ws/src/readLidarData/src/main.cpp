#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>
#include "dataType.h"

sensors::LidarScan lidarScan;

void laserCallback( const sensor_msgs::LaserScan::ConstPtr &scan )
{
	std::cout<<"laser call back ..."<<std::endl;

	memset( &lidarScan, 0, sizeof( lidarScan ) );
	lidarScan.angle_min = scan->angle_min;
	lidarScan.angle_max = scan->angle_max;
	lidarScan.angle_increment = scan->angle_increment;
	lidarScan.scan_time = scan->scan_time;
	lidarScan.time_increment = scan->time_increment;
	lidarScan.range_min = scan->range_min;
	lidarScan.range_max = scan->range_max;

	for( int i = 0; i < 360; i ++ ){
		lidarScan.ranges[i] = scan->ranges[i];
		lidarScan.intensities[i] = scan->intensities[i];
	}


}

int main( int argc, char **argv )
{
	ROS_INFO("Program Begins ...");
	ros::init( argc, argv, "read_lidar_data" );
	ros::NodeHandle n;
	
	ros::Subscriber lidar_sub = n.subscribe<sensor_msgs::LaserScan>("/laser_scan", 1, laserCallback);

	ros::spin();

	return 0;
}

