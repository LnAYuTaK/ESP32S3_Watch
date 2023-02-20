/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/


/*********************
 *      INCLUDES
 *********************/
#include "lv_port.h"
#include <stdbool.h>
#include "lvgl_helpers.h"

static void disp_init(void);

void lv_port_disp_init(void)
{

    disp_init();
    static lv_disp_draw_buf_t draw_buf_dsc_2;
    static lv_color_t buf_2_1[DISP_BUF_SIZE];                        /*A buffer for 10 rows*/
    static lv_color_t buf_2_2[DISP_BUF_SIZE];                        /*An other buffer for 10 rows*/
    lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, DISP_BUF_SIZE);   /*Initialize the display buffer*/
    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/
    static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LV_VER_RES_MAX;
    disp_drv.ver_res = LV_HOR_RES_MAX;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_driver_flush;

    /*Set a display buffer*/
    disp_drv.draw_buf = &draw_buf_dsc_2;

    disp_drv.offset_y = -20;

    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /*You code here*/
    lvgl_driver_init();
}

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}
p
/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}



/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;

