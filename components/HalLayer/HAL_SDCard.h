#pragma once 
#include "HAL_Module.h"
using namespace std;
class SDCard : public HALModule  
{
public:
    explicit SDCard(string moduleName = "SDCard");
    ~SDCard();
    int  init() override;
private:
   string  moduleName;
};






