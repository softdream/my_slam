#ifndef hectormapmutex_h__
#define hectormapmutex_h__

#include "MapLockerInterface.h"

#include <mutex>

class HectorMapMutex : public MapLockerInterface
{
public:
  virtual void lockMap()
  {
    mapModifyMutex_.lock();
  }

  virtual void unlockMap()
  {
    mapModifyMutex_.unlock();
  }

  std::mutex mapModifyMutex_;
};

#endif
