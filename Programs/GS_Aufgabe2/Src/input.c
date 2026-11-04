/**
 ******************************************************************************
 * @file    input.c
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Input handling for incremental encoder
 * @date    November 2026
 ******************************************************************************
 */

#include "input.h"
#include "timekeeping.h"
#include "stm32f429xx.h"

#define S6_PIN 6

PhaseSample input_read_phase(void) {
    uint32_t idr = GPIOF->IDR; // Read register

    uint32_t a = (idr >> 0) & 1U; // Canal A to PF0, NOLINT
    uint32_t b = (idr >> 1) & 1U; // Canal B to PF1, NOLINT

    PhaseSample sample;

    if (a == 0 && b == 0) {
        sample.phase = PHASE_A;
    } else if (a == 1 && b == 0) {
        sample.phase = PHASE_B;
    } else if (a == 1 && b == 1) {
        sample.phase = PHASE_C;
    } else { // a == 0 && b == 1
        sample.phase = PHASE_D;
    }

    sample.timestamp = time_now();
    return sample;
}

bool input_is_s6_pressed(void) {
    uint32_t s6 = (GPIOF->IDR >> S6_PIN) & 1U; // S6 to PF6, NOLINT
    return s6 == 0; // low-active: 0 = pressed
}

// EOF
