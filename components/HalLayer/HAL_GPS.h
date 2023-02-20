#pragma once 
#include "HAL_Config.h"
#include <string.h>
#include "HAL_Module.h"
#include "Connect.h"
#include "esp_event.h"
#include "freertos/queue.h"
#include "time.h"
#include "nmea_parser.h"
using namespace std;
//gps消息结构体
typedef struct gps_data_s
{
    double latitude;
    double longitude;
    double altitude;
    double speed;
}gps_data_t;
class GPS : public HALModule 
{
private:
    /* data */
public:
    explicit  GPS(string moduleName = "GPS");
    ~GPS();
    int init() override;
    Signal<gps_data_t*>*SignalGps;
private:
    string moduleName;  
};

esp_err_t  gpsInit();


