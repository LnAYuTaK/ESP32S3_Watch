#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_timer.h"

#include "lvgl.h"
#include "lv_port.h"

#include "HAL_Manager.h"
#include "Application.h"
// #include "lv_port.h"
static void lv_tick_task(void *arg)
{
	(void)arg;
	lv_tick_inc(10);
}

extern "C" void app_main(void) 
{ 
    lv_init();
    //HAL先初始化
    HALManager * hal = new  HALManager();
    hal->HALInit();
    //APP层初始化
    Application *app = new Application();
    app->appInit();
//LVGL定时器心跳
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "LVGL_GUI"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 10 * 1000));
}
