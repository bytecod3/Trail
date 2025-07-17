
/**
 * @file wifi-config.cpp
 * @author Edwin Mwiti (emwiti658@gmail.com)
 * @brief Implements Wifi connection functions
 * @version 0.1
 * @date 2025-07-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include <Arduino.h>
#include "wifi-config.h"
#include <WiFi.h>
#include <cstdlib>
#include "WiFiManager.h"
#include "config.h"
#include <esp_wifi_types.h>

/**
 * @brief This function sets the WIFI mode
 * 
 * @param m wifi_mode_t mode
 */
void WifiConfig::WIFI_set_mode(wifi_mode_t m)
{
    this->_mode = m;
}

/**
 * @brief This function sete the access point parameters for WIFI
 * 
 * @param s WIFI SSID
 * @param p WIFI password
 * @return true if WIFI parameters passed OK
 * @return false if unclear parameters have been passed to this function
 */
bool WifiConfig::WIFI_set_AP_params(const char *s, const char* p)
{
    if((s != nullptr) && (p != nullptr)) {
        // set SSID and password
        strcpy(this->_sta_name, s);
        strcpy(this->_sta_password, p);
        return true;
    } else {
        return false;
    }
}

/**
 * @brief This function retrieves the WIFI station SSID
 * 
 * @return char* WIFI SSID
 */
char* WifiConfig::WIFI_get_STA_name()
{
    return this->_sta_name;
}

/**
 * @brief This function retrieves the WIFI station password
 * 
 * @return char* WIFI password
 */
char* WifiConfig::WIFI_get_STA_password()
{
    return this->_sta_password;
}

/**
 * @brief This function starts the WIFI provisioner
 * 
 * @return true if a conenction was made successful
 * @return false if a connection failed
 */
bool WifiConfig::WIFI_provision()
{
    // start in station mode
    WiFiClass::mode(this->_mode);
    WiFiManager wm;

    bool connection_response = 0;
    #if DEBUG
        Serial.print("CREATE_AP: "); Serial.println(this->WIFI_get_STA_name());
    #endif
    connection_response = wm.autoConnect(this->_sta_name, this->_sta_password);

    if (connection_response == 0) {
        return false;
    } else {
        return true;
    }
}

/**
 * @brief This function creates a WIFI access point
 * 
 */
void WifiConfig::WIFI_create_access_point() {
    this->WIFI_set_AP_params("trail-wifi",""); /* empty string for NULL password */
    this->WIFI_create_AP();

}

/**
 * @brief This function creates a WIFI access point using the provided parameters 
 * 
 * @return true 
 * @return false 
 */
bool WifiConfig::WIFI_create_AP()
{   
    #if DEBUG
        Serial.println("[+]Creating Access point"); //  todo: use a logger
    #endif

    WiFiClass::mode(WIFI_MODE_AP);
    if(WiFi.softAP(this->WIFI_get_STA_name(), this->WIFI_get_STA_password())) {
        #if DEBUG
            Serial.print("[+]AP created with SSID: "); Serial.println(this->WIFI_get_STA_name());
            Serial.print("[+]AP created with IP: "); Serial.println(WiFi.softAPIP());
        #endif

        return true;
    } else {
        return false;
    }

}