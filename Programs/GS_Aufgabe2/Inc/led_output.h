/**
 ******************************************************************************
 * @file    led_output.h
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          LED output functionality
 * @date    November 2026
 ******************************************************************************
 */

#ifndef LED_OUTPUT_H
#define LED_OUTPUT_H

#include "types.h"
#include <stdint.h>
#include <stdbool.h>


/**
 * @brief Initialize LED output.
 */
void led_init(void);

/**
 * @brief Show count on LEDs as binary on D8-D15
 *
 * @param count The count to display.
 */
void led_show_count(int32_t count);

/**
 * @brief Show direction on LEDs. (D23 = forward, D22 = backward) (off = no direction)
 *
 * @param dir The direction to display.
 */
void led_show_direction(Direction dir);

/**
 * @brief Show error status on LED (D21)
 *
 * @param error_active The error status to display.
 */
void led_show_error(bool error_active);




#endif // LED_OUTPUT_H

// EOF