#ifndef __CST816T_H
#define __CST816T_H

#include <stdint.h>
#include <stdbool.h>
#include "lvgl_helpers.h"
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CST816T_I2C_SLAVE_ADDR    0X15

#define CST816T_MAX_X_COORD    LV_VER_RES_MAX
#define CST816T_MAX_Y_COORD    LV_HOR_RES_MAX

typedef struct {
    bool inited;
    uint8_t product_id;
    uint16_t max_x_coord;
    uint16_t max_y_coord;
    uint8_t i2c_dev_addr;
} cst816t_status_t;

/**
  * @brief  Initialize for CST816T communication via I2C
  * @param  dev_addr: Device address on communication Bus (I2C slave address of GT911).
  * @retval None
  */
void cst816t_init(uint8_t dev_addr);

/**
  * @brief  Get the touch screen X and Y positions values. Ignores multi touch
  * @param  drv:
  * @param  data: Store data here
  * @retval Always false
  */
bool cst816t_read(lv_indev_drv_t *drv, lv_indev_data_t *data);

#ifdef __cplusplus
}
#endif
#endif /* __CST816T_H */
