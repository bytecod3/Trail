/*
 * @file keypad.c
 * @brief This file implements keypad routines declared in keypad.h
 * @author Edwin Mwiti
 * @date Jul 31, 2025
 *
 */

#include "keypad.h"


/**
 * This function returns the number of columns that this keypad matrix has
 */
static uint8_t Keypad_get_num_cols (Keypad_type_t instance) {
	return instance->num_cols;
}

/**
 * @brief This function initialises the keypad structure
 */
void Keypad_initialise(Keypad_type_t instance) {
	instance->num_cols = 3;
	instance->num_rows = 3;

	instance->Keypad_get_cols = Keypad_get_num_cols;
}

