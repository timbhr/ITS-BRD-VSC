/**
 ******************************************************************************
 * @file    measurement.h
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Measurement functionality
 * @date    November 2026
 ******************************************************************************
 */

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Sets the measurement to a defined state. Called at program start and
 * after press of S6.
 *
 * @param count Current count value
 * @param now Current timestamp in timer ticks
 */
void meas_reset(int32_t count, uint64_t now);

/**
 * @brief Calculates angle and velocity in the background. Must be called in
 * every loop iteration. Recalculates only if a new phase change occurred.
 * The velocity is the average since the last output (see meas_output_due()).
 *
 * @param count Current count value
 * @param count_ts Timestamp of last phase change in timer ticks
 */
void meas_update(int32_t count, uint64_t count_ts);

/**
 * @brief Checks whether the current values should be output now and starts a
 * new measurement window if so.
 *
 * @param now Current timestamp in timer ticks
 *
 * @return true if values should be output: at least 300 ms since last output
 * and a phase change occurred, or 3 s passed without phase change (velocity
 * is then set to 0). false otherwise.
 */
bool meas_output_due(uint64_t now);

/**
 * @brief Get the current angle in degrees.
 *
 * @return The current angle in degrees
 */
double meas_get_angle(void);

/**
 * @brief Get the current velocity in degrees per second.
 *
 * @return The current velocity in degrees per second
 */
double meas_get_velocity(void);

#endif // MEASUREMENT_H

// EOF
