/**
 ******************************************************************************
 * @file    led_output.c
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          LED output functionality
 * @date    November 2026
 ******************************************************************************
 */

#include "led_output.h"
#include "stm32f429xx.h"

#define RESET_SHIFT 16 // BSRR: upper 16 bits reset pins

#define COUNT_MASK 0xFFU // D8-D15 = PD0-PD7

#define LED_D21 (1U << 5) // PE5: error
#define LED_D22 (1U << 6) // PE6: backward
#define LED_D23 (1U << 7) // PE7: forward

void led_init(void) {
    GPIOD->BSRR = COUNT_MASK << RESET_SHIFT;
    GPIOE->BSRR = (LED_D21 | LED_D22 | LED_D23) << RESET_SHIFT;
}

void led_show_count(int32_t count) {
    uint32_t bits = (uint32_t)count & COUNT_MASK; // lower 8 bits
    uint32_t off = ~bits & COUNT_MASK; // the other ones

    GPIOD->BSRR = bits | (off << RESET_SHIFT);
}

void led_show_direction(Direction dir) {
    switch (dir) {
    case DIR_FORWARD:
        GPIOE->BSRR = LED_D23 | (LED_D22 << RESET_SHIFT);
        break;
    case DIR_BACKWARD:
        GPIOE->BSRR = LED_D22 | (LED_D23 << RESET_SHIFT);
        break;
    default: // DIR_UNKNOWN: both off
        GPIOE->BSRR = (LED_D22 | LED_D23) << RESET_SHIFT;
        break;
    }
}

void led_show_error(bool error_active) {
    if (error_active) {
        GPIOE->BSRR = LED_D21;
    } else {
        GPIOE->BSRR = LED_D21 << RESET_SHIFT;
    }
}

// EOF