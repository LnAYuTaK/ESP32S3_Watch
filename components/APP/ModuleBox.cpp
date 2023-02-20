#include "ModuleBox.h"
#include "PositionManager.h"
#include "MapManager.h"

// #include "ViewPluginManager.h"
// #include "FreekApplication.h"
// #include "ViewSetup.h"
// #include "SettingsManager.h"
// #include "PositionManager.h"
// #include "MapEngineManager.h"
ModuleBox::ModuleBox(Application * app)
{
    _positionManager = new  PositionManager (app,this);
    _mapManager      = new  MapManager      (app,this);
    // _viewPluginManager = new   ViewPluginManager (app,this);
    // _viewSetup         = new   ViewSetup         (app,this);
}
//-----------------------------------------------------------------------------
void ModuleBox::setChildBoxes(void)
{
    // _viewPluginManager->setModuleBox(this);
    // _viewSetup->setModuleBox(this);
    _positionManager->setModuleBox(this);
    _mapManager->setModuleBox(this);
}
//-----------------------------------------------------------------------------
Module::Module(Application * app,ModuleBox *moduleBox)
    :_moduleBox(nullptr),
    _app(app)
{

}

//-----------------------------------------------------------------------------
void Module::setModuleBox(ModuleBox *moduleBox)
{
    _moduleBox  = moduleBox;
}
//-----------------------------------------------------------------------------

