#ifndef __HECTORSLAM_H_
#define __HECTORSLAM_H_

#include "GridMap.h"
#include "HectorSlamProcessor.h"
#include "DataPointContainer.h"
#include "MapLockerInterface.h"
#include "HectorMapMutex.h"

#include<opencv2/opencv.hpp>

#include "dataType.h"

class HectorSlam{
public:
	HectorSlam();
	~HectorSlam();

	//---------------- Main Process is in here ----------------//
	void scanCallback( const sensors::LidarScan &scan );

	//---------------- Display the Map by Opencv --------------//
	void displayMap(  const hectorslam::GridMap &gridMap);

	void getPose();
	
private:
	//----------------- Some Private Functions -----------------//
	void initParameters();
	bool LaserScan2DataContainer( const sensors::LidarScan &scan, hectorslam::DataContainer& dataContainer, float scaleToMap );
	
private:
	//------------------ Init Slam Processor ---------------------//
	hectorslam::HectorSlamProcessor *slamProcessor;
    	hectorslam::DataContainer laserScanContainer;
    	//PoseInfoContainer poseInfoContainer_; // 用于记录轨迹

        int lastGetMapUpdateIndex;

	//------------------ Init some Parameters ------------------//
	// 地图更新参数
        double p_update_factor_free_;
	double p_update_factor_occupied_;
	double p_map_update_distance_threshold_;
	double p_map_update_angle_threshold_;

       // map parameters --- resolution / size / init pose / map levels 
	double p_map_resolution_;
        int p_map_size_;
        double p_map_start_x_;
        double p_map_start_y_;
        int p_map_multi_res_levels_;
        double p_map_pub_period_;
};

#endif
