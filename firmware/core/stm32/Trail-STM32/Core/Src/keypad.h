/*
 * @file keypad.h
 * @brief This file declares the keypad class members and constants
 * @author Edwin Mwiti
 * @date Jul 31, 2025
 */

#ifndef SRC_KEYPAD_H_
#define SRC_KEYPAD_H_

#include <stdint.h>

/**
 *
 * @brief structure to represent the keypad
 *
 */
typedef struct Keypad{
	uint8_t num_cols;			/*!< number of columns  */
	uint8_t num_rows;			/*!< number of rows */

	/**
	 * @brief This function scans the keypad for a key press
	 */
	void (*Keypad_scan)(void);

	/**
	 * This function returns the number of rows that this keypad matrix has
	 */
	uint8_t (*Keypad_get_num_cols)(struct Keypad*);

	/**
	 * This function returns the number of columns that this keypad matrix has
	 */
	uint8_t (*Keypad_get_num_rows)(struct Keypad*);
} Keypad;

/*!< pointer to keypad structure */
typedef Keypad* Keypad_type_t;

/**
 * @brief This function scans the keypad for key presses
 */
char Keypad_scan(Keypad_type_t instance);


/**
 * @brief This function initializes the keypad structure
 */
void Keypad_initialise(Keypad_type_t instance);


#endif /* SRC_KEYPAD_H_ */
