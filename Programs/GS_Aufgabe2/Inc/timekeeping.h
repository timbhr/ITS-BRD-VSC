/**
 ******************************************************************************
 * @file    timekeeping.h
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Timekeeping functionality
 * @date    November 2026
 ******************************************************************************
 */

#ifndef TIMEKEEPING_H
#define TIMEKEEPING_H

#include <stdint.h>

/**
 * @brief Initialize timekeeping.
 */
void time_init(void);

/**
 * @brief Update timekeeping
 *
 * @note Must be called at least once in ~47s, otherwise timer overflows and timekeeping will be incorrect.
 */
void time_update(void);

/**
 * @brief Get current time (Last updated time).
 *
 * @return Current time in timer ticks (90 ticks = 1 µs)
 */
uint64_t time_now(void);

#endif // TIMEKEEPING_H

// EOF