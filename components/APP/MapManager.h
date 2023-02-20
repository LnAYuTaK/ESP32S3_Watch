#pragma once 
#include "ModuleBox.h"
class PositionManager;
class MapProvider;
class AmapProvider;
class MapManager : public Module
{
private:
    /* data */
public:
    MapManager(Application* app, ModuleBox* moduleBox);
    virtual ~MapManager();
    void setModuleBox(ModuleBox *moduleBox);
    // void getTileMap(int zoom ,int x ,int y);
    void setMapProvider(MapProvider *mapProvider);

    AmapProvider * mapProvider(){return this-> _provide;}
private:
//    esp_err_t connectAMapServer;
//    esp_http_client_handle_t client;
   PositionManager *_positionMgr;
   AmapProvider *   _provide;
};