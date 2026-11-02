/**
 ******************************************************************************
 * @file    display_output.h
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Display output functionality
 * @date    November 2026
 ******************************************************************************
 */

#ifndef DISPLAY_OUTPUT_H
#define DISPLAY_OUTPUT_H

/**
 * @brief Initialize display output with default text.
 */
void disp_init(void);

/**
 * @brief Set the values for display output in the buffer.
 * 
 * @param angle Angle in degrees
 * @param velocity Velocity in degrees per second
 *
 * @retval ERR_OK Success
 * @retval ERR_DISPLAY_BUFFER Formatted text exceeds display buffer
 */
int disp_set_values(double angle, double velocity);

/**
 * @brief Update the display output. Outpost atmost 1 character per call.
 */
void disp_step(void);



#endif // DISPLAY_OUTPUT_H

// EOF