#include "HAL_Manager.h"
HALManager * HALManager ::_HALManager  = nullptr;
HALManager ::HALManager (/* args */)
{
    _HALManager   = this;
    this->_sdCard = new SDCard();
    this->_wifi   = new WiFi();
    this->_gps    = new GPS();
    this->_screen = new Screen();
}
//-----------------------------------------------------------------------------
HALManager ::~HALManager ()
{
    
}
//----------------------------------------------------------------------
void HALManager::HALInit()
{
    this->_sdCard->init();
    this->_wifi->init();
    this->_gps->init();
    // this->_screen->init();
}
//-----------------------------------------------------------------------------
//Singleton Inference
HALManager  *HAL()
{
    return HALManager ::_HALManager ;
}
//-----------------------------------------------------------------------------








