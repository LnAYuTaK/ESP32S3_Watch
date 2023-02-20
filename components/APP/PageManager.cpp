#include "PageManager.h"
PageManager::PageManager(Application* app, ModuleBox* moduleBox)
    :Module(app, moduleBox)
{

}
//******************************************************
PageManager::~PageManager()
{ 

}
//******************************************************
void PageManager::setModuleBox(ModuleBox * moduleBox)
{
//这里负责连接所需要的HAL层或者APP层组件
}

// /******************************************************
//  * @brief   设置当前页面
//  * @param   pageMgr      页面管理类
//  * @param   page     页面
//  * @return  无
//  ******************************************************/
// void PageManager::PageMgr_set_current_page(lv_obj_t *page)
// {
//     // pageMgr->current_page = page;
//     this->current_page = page;
// }
// /******************************************************
//  * @brief   获取当前页面
//  * @param   pageMgr      页面管理类
//  * @return  当前页面
//  ******************************************************/
// lv_obj_t * PageManager::PageMgr_get_current_page()
// {
//     return this->current_page;
// }

// /******************************************************
//  * @brief   设置下一个页面
//  * @param   pageMgr      页面管理类
//  * @param   page     页面
//  * @return  无
//  ******************************************************/
// void PageManager::PageMgr_set_next_page(lv_obj_t *page)
// {
//    this->next_page = page;
// }
// /******************************************************
//  * @brief   获取下一个页面
//  * @param   pageMgr      页面管理类
//  * @return  下一个页面
//  ******************************************************/
// lv_obj_t * PageManager::PageMgr_get_next_page()
// {
//     return pageMgr->next_page;
// }
// /******************************************************
//  * @brief   切换页面
//  * @param   pageMgr      页面管理类
//  * @return  无
//  ******************************************************/
// void PageManager::PageMgr_switch_page()
// {
//     lv_obj_t *current_page = this->currentPage;
//     lv_obj_t *next_page = this->nextPage;
//     lv_obj_set_hidden(current_page, true);
//     lv_obj_set_hidden(next_page, false);
//     this->current_page = pageMgr->next_page;
//     this->next_page = NULL;
// }
