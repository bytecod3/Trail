#include "FSM.h"

const char* convert_state_to_str(wifi_state_t state) {

    switch (state)
    {
        case STATE_WIFI_PROVISION_REQUEST:
            return "STATE_WIFI_PROVISION_REQUEST";
            break;

        case STATE_WIFI_WAITING_PROVISION:
            return "STATE_WIFI_WAITING_PROVISION";
            break;

        case STATE_WIFI_PROVISION_TIMEOUT:
            return "STATE_WIFI_PROVISION_TIMEOUT";
            break;

        case STATE_WIFI_CONNECT:
            return "STATE_WIFI_CONNECTING";
            break;

        case STATE_WIFI_CONNECTING:
            return "STATE_WIFI_CONNECT";
            break;

        case STATE_WIFI_CONNECTED:
            return "STATE_WIFI_CONNECTED";
            break;

        case STATE_WIFI_CONNECTION_TIMEOUT:
            return "STATE_WIFI_CONNECTION_TIMEOUT";
            break;

        case STATE_WIFI_CONNECTION_ERROR:
            return "STATE_WIFI_CONNECTION_ERROR";
            break;

        case STATE_WIFI_DISCONNECTED:
            return "STATE_WIFI_DISCONNECTED";
            break;
    
        default:
            return "STATE_INVALID";
            break;
    }

}