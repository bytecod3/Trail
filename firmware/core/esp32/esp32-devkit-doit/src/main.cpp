/**
 * @file main.cpp
 * @author Edwin Mwiti (emwiti658@gmail.com)
 * @brief This file implements the main logic for handling WIFI and BT connection
 * @version 0.1
 * @date 2025-07-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "pins.h"
#include "globals.h"
#include "FSM.h"
#include "esp_log.h"
#include "wifi-config.h"
#include "files.h"
#include "config.h"
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"


/* function prototypes */
void WIFI_web_server_not_found(AsyncWebServerRequest*);
void WIFI_server_init();

static const char* TAG = "WIFI_MONITOR";        /* tag to use for debug messages */

/* finite state machine variables */
wifi_state_t sm_state = STATE_WIFI_PROVISION_REQUEST;

/* wifi provisioning */
WifiConfig WifiProvisioner;     /*!< to use for provisioning for WIFI */
AsyncWebServer wifi_server(WIFI_SERVER_PORT);

/**
 * JSON file variables 
 * 
 */
JsonDocument wifi_config_doc;
uint8_t credentials_saved = 0;


/**
 * Device Index Page
 */
const char wifi_server_index_html[] PROGMEM = R"rawliteral(

<!DOCTYPE HTML>
<html>
<head>
  <title>Trail Network Config</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head>
    <body>
    <h3> Trail WiFi Configuration</h3>
    <form action="/get">
        <span>WiFi SSID: </span> <input type="text" name="wifi_ssid"> <br><br>
        <span>WiFi Password: </span> <input type="text" name="wifi_password"> <br><br>
    <input type="submit" value="SAVE">
    </form><br>

    </form><br>
</body>
</html>

)rawliteral";

const char wifif_server_success_response[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP LiteEVSE Network Config</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head>
    <body>
     <p>Parameters Saved!</p> <br><br>
     <br><a href="/network">Return to Home Page</a>
</body>
</html>
)rawliteral";

uint64_t ESP_get_id() {
    return ESP.getEfuseMac();
}

void JSON_file_create(const String WIFI_name, const String WIFI_password) {
    wifi_config_doc["device_id"] = ESP_get_id();
    wifi_config_doc["wifi_name"] = WIFI_name;
    wifi_config_doc["wifi_password"] = WIFI_password;

    
    char wifi_config_json_string[128];
    serializeJson(wifi_config_doc, wifi_config_json_string);

    writeFile(LittleFS, saved_networks_file_path, wifi_config_json_string);

}

/**
 * @brief This function initalizes the web server to use for WIFI provisioning to the device 
 * 
 */
void WIFI_server_init() {
    // set handlers
    // todo: use const char variables for URLs

    #if DEBUG
        ESP_LOGI(TAG, "Initializing web server...");
    #endif

    wifi_server.on("/network", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", wifi_server_index_html);
    });

    wifi_server.on("/get", HTTP_GET, [](AsyncWebServerRequest* request) {
        String inputMessage;
        String inputParam;

        String config_wifi_name;
        String config_wifi_psd;

        // Wi-Fi SSID (ipaddress/get?wifi-ssid=12345
        if(request->hasParam("wifi_ssid")) {

            config_wifi_name = request->getParam("wifi_ssid")->value();

            if(config_wifi_name != "") { /* SSID must exist */
                inputParam = config_wifi_name;
            }
        }

        if(request->hasParam("wifi_password")) { /* Wi-Fi password */
            config_wifi_psd = request->getParam("wifi_password")->value();

            if (config_wifi_psd != "") {
                inputParam = config_wifi_psd;
            }
        }

        /* save credentials to memory */
        JSON_file_create(config_wifi_name, config_wifi_psd);

        /* crdentials have been saved here, so update the saved bit */
        credentials_saved = 1;

        JsonDocument doc;
        readFile(LittleFS, config_file_path);
        deserializeJson(doc, file_data_buffer);
        doc["wifi_configured"] = credentials_saved;

        char wifi_config_string[32];
        serializeJson(doc, wifi_config_string);
        writeFile(LittleFS, config_file_path, wifi_config_string);

        // todo: update screen

        request->send(200, "text/html", wifif_server_success_response);
    });

    // begin server
    wifi_server.onNotFound(WIFI_web_server_not_found);
    wifi_server.begin();
     ESP_LOGI(TAG, "Provisioning server started, waiting for config parameters...");

}

