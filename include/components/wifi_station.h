#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include <cstring>

class WifiStation
{
    public:

        enum class WifiState {
            NOT_INITIALIZED,
            INITIALIZED,
            READY_TO_CONNECT,
            CONNECTING,
            WAITING_FOR_IP,
            CONNECTED,
            DISCONNECTED,
            ERROR
        };

        static constexpr const char* TAG = "[wifi station]";
        void setSSIDandPASSWORD(const char* ssid, const char* password);
        void start();
        void handle_wifi();
        constexpr static const WifiState &get_state(void) { return _state;};
    
    private:

        static void _start();
        static void _connect();

        static WifiState _state;

        static wifi_init_config_t _wifi_init_cfg;
        static wifi_config_t _wifi_cfg;

        static void wifi_event_handler(
                void *arg, 
                esp_event_base_t event_base, 
                int32_t event_id, 
                void *event_data);

        static void ip_event_handler(
            void *arg, 
            esp_event_base_t event_base, 
            int32_t event_id, 
            void *event_data);

};