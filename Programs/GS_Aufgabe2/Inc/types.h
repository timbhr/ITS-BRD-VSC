/**
 ******************************************************************************
 * @file    types.h
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Types for incremental encoder
 * @date    November 2026
 ******************************************************************************
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

/**
 * @brief Phases of incremental encoder, a --> b --> c --> d
 */
typedef enum {
    PHASE_A = 0,
    PHASE_B = 1,
    PHASE_C = 2,
    PHASE_D = 3,
} Phase;

/**
 * @brief Structure for storing phase samples
 */
typedef struct {
    Phase phase;
    uint64_t timestamp; // time in timer ticks (90 ticks = 1 µs)
} PhaseSample;

/**
 * @brief Direction of incremental encoder
 */
typedef enum {
    DIR_UNKNOWN,
    DIR_FORWARD,
    DIR_BACKWARD,
} Direction;

#endif // TYPES_H

// EOF