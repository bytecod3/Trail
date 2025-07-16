/**
 * @file main.cpp
 * @author Edwin Mwiti (emwiti658@gmail.com)
 * @brief This file implements the main logic for handling WIFI and BT connectiongf
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

#define BAUDRATE 115200

static const char* TAG = "WIFI_MONITOR";        /* tag to use for debug messages */

/* finite state machine variables */
wifi_state_t sm_State = STATE_WIFI_WAITING_PROVISION;

/* wifi connection timing variables  */
unsigned long provision_start_timer = 0;
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
 * @brief WIFI connection task
 * 
 * @param pv_parameters 
 */
void x_wifi_connect(void* pv_parameters) {
    for (;;) {

        ESP_LOGI(TAG, "connecting to WIFI");

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void x_wifi_state_callback(void* pvParameters) {
    for (;;) {

    }
}

void setup() {
    Serial.begin(BAUDRATE);
    delay(50);
    esp_log_level_set(TAG, ESP_LOG_INFO);

    /**
     * Create tasks 
     * 
     */
    ESP_LOGI(TAG, "Creating tasks...");
    uint8_t app_core_id = 1;
    BaseType_t res = xTaskCreatePinnedToCore(x_wifi_connect, "x_wifi_connect", WIFI_MONITOR_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &wifi_monitor_task_handle, app_core_id);

    if(res == pdPASS) {
        ESP_LOGI(TAG, "x_wifi_connect task created OK.");
    } else {
        ESP_LOGE(TAG, "x_wifi_connect task creation failed.");
    }

    res = xTaskCreatePinnedToCore(x_wifi_connect, "x_wifi_connect", WIFI_MONITOR_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &wifi_monitor_task_handle, app_core_id);

    if(res == pdPASS) {
        ESP_LOGI(TAG, "x_wifi_connect task created OK.");
    } else {
        ESP_LOGE(TAG, "x_wifi_connect task creation failed.");
    }

}

void loop() {

}
