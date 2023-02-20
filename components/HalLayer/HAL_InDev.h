#pragma once 
#include "HAL_Config.h"
#include "HAL_Module.h"
using namespace std;
class Indev : public HALModule 
{
public:
    explicit Indev(string moduleName = "Indev");
    ~Indev();
    int  init() override;
private:
    string moduleName;
};