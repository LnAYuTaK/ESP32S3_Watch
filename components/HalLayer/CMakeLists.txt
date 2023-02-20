file(GLOB_RECURSE SOURCES 	./*.cpp
							)

idf_component_register(SRCS	${SOURCES}
                   INCLUDE_DIRS 
								.
                    REQUIRES  fatfs
 			                  spiffs
                              Nmea
                              Utils
                              nvs_flash
                              lvgl_porting
                              esp_sqlite3
                              lvgl_porting
)

