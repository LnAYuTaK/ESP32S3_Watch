#pragma once 
#include "HAL_Config.h"
#include "HAL_Module.h"
using namespace std;
class IMU : public HALModule 
{
public:
    explicit IMU(string moduleName = "IMU");
    ~IMU();
    int  init() override;
private:
    string moduleName;
};