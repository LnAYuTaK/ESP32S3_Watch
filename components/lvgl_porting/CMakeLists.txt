file(GLOB_RECURSE SOURCES 	./*.cpp
					)

idf_component_register(SRCS	${SOURCES}
                   INCLUDE_DIRS 
								.
                    REQUIRES lvgl
                             lvgl_esp32_drivers
                             fatfs
                            )
