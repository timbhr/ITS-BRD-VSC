/**
 ******************************************************************************
 * @file    display_output.c
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Display output functionality
 * @date    November 2026
 ******************************************************************************
 */

#include "display_output.h"
#include "err_handler.h"
#include "lcd.h"
#include <stdio.h>

#define FONT_SIZE 24

#define VALUE_COL   9  // column where values start
#define ANGLE_ROW   0
#define VEL_ROW     1
#define UNIT_COL    20 // column where units start

#define VALUE_WIDTH 10 // must match the width in VALUE_FORMAT
#define VALUE_FORMAT "%10.1f"
#define NUM_VALUES  2  // angle and velocity

#define TOTAL_CHARS (NUM_VALUES * VALUE_WIDTH)

// one line per value, +1 for the terminating '\0'
static char buffer[NUM_VALUES][VALUE_WIDTH + 1];
static unsigned int pos = TOTAL_CHARS; /* nothing to output yet */

void disp_init(void) {
    lcdSetFont(FONT_SIZE);

    lcdGotoXY(0, ANGLE_ROW);
    lcdPrintS("Winkel:");
    lcdGotoXY(UNIT_COL, ANGLE_ROW);
    lcdPrintS("Grad");

    lcdGotoXY(0, VEL_ROW);
    lcdPrintS("Geschw.:");
    lcdGotoXY(UNIT_COL, VEL_ROW);
    lcdPrintS("Grad/s");
}

int disp_set_values(double angle, double velocity) { // NOLINT
    int len_angle = snprintf(buffer[0], sizeof(buffer[0]), VALUE_FORMAT, angle);
    int len_vel = snprintf(buffer[1], sizeof(buffer[1]), VALUE_FORMAT, velocity);

    if (len_angle < 0 || len_angle > VALUE_WIDTH ||
        len_vel < 0 || len_vel > VALUE_WIDTH) {
        pos = TOTAL_CHARS; /* don't print truncated text */
        return ERR_DISPLAY_BUFFER;
    }

    pos = 0; /* start output from first character */
    return ERR_OK;
}

void disp_step(void) {
    if (pos >= TOTAL_CHARS) {
        return; /* everything printed */
    }

    unsigned int line = pos / VALUE_WIDTH;
    unsigned int col = pos % VALUE_WIDTH;

    lcdGotoXY((POINT)(VALUE_COL + col), (POINT)(ANGLE_ROW + line));
    lcdPrintC(buffer[line][col]);

    pos++;
}

// EOF