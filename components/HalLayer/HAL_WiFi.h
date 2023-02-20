#pragma once 
#include "HAL_Module.h"
#include "HAL_Config.h"
#include "esp_err.h"
using namespace std;
class WiFi : public HALModule  
{
public:
    explicit WiFi(string moduleName = "WiFi");
    ~WiFi();
    int  init() override;

private:
   string  moduleName;
};



