/*
 * @file keypad.c
 * @brief This file implements keypad routines declared in keypad.h
 * @author Edwin Mwiti
 * @date Jul 31, 2025
 *
 */

#include "keypad.h"

uint16_t keypad_cols[3] = {
		KBD_COL_A_Pin,
		KBD_COL_B_Pin,
		KBD_COL_C_Pin,
};

uint16_t keypad_rows[3] = {
		KBD_ROW_A_Pin,
		KBD_ROW_B_Pin,
		KBD_ROW_C_Pin
};

/**
 * This function returns the number of columns that this keypad matrix has
 */
static uint8_t Keypad_get_num_cols (Keypad_type_t instance) {
	return instance->num_cols;
}

/**
 * @brief This function scans the keypad for key presses
 */
char Keypad_scan(Keypad_type_t instance) {
	/*
	 * for each column, write column low,
	 * 	for each row, read the input
	 */
	uint8_t n_cols = Keypad_get_num_cols(instance);
	for(uint8_t i = 0; i < n_cols; i++) { // column scan
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState)

	}
}


/**
 * @brief This function initializes the keypad structure
 */
void Keypad_initialise(Keypad_type_t instance) {
	instance->num_cols = 3;
	instance->num_rows = 3;

	instance->Keypad_get_num_cols = Keypad_get_num_cols;
	instance->Keypad_scan = Keypad_scan;

}

