#include "PositionManager.h"
PositionManager::PositionManager(Application* app, ModuleBox* moduleBox)
    :Module(app, moduleBox)
    ,_gps(HAL()->gps())
{

}
//******************************************************
PositionManager::~PositionManager()
{ 

}
//******************************************************
void PositionManager::Upgrade(gps_data_t *data)
{
    // this->data.altitude  = data->altitude;
    // this->data.latitude  = data->latitude;
    // this->data.longitude = data->longitude;
    // this->data.speed     = data->speed;
}
//******************************************************
void PositionManager::setModuleBox(ModuleBox * moduleBox)
{
   //绑定HAL_GPS
    // _gps->SignalGps->ValueChanged.Bind(this,&PositionManager::Upgrade);
}