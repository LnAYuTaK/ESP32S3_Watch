#pragma once 
/*     屏幕引脚配置  */
#include "hal/gpio_types.h"
#define CONFIG_SCREEN_DC_PIN        GPIO_NUM_2
#define CONFIG_SCREEN_SCK_PIN       GPIO_NUM_10
#define CONFIG_SCREEN_MOSI_PIN      GPIO_NUM_11
#define CONFIG_SCREEN_HOR_RES       240
#define CONFIG_SCREEN_VER_RES       280
/*      GPS         */
#define CONFIG_GPS_RX_PIN           GPIO_NUM_5
#define CONFIG_GPS_UART_BAUD_RATE   9600
#define CONFIG_GPS_EVENT_QUEUESIZE  16
#define CONFIG_GPS_UART_NUM         UART_NUM_1
/*      IMU         */
// #define CONFIG_IMU_INT1_PIN         PB10
// #define CONFIG_IMU_INT2_PIN         PB11
/*      电池        */
// #define CONFIG_POWER_EN_PIN         PA12
// #define CONFIG_POWER_WAIT_TIME      1000
// #define CONFIG_POWER_SHUTDOWM_DELAY 5000
// #define CONFIG_POWER_BATT_CHG_DET_PULLUP    true
/*      SD卡       */
#define CONFIG_SD_CMD_PIN          GPIO_NUM_2
#define CONFIG_SD_D0_PIN           GPIO_NUM_15
#define CONFIG_SD_CLK_PIN          GPIO_NUM_14
#define MOUNT_POINT                "/SD"
/*      WiFi      */ 
#define CONFIG_WIFI_SSID        "AmaneSuzuha"
#define CONFIG_WIFI_PASSWD      "88888888"
#define WIFI_CONNECT_MAXIMUM_RETRY  10
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

/*       LVGL     */
//#define LVGL_FS_FATFS_DISABLED	// 禁用lvgl文件接口


/* 是否启用 lvgl的文件系统，如果定义了LVGL_FS_FATFS_DISABLED 则禁用（默认：启用） */
#if !defined(LVGL_FS_FATFS_DISABLED)
	#ifndef LVGL_FS_FATFS_DISABLED
		#define LVGL_FS_FATFS_DISABLED
	#endif
#endif
