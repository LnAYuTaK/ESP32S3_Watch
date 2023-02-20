// #ifndef Application_H
// #define Application_H
#pragma once 
#include <iostream>
#include <string>

using namespace std;
class ModuleBox;
///
/// \brief The Application class
///
class Application
{
public:
    Application();
    ~Application();
    string name()          {return _name;}
    ModuleBox * moduleBox(){return _moduleBox;}
public :
    void appInit();
    static Application*  _app;
private:
    // static Application*  _app;
    ModuleBox *              _moduleBox;
    void                     _exitWithError    (string errorMessage);
    static string _name;
};
Application* App(void);

