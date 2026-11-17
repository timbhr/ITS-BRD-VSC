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
#define TICKS_PER_S (TICKS_PER_MS * 1000U)

#define MIN_INTERVAL (300U * TICKS_PER_MS)  // 300 ms
#define MAX_INTERVAL (3000U * TICKS_PER_MS) // 3 s

// start of the current measurement window (= state at last output)
static int32_t start_count = 0;
static uint64_t start_timestamp = 0;

// latest phase change seen by meas_update()
static int32_t last_count = 0;
static uint64_t last_change_ts = 0;

static uint64_t last_output_time = 0; // time of last output
static double angle = 0.0;            // degrees
static double velocity = 0.0;         // degrees per second

void meas_reset(int32_t count,  // NOLINT (bugprone-easily-swappable-parameters)
                uint64_t now) { // NOLINT (bugprone-easily-swappable-parameters)
   start_count = count;
   start_timestamp = now;
   last_count = count;
   last_change_ts = now;
   last_output_time = now;
   angle = (double)count * DEG_PER_COUNT;
   velocity = 0.0;
}

void meas_update(int32_t count,       // NOLINT (bugprone-easily-swappable-parameters)
                 uint64_t count_ts) { // NOLINT (bugprone-easily-swappable-parameters)
   // only recalculate if there is a new phase change
   if (count_ts <= last_change_ts) {
      return;
   }

   last_count = count;
   last_change_ts = count_ts;

   angle = (double)count * DEG_PER_COUNT;

   // average velocity since start of the window, dt is always > 0 here
   double dt_s = (double)(count_ts - start_timestamp) / (double)TICKS_PER_S;
   velocity = (double)(count - start_count) * DEG_PER_COUNT / dt_s;
}

bool meas_output_due(uint64_t now) {
   uint64_t elapsed = now - last_output_time;

   // rule 1: at most every 300 ms
   if (elapsed < MIN_INTERVAL) {
      return false;
   }

   bool changed = (last_change_ts > start_timestamp);

   // rule 2: without phase change wait up to 3 s
   if (!changed && elapsed < MAX_INTERVAL) {
      return false;
   }

   if (!changed) {
      velocity = 0.0; // standstill
   }

   // start a new window at the latest phase change
   start_count = last_count;
   start_timestamp = last_change_ts;
   last_output_time = now;
   return true;
}

double meas_get_angle(void) { return angle; }

double meas_get_velocity(void) { return velocity; }

// EOF
