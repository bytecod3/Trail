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
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


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

/**
 * @brief This function initalizes the web server to use for WIFI provisioning to the device 
 * 
 */
void WIFI_server_init() {
    // set handlers
    // todo: use const char variables for URLs
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

        if(request->hasParam("wifi_password")) { // Wi-Fi password
            config_wifi_psd = request->getParam("wifi_password")->value();

            if (config_wifi_psd != "") {
                inputParam = config_wifi_psd;
            }
        }

        request->send(200, "text/html", wifif_server_success_response);
    });

    // begin server
    wifi_server.onNotFound(WIFI_web_server_not_found);
    wifi_server.begin();

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
TaskHandle_t bluetooth_monitor_task_handle;
TaskHandle_t watchdog_timer_task_handle;

/* message queue */
QueueHandle_t wifi_status_queue_handle;

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

            writeFile(LittleFS, config_file_path, "OK"); /* just to initialize the file with some data */

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
             * since data here is stored as JSON, there is a variable called wifi_configured.
             * it is set to 1 if this device has been connected to a wifi network before (see WIFI_server_init())
             * it is 0 if no WIFI network has been configured before
             * 
             */

             
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

        ESP_LOGI(TAG, "connecting to WIFI");
        switch (sm_state) {
            case STATE_WIFI_PROVISION_REQUEST:
                WifiProvisioner.WIFI_create_access_point();
                WIFI_server_init();

                wifi_provision_start_timer = millis();
                sm_state = STATE_WIFI_WAITING_PROVISION;

                break;

            case STATE_WIFI_WAITING_PROVISION:
                

                /* check for provision timeout */
                if( (millis() - wifi_provision_start_timer) >= WIFI_CONNECTION_TIMEOUT) {
                    sm_state = STATE_WIFI_PROVISION_TIMEOUT;
                }

                break;
        
            default:
                break;
        }
        

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void x_wifi_state_callback(void* pvParameters) {
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(200));
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
     * Create tasks 
     * 
     */
    #if DEBUG 
        ESP_LOGI(TAG, "Creating tasks...");
    #endif
    // uint8_t app_core_id = 1;
    // BaseType_t res = xTaskCreatePinnedToCore(x_wifi_connect, "x_wifi_connect", WIFI_MONITOR_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &wifi_monitor_task_handle, app_core_id);

    // if(res == pdPASS) {
    //     ESP_LOGI(TAG, "x_wifi_connect task created OK.");
    // } else {
    //     ESP_LOGE(TAG, "x_wifi_connect task creation failed.");
    // }

    // res = xTaskCreatePinnedToCore(x_wifi_connect, "x_wifi_connect", WIFI_MONITOR_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &wifi_monitor_task_handle, app_core_id);

    // if(res == pdPASS) {
    //     ESP_LOGI(TAG, "x_wifi_connect task created OK.");
    // } else {
    //     ESP_LOGE(TAG, "x_wifi_connect task creation failed.");
    // }

}

void loop() {

}
