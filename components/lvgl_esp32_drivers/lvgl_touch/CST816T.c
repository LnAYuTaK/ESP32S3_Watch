#include <esp_log.h>
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include <lvgl.h>
#else
#include <lvgl/lvgl.h>
#endif
#include "CST816T.h"

#include "lvgl_i2c/i2c_manager.h"

#include "driver/gpio.h"

#define TAG "CST816T"

cst816t_status_t cst816t_status;

//TODO: handle multibyte read and refactor to just one read transaction
esp_err_t cst816t_i2c_read( uint8_t slave_addr, uint16_t register_addr, uint8_t *data_buf, uint8_t len ) 
{
    return lvgl_i2c_read( CONFIG_LV_I2C_TOUCH_PORT, slave_addr, register_addr | I2C_REG_16, data_buf, len );
}

esp_err_t cst816t_i2c_write8( uint8_t slave_addr, uint16_t register_addr, uint8_t data ) 
{
    uint8_t buffer = data;
    return lvgl_i2c_write( CONFIG_LV_I2C_TOUCH_PORT, slave_addr, register_addr | I2C_REG_16, &buffer, 1 );
}


static xQueueHandle ctp_evt_queue = NULL;

static void IRAM_ATTR ctp_isr_handler( void* arg )
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR( ctp_evt_queue, &gpio_num, NULL );
}

#define CTP_INT_IO          2
#define CTP_INT_PIN_SEL     ( 1ULL << CTP_INT_IO )

static struct
{
    int16_t last_x;         // x 坐标
    int16_t last_y;         // y 坐标
    int16_t flag;
}ctp_data;

static void ctp_task( void* arg )
{
    uint32_t io_num;

    while( 1 )
    {
        if( xQueueReceive( ctp_evt_queue, &io_num, portMAX_DELAY ) ) 
        {
            uint8_t touch_data[7];

            cst816t_i2c_read( cst816t_status.i2c_dev_addr, 0x00, touch_data, 7 );

            if( touch_data[2] != 0x00 )
            {
                ctp_data.last_x = ((uint16_t)(touch_data[3] & 0x0f) << 8) | (uint16_t)touch_data[4];
                ctp_data.last_y = ((uint16_t)(touch_data[5] & 0x0f) << 8) | (uint16_t)touch_data[6];

                #if CONFIG_LV_CST816T_INVERT_X
                    ctp_data.last_x = cst816t_status.max_x_coord - ctp_data.last_x;
                #endif
                #if CONFIG_LV_CST816T_INVERT_Y
                    ctp_data.last_y = cst816t_status.max_y_coord - ctp_data.last_y;
                #endif
                #if CONFIG_LV_CST816T_SWAPXY
                    int16_t swap_buf = ctp_data.last_x;
                    ctp_data.last_x = ctp_data.last_y;
                    ctp_data.last_y = swap_buf;
                #endif

                ctp_data.flag = 1;        // 按下
            }
            else
            {
                ctp_data.last_x = 0;
                ctp_data.last_y = 0;
                ctp_data.flag   = 0;       // 松开
            }
        }
    }
}

void CTP_INT_Init( void )
{
    gpio_config_t io_conf   = {};                       // zero-initialize the config structure.
    io_conf.pin_bit_mask    = CTP_INT_PIN_SEL;          // bit mask of the pins
    io_conf.intr_type       = GPIO_INTR_ANYEDGE;        // interrupt of falling edge
    io_conf.mode            = GPIO_MODE_INPUT;          // set as input mode
    io_conf.pull_up_en      = 1;                        // enable pull-up mode
    gpio_config( &io_conf );

    ctp_evt_queue = xQueueCreate(10, sizeof(uint32_t));                            // create a queue to handle gpio event from isr
    xTaskCreate( ctp_task, "ctp_task", 2048, NULL, 10, NULL );                      // start gpio task

    gpio_install_isr_service( ESP_INTR_FLAG_LEVEL3 );                               // install gpio isr service
    gpio_isr_handler_add( CTP_INT_IO, ctp_isr_handler, (void*) CTP_INT_IO );        // hook isr handler for specific gpio pin
}

uint8_t get_ctp_int( void )
{
    return gpio_get_level( CTP_INT_IO );
}

/**
  * @brief  Initialize for CST816T communication via I2C
  * @param  dev_addr: Device address on communication Bus (I2C slave address of CST816T).
  * @retval None
  */
void cst816t_init( uint8_t dev_addr ) 
{
    if( !cst816t_status.inited ) 
    {
        cst816t_status.i2c_dev_addr = dev_addr;

        cst816t_i2c_read( cst816t_status.i2c_dev_addr, 0xA7, &cst816t_status.product_id, 1 );

        if( cst816t_status.product_id == 0xB5 )
        {
            ESP_LOGI(TAG, "touch chip: CST816T");
        }

        cst816t_i2c_write8( cst816t_status.i2c_dev_addr, 0xFA, 0x60 );   // 报点模式
        cst816t_i2c_write8( cst816t_status.i2c_dev_addr, 0xFE, 0x01 );   // 禁止休眠

        cst816t_status.max_x_coord = CST816T_MAX_X_COORD;
        cst816t_status.max_y_coord = CST816T_MAX_Y_COORD;

        cst816t_status.inited = true;

        CTP_INT_Init(  );
    }
}

/**
  * @brief  Get the touch screen X and Y positions values. Ignores multi touch
  * @param  drv:
  * @param  data: Store data here
  * @retval Always false
  */
bool cst816t_read(lv_indev_drv_t *drv, lv_indev_data_t *data) 
{
    data -> point.x = ctp_data.last_x;
    data -> point.y = ctp_data.last_y;

    if( ctp_data.flag )
    {
        data->state     = LV_INDEV_STATE_PR;        // 按下
    }
    else
    {
        data -> state   = LV_INDEV_STATE_REL;       // 松开
    }

    #if LVGL_VERSION_MAJOR >= 8
        data->continue_reading = false;
    #endif

    return false;
}
