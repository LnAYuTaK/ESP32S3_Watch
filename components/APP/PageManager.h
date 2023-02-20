#pragma once 
#include "ModuleBox.h"
#include "lvgl/lvgl.h"
#include  <vector>
//页面管理器
class PageManager : public Module
{
private:
    /* data */
public:
    PageManager(Application* app, ModuleBox* moduleBox);
    virtual ~PageManager();
    // void PageMgr_set_current_page();
    // lv_obj_t *PageMgr_get_current_page();
    // lv_obj_t * PageMgr_get_current_page();
    // void SetNextPage(lv_obj_t *page);
    // lv_obj_t * PageMgr_get_next_page()
    void   setModuleBox(ModuleBox *moduleBox);
private:
    lv_obj_t *currentPage;
    lv_obj_t *nextPage;
    lv_obj_t *lastPage;
    vector<lv_obj_t *> PageVector;
};