/**
 * @brief This function runs if the web provisioning web server is not found
 * 
 * @param request pointer to a AsyncWebServerRequest
 */
void WIFI_web_server_not_found(AsyncWebServerRequest* request) {
    request->send(404, "text/plain", "Trail server not found");
}

/* wifi connection timing variables  */
unsigned long wifi_provision_start_timer = 0;
unsigned long wifi_connect_start_time = 0;



/* task handles */
TaskHandle_t wifi_monitor_task_handle;
TaskHandle_t get_state_from_queue_task_handle;
TaskHandle_t bluetooth_monitor_task_handle;
TaskHandle_t watchdog_timer_task_handle;

/* message queue */
QueueHandle_t wifi_state_queue_handle;

/* Tasks function prototypes */
void x_wifi_connect(void *);
void x_wifi_state_callback(void*);

/**
 * @brief This function mounts the LittleFS filesystem on ESP32
 * 
 */
void LittleFS_mount() {

    #if DEBUG 
        ESP_LOGI(TAG, "Mounting Little FS");
    #endif

    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
        #if DEBUG
            ESP_LOGE(TAG, "LittleFS mount failed. Formatting...");
        #endif

        if (LittleFS.format()) {
            #if DEBUG
                ESP_LOGI(TAG, "Little FS successfully formatted");
            #endif
        } else {
            #if DEBUG
                ESP_LOGE(TAG, "Error formatting Little FS");
            #endif
        }

        if (!LittleFS.begin()) {
            #if DEBUG
                ESP_LOGE(TAG, "Little FS could not be mounted after formatting");
            #endif
        } else {
            #if DEBUG
                ESP_LOGI(TAG, "Little FS successfully mounted after formatting");
            #endif
        }
    } else {
        #if DEBUG
            ESP_LOGI(TAG, "Little FS mounted successfully");
        #endif
    }
}

/**
 * @brief This function initializes the file operation functions for WIFI subsystem
 * 
 */
void file_operations_init() {
    File wifi_root_path  = LittleFS.open(wificonfig_folder_path);

    if(!wifi_root_path) {
        #if DEBUG
            ESP_LOGI(TAG, "/wificonfig directory does not exist. Creating");
        #endif
        createDir(LittleFS, wificonfig_folder_path);
    } else {
        listDir(LittleFS, wificonfig_folder_path, 3);

        /* check if relevant files exist and/or create them */
        File file = LittleFS.open(config_file_path);
        if(!file) {
            #if DEBUG
                ESP_LOGI(TAG, "config.ini file does not exist, creating file...");
            #endif

            writeFile(LittleFS, config_file_path, ""); /* just to initialize the file */

            #if DEBUG
                 ESP_LOGI(TAG, "config.ini file created");
            #endif
            
        } else {
            #if DEBUG
                ESP_LOGI(TAG, "config.ini file already exists");
            #endif

            /**
             * 
             * Now if the config.ini file exists, we need to read its contents.
             * since data here is stored as JSON, there is a variable called "wifi_configured"
             * it is set to 1 if this device has been connected to a wifi network before (see WIFI_server_init())
             * it is 0 if no WIFI network has been configured before
             * 
             */
            readFile(LittleFS, config_file_path);
            #if DEBUG
                ESP_LOGI(TAG, "config file contents: %s", file_data_buffer);
            #endif

            if(strcmp(file_data_buffer, "") == 0) {
                #if DEBUG
                    ESP_LOGI(TAG, "WIFI configured bit does not exist");
                #endif

                /* create wifi configuration bit */
                JsonDocument doc;
                doc["wifi_configured"] = 0;
                char wifi_configured_string[50];
                serializeJson(doc, wifi_configured_string);
                writeFile(LittleFS, config_file_path, wifi_configured_string);

                /* change state */
                sm_state = STATE_WIFI_PROVISION_REQUEST;
            } else {
                /* here the wifi_config bit exists */
                #if DEBUG
                    ESP_LOGI(TAG, "WIFI config bit exists");
                #endif

                JsonDocument doc;
                uint8_t wifi_conf_check_bit;
                readFile(LittleFS, config_file_path);
                deserializeJson(doc, file_data_buffer);
                wifi_conf_check_bit = doc["wifi_configured"];

                if(wifi_conf_check_bit == 0) {
                    sm_state = STATE_WIFI_PROVISION_REQUEST;
                } else {
                    sm_state = STATE_WIFI_CONNECT;
                }


            }
             
        }
    }

}

