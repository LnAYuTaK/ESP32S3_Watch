
/**
 * @file Application.cpp
 * @author LnAYuTaK (807874484@qq.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Application.h"
#include "ModuleBox.h"
#include "HAL_Manager.h"
Application* Application::_app = nullptr;
Application::Application()
{
     _app = this;
}
//-----------------------------------------------------------------------------
Application::~Application()
{  
     delete _moduleBox;
}
//-----------------------------------------------------------------------------
//全局单例接口
Application* App(void)
{
    return Application::_app;
}
//-----------------------------------------------------------------------------
void Application::appInit()
{
     _moduleBox = new ModuleBox(this);
     _moduleBox->setChildBoxes();
}
//-----------------------------------------------------------------------------







