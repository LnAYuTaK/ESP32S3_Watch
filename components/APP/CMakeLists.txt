file(GLOB_RECURSE SOURCES 	./*.cpp
							)

idf_component_register(SRCS	${SOURCES}
                   INCLUDE_DIRS 
								.
                    REQUIRES  
                    HalLayer
                    lvgl
                    Utils
                    esp_http_client
                    esp-tls
                    lvgl_esp32_drivers

)