/**
 * @brief WIFI connection task
 * 
 * @param pv_parameters 
 */
void x_wifi_connect(void* pv_parameters) {
    for (;;) {

        switch (sm_state) {
            case STATE_WIFI_PROVISION_REQUEST:
                WifiProvisioner.WIFI_create_access_point();
                WIFI_server_init();

                wifi_provision_start_timer = millis();
                sm_state = STATE_WIFI_WAITING_PROVISION;

                break;

            case STATE_WIFI_WAITING_PROVISION:

                if(credentials_saved) {
                    #if DEBUG
                        ESP_LOGI(TAG, "Credentials exist. Connecting...");
                    #endif

                    sm_state = STATE_WIFI_CONNECT;
                } else {
                    /* check for provision timeout */
                    if( (millis() - wifi_provision_start_timer) >= WIFI_CONNECTION_TIMEOUT) {
                        sm_state = STATE_WIFI_PROVISION_TIMEOUT;
                    }
                }

                break;
        
            default:
                break;
        }

        /* send the current state to queue even if it is global */
        // todo: check return type from QUEUE send 
        xQueueSend(wifi_state_queue_handle, &sm_state, portMAX_DELAY);

        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void x_wifi_state_callback(void* pvParameters) {
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}


/**
 * 
 * @brief This function fetches the current state from the wifi_state_queue and converts it to a readable string 
 * 
 */
void x_get_state_from_queue(void* pvParameters) {
    wifi_state_t rcvd_state;

    for (;;) {
        xQueueReceive(wifi_state_queue_handle, &rcvd_state, portMAX_DELAY);

        #if DEBUG
            ESP_LOGI(TAG, "current state: %s", convert_state_to_str(rcvd_state));
        #endif
    }
    
}

void setup() {
    Serial.begin(BAUDRATE);
    delay(50); /* delay to give time to serial to boot OK */
    esp_log_level_set(TAG, ESP_LOG_INFO);

    /* mount files sytem */
    LittleFS_mount();

    /* initialize files */
    // deleteFile(LittleFS, config_file_path);
    // deleteFile(LittleFS, saved_networks_file_path);
    file_operations_init();

    /**
     * 
     * Create queues
     * 
     */
    wifi_state_queue_handle = xQueueCreate(SIZE_OF_WIFI_STATE_QUEUE, sizeof(wifi_state_t));
    if (wifi_state_queue_handle != NULL) {
        #if DEBUG
            ESP_LOGI(TAG, "wifi_state_queue created OK.");
        #endif
    } else {
        #if DEBUG
            ESP_LOGI(TAG, "wifi_state_queue failed to create.");
        #endif
    }

    /**
     * Create tasks 
     * 
     */
    #if DEBUG 
        ESP_LOGI(TAG, "Creating tasks...");
    #endif

    uint8_t app_core_id = 1;

    BaseType_t res = xTaskCreatePinnedToCore(x_wifi_connect, "x_wifi_connect", WIFI_MONITOR_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &wifi_monitor_task_handle, app_core_id);
    if(res == pdPASS) {
        #if DEBUG 
            ESP_LOGI(TAG, "x_wifi_connect task created OK.");
        #endif
    } else {
        #if DEBUG
            ESP_LOGE(TAG, "x_wifi_connect task creation failed.");
        #endif
    }

    res = xTaskCreatePinnedToCore(x_get_state_from_queue, "x_get_state_from_queue", WIFI_MONITOR_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &get_state_from_queue_task_handle, app_core_id);
    if(res == pdPASS) {
        #if DEBUG
            ESP_LOGI(TAG, "x_get_state_from_queue task created OK.");
        #endif
    } else {
        #if DEBUG
            ESP_LOGE(TAG, "x_get_state_from_queue task creation failed.");
        #endif
    }


}

void loop() {

}
