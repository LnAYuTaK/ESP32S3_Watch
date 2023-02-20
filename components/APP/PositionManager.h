#pragma once 
#include "ModuleBox.h"
#include "Connect.h"
#include "HAL_Manager.h"
#define DEFAULT_LAT  38.965767
#define DEFAULT_LON  120.083923
//位置管理器 处理坐标位置，地图换算
class PositionManager : public Module
{
private:
    /* data */
public:
    PositionManager(Application* app, ModuleBox* moduleBox);
    virtual ~PositionManager();
    void   setModuleBox(ModuleBox *moduleBox);
    double getLongitude()  {return this->data.longitude;}
    double getLatitude()   {return this->data.latitude;}
    double getSpeed()      {return this->data.speed;}
    double getAltitude()   {return this->data.altitude;}
private:
    void Upgrade(gps_data_t *data);
    GPS *_gps = nullptr;
    gps_data_t data = {0,0,0,0};
};
