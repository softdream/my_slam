#include "hectorSlam.h"

HectorSlam::HectorSlam(): lastGetMapUpdateIndex( -100 )
{
	this->initParameters();

	//-------------------- Initialized a New Slam Processor ---------------------------//
	slamProcessor = new hectorslam::HectorSlamProcessor(static_cast<float>(p_map_resolution_),
                                                        	p_map_size_, 
								p_map_size_,
                                                        	Eigen::Vector2f(p_map_start_x_, p_map_start_y_),
                                                        	p_map_multi_res_levels_);
	//---------------------- Set Some Parameters -------------------------------------//
        slamProcessor->setUpdateFactorFree(p_update_factor_free_);                // 0.4
        slamProcessor->setUpdateFactorOccupied(p_update_factor_occupied_);        // 0.9
        slamProcessor->setMapUpdateMinDistDiff(p_map_update_distance_threshold_); // 0.4
        slamProcessor->setMapUpdateMinAngleDiff(p_map_update_angle_threshold_);   // 0.9

	//----------------------  --------------------------//
}

HectorSlam::~HectorSlam()
{
	delete slamProcessor;
}

void HectorSlam::initParameters()
{
	p_map_resolution_ = 0.05;
	p_map_size_ = 2048;
	p_map_start_x_ = 0.5;
	p_map_start_y_ = 0.5;
	p_map_multi_res_levels_ = 3;

	p_update_factor_free_ = 0.4;
	p_update_factor_occupied_ = 0.9;
	p_map_update_distance_threshold_ = 0.4;
	p_map_update_angle_threshold_ = 0.9;
	
}

bool HectorSlam::LaserScan2DataContainer( const sensors::LidarScan &scan, hectorslam::DataContainer& dataContainer, float scaleToMap )
{
	size_t size = scan.size();

  	float angle = scan.angle_min;

  	dataContainer.clear();

  	dataContainer.setOrigo(Eigen::Vector2f::Zero());

  	float maxRangeForContainer = scan.range_max - 0.1f;

  	for (size_t i = 0; i < size; ++i){
    		float dist = scan.ranges[i];

    		if ( (dist > scan.range_min) && (dist < maxRangeForContainer)){
      			dist *= scaleToMap;
      			dataContainer.add(Eigen::Vector2f(cos(angle) * dist, sin(angle) * dist));
    		}

    		angle += scan.angle_increment;
  	}

  	return true;
}

void HectorSlam::scanCallback( const sensors::LidarScan &scan )
{
	Eigen::Vector3f startEstimate(Eigen::Vector3f::Zero());
	if( LaserScan2DataContainer( scan, laserScanContainer, slamProcessor->getScaleToMap() ) == true ){
		// 首先获取上一帧的位姿，作为初值
        	startEstimate = slamProcessor->getLastScanMatchPose();

        	// 进入扫描匹配与地图更新
        	slamProcessor->update(laserScanContainer, startEstimate);
	}
}

void HectorSlam::getMap(  const hectorslam::GridMap &gridMap)
{
	cv::Mat map;
	if (lastGetMapUpdateIndex != gridMap.getUpdateIndex()){
        	int sizeX = gridMap.getSizeX();
        	int sizeY = gridMap.getSizeY();
	
		unsigned char **data = new unsigned char[sizeX][sizeY];
		for( int i = 0; i < sizeX; ++i ){
			for( int j = 0; j < sizeY; ++j ){
				if( gridMap.isFree( i * sizeY + j ) ){
					data[i][j] = 0;
				}
				else if( gridMap.isOccupied( i * sizeY + j ) ){
					data[i][j] = 100;
				}
			}
		}
	
		lastGetMapUpdateIndex = gridMap.getUpdateIndex();
	}
	
	delete[] data;
}

void HectorSlam::getPose()
{

}














