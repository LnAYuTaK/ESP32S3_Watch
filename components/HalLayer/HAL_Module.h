#pragma once 
#include <string>
#include <iostream>
using namespace std;
class HALModule
{
public:
    HALModule(string moduleName);
    ~HALModule();
    virtual int init() = 0;
private:
    string moduleName;
};


