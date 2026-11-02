/**
 ******************************************************************************
 * @file    phase_counter.h
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Phase counter functionality
 * @date    November 2026
 ******************************************************************************
 */

#ifndef PHASE_COUNTER_H
#define PHASE_COUNTER_H

#include "types.h"

/** 
 * @brief Reset the phase counter. First update after reset will not compare for a phase change.
 *        Only the phase will be taken over. The will not change.
 */
void pc_reset(void);

/**
 * @brief Update phase counter with new phase sample.
 * 
 * @param sample New phase sample
 *
 * @retval ERR_OK Success
 * @retval ERR_PHASE_SKIPPED Phase was skipped
 */
int pc_update(PhaseSample sample);

/**
 * @brief Get the current phase count.
 * 
 * @return Current phase count
 */
int32_t pc_get_count(void);

/**
 * @brief Get timestamp of last phaseswitch in timer ticks (90 ticks = 1 µs).
 *
 * @return Timestamp of last phaseswitch
 */
uint64_t pc_get_count_timestamp(void);

/**
 * @brief Get the current direction of the phase counter.
 * 
 * @return Current direction of the phase counter
 */
Direction pc_get_direction(void);

#endif // PHASE_COUNTER_H

// EOF