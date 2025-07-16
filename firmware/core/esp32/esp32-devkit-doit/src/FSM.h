
/**
 * @file FSM.h
 * @author Edwin Mwiti (emwiti658@gmail.com)
 * @brief This file declares the Finite State Machine
 * @version 0.1
 * @date 2025-07-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #ifndef FSM_H
 #define FSM_H

 typedef enum {
    STATE_WIFI_WAITING_PROVISION,               /*!< waiting for provision of credentials  */
    STATE_WIFI_CONNECTING,                      /*!< attempting wifi connection  */
    STATE_WIFI_CONNECTED,                       /*!< wifi connected */
    STATE_WIFI_CONNECTION_TIMEOUT,              /*!< wifi connection timeout */
    STATE_WIFI_CONNECTION_ERROR,                /*!< wifi could not connect due to error */
    STATE_WIFI_DISCONNECTED                     /*!< wifi disconnected for some reason - e.g out of range */
 } state_t;

 #endif