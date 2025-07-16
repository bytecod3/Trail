 /**
 * @file wifi-config.h
 * @author Edwin Mwiti (emwiti658@gmail.com)
 * @brief: This file implements headers for Wifi provisioning
 * @version 0.1
 * @date 2025-07-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef WIFI_PROVISIONER_WIFI_CONFIG_H
#define WIFI_PROVISIONER_WIFI_CONFIG_H

#include <Arduino.h>
#include "esp_wifi_types.h"

class WifiConfig{
private:
    wifi_mode_t _mode;
    char _sta_name[20];
    char _sta_password[20];
    bool _timeout();

public:

    void WIFI_set_mode(wifi_mode_t m);
    bool WIFI_set_AP_params(const char* s, const char* p);
    char* WIFI_get_STA_name();
    char* WIFI_get_STA_password();
    bool WIFI_provision();
    void WIFI_create_access_point();
    bool WIFI_create_AP();
    bool WIFI_check_connect();
    bool WIFI_disconnect();
    bool WIFI_check_STA_AP();
};

#endif //WIFI_PROVISIONER_WIFI_CONFIG_H