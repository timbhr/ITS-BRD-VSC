/**
 ******************************************************************************
 * @file    phase_counter.c
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Phase counter for incremental encoder
 * @date    November 2026
 ******************************************************************************
 */

#include "phase_counter.h"
#include "err_handler.h"
#include <stdbool.h>

#define PHASE_MASK 3 /* modulo 4 for phase difference */

static Phase last_phase = PHASE_A;
static int32_t count = 0;
static uint64_t count_timestamp = 0;
static Direction direction = DIR_UNKNOWN;
static bool first_sample = true;

void pc_reset(void) {
    count = 0;
    direction = DIR_UNKNOWN;
    first_sample = true;
}

int pc_update(PhaseSample sample) {
    if (first_sample) {
        last_phase = sample.phase;
        count_timestamp = sample.timestamp;
        first_sample = false;
        return ERR_OK;
    }

    int diff = ((int)sample.phase - (int)last_phase) & PHASE_MASK;

    switch (diff) {
    case 1: // step forward
        count++;
        direction = DIR_FORWARD;
        count_timestamp = sample.timestamp;
        break;
    case 3: // step backward
        count--;
        direction = DIR_BACKWARD;
        count_timestamp = sample.timestamp;
        break;
    case 2: // phase skipped
        return ERR_PHASE_SKIPPED;
    default: // 0: no change
        break;
    }

    last_phase = sample.phase;
    return ERR_OK;
}

int32_t pc_get_count(void) {
    return count;
}

uint64_t pc_get_count_timestamp(void) {
    return count_timestamp;
}

Direction pc_get_direction(void) {
    return direction;
}

// EOF
