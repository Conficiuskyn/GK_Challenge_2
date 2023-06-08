#include "freertos/FreeRTOS.h"
#include "mqtt_client.h"

class MQTTManager
{
    public:
        static constexpr const char* TAG = "[mqtt manager]";
        void start();
    
    private:
        static esp_mqtt_client_handle_t client;
        static void mqtt_event_handler(
            void *arg,
            esp_event_base_t event_base,
            int32_t event_id,
            void *event_data); 
};