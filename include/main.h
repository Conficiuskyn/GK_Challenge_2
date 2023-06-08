#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "wifi_station.h"
#include "nvs_flash.h"
#include "mqtt_manager.h"

class Main
{
    static constexpr const char* TAG = "[main]";
    WifiStation wifi;
    MQTTManager mqtt_client;

    public:
        void run();
};