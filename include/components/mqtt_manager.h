#include "freertos/FreeRTOS.h"
#include "mqtt_client.h"
#include "esp_log.h"

class MQTTManager
{
    public:
        static constexpr const char* TAG = "[mqtt manager]";
        void start();
        bool isRunning();
        void setBrokerUri(const char* uri);
    
    private:
        bool _running = false;
        static void mqtt_event_handler(
            void *arg,
            esp_event_base_t event_base,
            int32_t event_id,
            void *event_data); 
};