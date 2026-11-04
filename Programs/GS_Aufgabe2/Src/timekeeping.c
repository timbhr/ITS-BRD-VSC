/**
 ******************************************************************************
 * @file    timekeeping.c
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Timekeeping functions for incremental encoder
 * @date    November 2026
 ******************************************************************************
 */

#include "timekeeping.h"
#include "timer.h"

static uint32_t last_ticks;
static uint64_t total_ticks;

void time_init(void) {
   initTimer();
   last_ticks = getTimeStamp();
   total_ticks = 0;
}

void time_update(void) {
    uint32_t current = getTimeStamp();
    uint32_t diff = current - last_ticks;

    total_ticks += diff;
    last_ticks = current;
}

uint64_t time_now(void) {
    return total_ticks;
}
// EOF
