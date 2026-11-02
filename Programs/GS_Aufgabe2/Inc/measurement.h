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

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Sets the measurement to a defined state. Called at program start and after press of S6.
 * 
 * @param count Current count value
 * @param now Current timestamp in timer ticks
 */
void meas_reset(int32_t count, uint64_t now);

/**
 * @brief Updates the measurement.
 * 
 * @param count Current count value
 * @param count_ts Timestamp of last phase change in timer ticks
 * @param now Current timestamp in timer ticks
 *
 * @return true if updated. false if < 300ms since last update, or if no phase change within 3s.
 */
bool meas_update(int32_t count, uint64_t count_ts, uint64_t now);


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