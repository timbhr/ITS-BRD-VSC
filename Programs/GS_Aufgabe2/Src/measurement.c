/**
 ******************************************************************************
 * @file    measurement.c
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Measurement functions for incremental encoder
 * @date    November 2026
 ******************************************************************************
 */
#include "measurement.h"
#include "timer.h"

#define COUNTS_PER_REVOLUTION 1200.0
#define DEG_PER_COUNT (360.0 / COUNTS_PER_REVOLUTION) // 0.3 degrees

#define TICKS_PER_MS ((uint64_t)TICKS_PER_US * 1000U)
#define TICKS_PER_S  (TICKS_PER_MS * 1000U)

#define MIN_INTERVAL (300U * TICKS_PER_MS)  // 300 ms
#define MAX_INTERVAL (3000U * TICKS_PER_MS) // 3 s

static int32_t start_count = 0;      // count at last calculation
static uint64_t start_timestamp = 0; // timestamp of that count
static uint64_t last_calc_time = 0;  // time of last calculation
static double angle = 0.0;           // degrees
static double velocity = 0.0;        // degrees per second

void meas_reset(int32_t count, uint64_t now) { // NOLINT (bugprone-easily-swappable-parameters)
    start_count = count;
    start_timestamp = now;
    last_calc_time = now;
    angle = (double)count * DEG_PER_COUNT;
    velocity = 0.0;
}

bool meas_update(int32_t count, uint64_t count_ts, uint64_t now) { // NOLINT (bugprone-easily-swappable-parameters)
    uint64_t elapsed = now - last_calc_time;

    // rule 1: at most every 300 ms
    if (elapsed < MIN_INTERVAL) {
        return false;
    }

    // a phase change always produces a newer timestamp
    bool changed = (count_ts > start_timestamp);

    // rule 2: without phase change wait up to 3s
    if (!changed && elapsed < MAX_INTERVAL) {
        return false;
    }

    angle = (double)count * DEG_PER_COUNT;

    if (changed) {
        double dt_s = (double)(count_ts - start_timestamp) / (double)TICKS_PER_S;
        velocity = (double)(count - start_count) * DEG_PER_COUNT / dt_s;
        start_timestamp = count_ts;
    } else {
        velocity = 0.0;
    }

    start_count = count;
    last_calc_time = now;
    return true;
}

double meas_get_angle(void) {
    return angle;
}

double meas_get_velocity(void) {
    return velocity;
}

// EOF
