/*
 * @file: state-machine.h
 * @brief: This file declares the possible state machines for this device
 * @author: Edwin Mwiti
 *
 */

#ifndef SRC_STATE_MACHINE_H_
#define SRC_STATE_MACHINE_H_

 /**
 * @brief Finite state machine states
 * This enum contains all the possible states that the WIFI subsystem can be in
 * at a given time during the operation of the device
 * @typedef wifi_state_t
 */
typedef enum states {
	STATE_WIFI_PROVISION_REQUEST,               /*!< send a request to connect to WIFI */
	STATE_WIFI_WAITING_PROVISION,               /*!< waiting for provision of wifi credentials  */
	STATE_WIFI_PROVISION_TIMEOUT,               /*!< waited too long for credentials */
	STATE_WIFI_CONNECT,                         /*!< start connecting to WIFI */
	STATE_WIFI_CONNECTING,                      /*!< attempting wifi connection  */
	STATE_WIFI_CONNECTED,                       /*!< WIFI connected */
	STATE_WIFI_CONNECTION_TIMEOUT,              /*!< WIFI connection timeout */
	STATE_WIFI_CONNECTION_ERROR,                /*!< WIFI could not connect due to error */

} state_type_t;


#endif /* SRC_STATE_MACHINE_H_ */
