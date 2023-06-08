#include "mqtt_manager.h"

#define MQTT_BROKER_URI "mqtt://broker.hivemq.com"
#define MQTT_TOPIC "/__GK__/hello"

//Starts the mqtt client and assigning the broker uri.
void MQTTManager::start() 
{    
    esp_mqtt_client_config_t mqtt_config = {
        .broker = {
            .address = {
                .uri = MQTT_BROKER_URI,
            },
        },
    };

    esp_mqtt_client_handle_t _client = esp_mqtt_client_init(&mqtt_config);

    esp_mqtt_client_register_event(_client, (esp_mqtt_event_id_t)ESP_EVENT_ANY_ID, mqtt_event_handler, _client);
    if (esp_mqtt_client_start(_client) == ESP_OK) {
        ESP_LOGI(TAG, "Started");
        _running = true;
    }
    else {
        ESP_LOGI(TAG, "Starting Failed");
        _running = false;
    }

}

bool MQTTManager::isRunning() {
    return _running;
}

//Handles mqtt events and incoming data
//Sends back "pong" when receiving "ping"
void MQTTManager::mqtt_event_handler(
            void *arg,
            esp_event_base_t event_base,
            int32_t event_id,
            void *event_data) {

    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id = 0;

    switch (event->event_id) 
    {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_subscribe(client, MQTT_TOPIC, 0);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
            break;

        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            break;

        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;

        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            // Handle received MQTT data
            // event->topic contains the topic, and event->data contains the payload
            if (strcmp(event->data, "ping") == 0) {
                ESP_LOGI(TAG, "ping received from topic");
                msg_id = esp_mqtt_client_publish(client, MQTT_TOPIC, "pong", 0, 1, 0);
                ESP_LOGI(TAG, "Sent pong : %d", msg_id);
            }
            break;

        default:
            break;
    }
}
 