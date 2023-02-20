#include "HAL_Screen.h"
#include "lv_port.h"
Screen::Screen(string moduleName)
    : HALModule(moduleName)
{
   
}
//-----------------------------------------------------------------------------
Screen::~Screen()
{

}
//-----------------------------------------------------------------------------
int Screen::init(void)
{
    lv_port_disp_init();
    return 0;
}
//-----------------------------------------------------------------------------

