#include "HAL_Manager.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
static const char *TAG = "gps_demo";
#define TIME_ZONE (+8)   //Beijing Time
#define YEAR_BASE (2000) //date in GPS starts from 2000

#define NMEA_PARSER_CONFIG_DEFAULT()       \
    {                                      \
        .uart = {                          \
            .uart_port = UART_NUM_1,       \
            .rx_pin = CONFIG_GPS_RX_PIN,   \
            .baud_rate = CONFIG_GPS_UART_BAUD_RATE,             \
            .data_bits = UART_DATA_8_BITS, \
            .parity = UART_PARITY_DISABLE, \
            .stop_bits = UART_STOP_BITS_1, \
            .event_queue_size = CONFIG_GPS_EVENT_QUEUESIZE         \
        }                                  \
    }
//------------------------------------------------------------------
static void gps_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    gps_t *gps = NULL;
    switch (event_id) {
    case GPS_UPDATE:
        gps = (gps_t *)event_data;
        ESP_LOGI(TAG, "%d/%d/%d %d:%d:%d => \r\n"
                 "\t\t\t\t\t\tlatitude   = %.05f°N\r\n"
                 "\t\t\t\t\t\tlongitude = %.05f°E\r\n"
                 "\t\t\t\t\t\taltitude   = %.02fm\r\n"
                 "\t\t\t\t\t\tspeed      = %fm/s",
                gps->date.year + YEAR_BASE, gps->date.month, gps->date.day,
                gps->tim.hour + TIME_ZONE, gps->tim.minute, gps->tim.second,
                gps->latitude, gps->longitude, gps->altitude, gps->speed);
        break;
    case GPS_UNKNOWN:
        /* print unknown statements */
        ESP_LOGW(TAG, "Unknown statement:%s", (char *)event_data);
        break;
    default:
        break;
    }
}
//------------------------------------------------------------------
GPS::GPS(string moduleName)
    :HALModule(moduleName)
{
    SignalGps = new Signal<gps_data_t*>();
}
//-----------------------------------------------------------------------------
GPS::~GPS()
{

}
//------------------------------------------------------------------
int GPS::init()
{
    nmea_parser_config_t config = NMEA_PARSER_CONFIG_DEFAULT();
    nmea_parser_handle_t nmea_hdl = nmea_parser_init(&config);
    nmea_parser_add_handler(nmea_hdl, gps_event_handler, NULL);
    return ESP_OK;
}

