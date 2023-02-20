#pragma once 
#include "HAL_SDCard.h"
#include "HAL_IMU.h"
#include "HAL_GPS.h"
#include "HAL_Config.h"
#include "HAL_WiFi.h"
#include "HAL_Screen.h"
using namespace std;
class HALManager 
{
public:
    HALManager(/* args */);
    ~HALManager();
    inline SDCard * sdCard(){return this->_sdCard;}
    inline GPS    * gps()   {return this->_gps;}
    inline WiFi   * wifi()  {return this->_wifi;}
    inline Screen * screen(){return this->_screen;}

public:
    static HALManager * _HALManager;
    void HALInit();
private:
    SDCard * _sdCard = nullptr;
    WiFi *   _wifi   = nullptr;
    GPS *    _gps    = nullptr;
    Screen * _screen = nullptr;
};
HALManager * HAL(void);
