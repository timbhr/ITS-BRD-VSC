/**
 ******************************************************************************
 * @file    input.h
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Input handling
 * @date    November 2026
 ******************************************************************************
 */
#ifndef INPUT_H
#define INPUT_H

#include "types.h"
#include <stdbool.h>

/** 
 * @brief Read the current phase sample.
 * 
 * @return Current phase sample
 */
PhaseSample input_read_phase(void);

/**
 * @brief Check if S6 is pressed.
 * 
 * @return true if S6 is pressed, false otherwise
 */
bool input_is_s6_pressed(void);

#endif // INPUT_H

// EOF