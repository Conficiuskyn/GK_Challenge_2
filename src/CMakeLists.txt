file(GLOB COMPONENT_SOURCES "components/*.cpp")
idf_component_register(SRCS "main.cpp" ${COMPONENT_SOURCES}
                    INCLUDE_DIRS "." "../include" "../include/components"
                    REQUIRES esp_wifi nvs_flash esp_event esp_netif lwip) 