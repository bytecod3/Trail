/*
 * button.c
 *
 *  Created on: Jul 12, 2025
 *      Author: edwin mwiti
 */

#include "button.h"
#include <stdint.h>

struct Button {
	uint8_t _pin;
	uint8_t (*func)(void);
};


