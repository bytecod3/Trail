
/**
 * @file globals.h
 * @author Edwin Mwiti (emwiti658@gmail.com)
 * @brief This file defines the global definitions for various usages
 * @version 0.1
 * @date 2025-07-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef GLOBALS_H
#define GLOBALS_H

#define BAUDRATE                        115200  /*!< ESP32 Serial monitor baudrate */

#define WIFI_SERVER_PORT                80      /*!< port to use when creating WIFI web server */
#define WIFI_MONITOR_STACK_SIZE         1024    /*!< WIFI monitor stack size in words */
#define WIFI_CONNECTION_TIMEOUT         300000  /*!< timeout for wifi connection - 5 min */

#endif