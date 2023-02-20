#ifndef MODULEBOX_H
#define MODULEBOX_H

#include "Application.h"
// class ViewPluginManager;
// class ViewSetup;
// class SettingsManager;
// class PositionManager;
// class MapEngineManager;
class PositionManager;
class MapManager;
///
/// \brief The ModuleBox class
/// 统一接口管理所有插件
///
class ModuleBox 
{
public:
    ModuleBox(Application * app);
    void setChildBoxes(void);
    // SettingsManager *     settingsManager()   { return this->_settingsManager; }
    MapManager *        mapManager()        { return this->_mapManager; }
    // ViewPluginManager *   viewPluginManager() { return this->_viewPluginManager; }
    PositionManager *   positionManager()   { return this->_positionManager; }
    // ViewSetup *           viewSetup()         { return this->_viewSetup; }
    // PageManager *         pageManager()       { return this->PageManager;}
private:
    // SettingsManager*      _settingsManager    = nullptr;
    MapManager *        _mapManager      = nullptr;
    // ViewPluginManager *   _viewPluginManager  = nullptr;
    // ViewSetup *           _viewSetup          = nullptr;
    PositionManager *   _positionManager = nullptr;
    //TUDO
};

class Module
{
public:
    Module(Application * app,ModuleBox* moduleBox);
    virtual void setModuleBox(ModuleBox *moduleBox);
protected:
    ModuleBox  * _moduleBox;
    Application * _app;
};

#endif // MODULEBOX_H
