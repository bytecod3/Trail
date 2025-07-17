
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

 /**
 * @brief Finite state machine states for WIFI connection system
 * 
 * This struct contains all the possible states that the WIFI subsystem can be in 
 * at a given time during the operation of the device 
 *  * 
 * @typedef wifi_state_t
 */
 typedef enum {
    STATE_WIFI_PROVISION_REQUEST,               /*!< send a request to connect to WIFI */
    STATE_WIFI_WAITING_PROVISION,               /*!< waiting for provision of wifi credentials  */
    STATE_WIFI_PROVISION_TIMEOUT,               /*!< waited too long for credentials */
    STATE_WIFI_CONNECTING,                      /*!< attempting wifi connection  */
    STATE_WIFI_CONNECTED,                       /*!< WIFI connected */
    STATE_WIFI_CONNECTION_TIMEOUT,              /*!< WIFI connection timeout */
    STATE_WIFI_CONNECTION_ERROR,                /*!< WIFI could not connect due to error */
    STATE_WIFI_DISCONNECTED                     /*!< WIFI disconnected for some reason - e.g out of range */
 } wifi_state_t;

 #endif