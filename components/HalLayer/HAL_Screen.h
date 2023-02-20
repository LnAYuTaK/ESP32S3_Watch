#pragma once
#include "HAL_Config.h"
#include "HAL_Module.h"
using namespace std;
class Screen : public HALModule 
{
public:
    explicit Screen(string moduleName = "Screen");
    ~Screen();
    int  init() override;
private:
    string moduleName;
};