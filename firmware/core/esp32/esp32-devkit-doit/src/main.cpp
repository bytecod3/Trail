/**
 * @file main.cpp
 * @author Edwin Mwiti (emwiti658@gmail.com)
 * @brief This file implements the main logic for handling WIFI and BT connections
 * @version 0.1
 * @date 2025-07-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "pins.h"
#include "esp_log.h"

#define BAUDRATE 115200

static const char* TAG = "WIFI_MONITOR";        /* tag to use for debug messages */

TaskHandle_t wifi_monitor_task_handle;
TaskHandle_t bluetooth_monitor_task_handle;
TaskHandle_t watchdog_timer_task_handle;

QueueHandle_t wifi_status_queue_handle;         /* message queue */

void setup() {
    Serial.begin(BAUDRATE);
    delay(50);
    esp_log_level_set(TAG, ESP_LOG_INFO);

    

}

void loop() {

}
