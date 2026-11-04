/**
 ******************************************************************************
 * @file    test.c
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Tests for the program (without encoder hardware)
 * @date    November 2026
 ******************************************************************************
 */

#include "test.h"
#include "err_handler.h"
#include "lcd.h"
#include "measurement.h"
#include "phase_counter.h"
#include "timer.h"
#include "types.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define FONT_SIZE 16
#define LINE_LEN 40
#define TOLERANCE 1e-6

#define TICKS_PER_MS ((uint64_t)TICKS_PER_US * 1000U)

#define EXPECT_ERR 99 /* marker in expected table: phase skipped */

static int passed = 0;
static int failed = 0;
static unsigned int fail_line = 2; /* lines 0 and 1: summary */
static char line_buf[LINE_LEN];

/* ---------- helpers ---------- */

static void check(bool condition, const char *name) {
    if (condition) {
        passed++;
    } else {
        failed++;
        snprintf(line_buf, sizeof(line_buf), "FAIL: %s", name);
        lcdGotoXY(0, (POINT)fail_line);
        lcdPrintS(line_buf);
        fail_line++;
    }
}

static bool near(double a, double b) {
    double d = a - b;
    return (d < TOLERANCE) && (d > -TOLERANCE);
}

static int feed(Phase phase, uint64_t timestamp) {
    PhaseSample sample = {phase, timestamp};
    return pc_update(sample);
}

/* ---------- phase_counter ---------- */

static void test_forward(void) {
    pc_reset();
    int err = feed(PHASE_A, 0);
    err |= feed(PHASE_B, 1);
    err |= feed(PHASE_C, 2);
    err |= feed(PHASE_D, 3);
    err |= feed(PHASE_A, 4);

    check(err == ERR_OK, "forward no error");
    check(pc_get_count() == 4, "forward count");
    check(pc_get_direction() == DIR_FORWARD, "forward direction");
}

static void test_backward(void) {
    pc_reset();
    int err = feed(PHASE_A, 0);
    err |= feed(PHASE_D, 1);
    err |= feed(PHASE_C, 2);
    err |= feed(PHASE_B, 3);
    err |= feed(PHASE_A, 4);

    check(err == ERR_OK, "backward no error");
    check(pc_get_count() == -4, "backward count");
    check(pc_get_direction() == DIR_BACKWARD, "backward direction");
}

static void test_no_change(void) {
    pc_reset();
    feed(PHASE_B, 0);
    feed(PHASE_B, 1);
    feed(PHASE_B, 2);

    check(pc_get_count() == 0, "no change count");
    check(pc_get_direction() == DIR_UNKNOWN, "no change direction");
}

static void test_first_sample(void) {
    /* first sample after reset must not be compared */
    pc_reset();
    int err = feed(PHASE_C, 0);
    check(err == ERR_OK, "first sample no error");
    check(pc_get_count() == 0, "first sample count");

    feed(PHASE_D, 1);
    check(pc_get_count() == 1, "first sample then step");
}

static void test_timestamp(void) {
    pc_reset();
    feed(PHASE_A, 100);
    feed(PHASE_B, 200);
    feed(PHASE_B, 300); /* no change: timestamp must stay 200 */

    check(pc_get_count_timestamp() == 200, "timestamp of last change");
}

static void test_all_transitions(void) {
    /* expected count after (old -> new), from table 1 of the concept */
    static const int expected[4][4] = {
        /* new:  A           B           C           D          */
        {0,          1,          EXPECT_ERR, -1},         /* old A */
        {-1,         0,          1,          EXPECT_ERR}, /* old B */
        {EXPECT_ERR, -1,         0,          1},          /* old C */
        {1,          EXPECT_ERR, -1,         0},          /* old D */
    };

    bool all_ok = true;

    for (int old_p = 0; old_p < 4; old_p++) {
        for (int new_p = 0; new_p < 4; new_p++) {
            pc_reset();
            feed((Phase)old_p, 0);
            int err = feed((Phase)new_p, 1);

            if (expected[old_p][new_p] == EXPECT_ERR) {
                all_ok = all_ok && (err == ERR_PHASE_SKIPPED);
            } else {
                all_ok = all_ok && (err == ERR_OK) &&
                         (pc_get_count() == expected[old_p][new_p]);
            }
        }
    }

    check(all_ok, "all 16 transitions");
}

/* ---------- err_handler ---------- */

static void test_error_handler(void) {
    err_clear();
    err_handle(ERR_OK);
    check(!err_is_active(), "err OK has no effect");

    err_handle(ERR_PHASE_SKIPPED);
    check(err_is_active(), "err activated");
    check(err_get_code() == ERR_PHASE_SKIPPED, "err code stored");

    err_handle(ERR_OK);
    check(err_is_active(), "err OK does not clear");

    err_handle(ERR_DISPLAY_BUFFER);
    check(err_get_code() == ERR_PHASE_SKIPPED, "first error kept");

    err_clear();
    check(!err_is_active(), "err cleared");
}

/* ---------- measurement ---------- */

static void test_meas_too_early(void) {
    meas_reset(0, 0);
    bool upd = meas_update(10, 100 * TICKS_PER_MS, 200 * TICKS_PER_MS);
    check(!upd, "meas < 300 ms no update");
}

static void test_meas_full_revolution(void) {
    /* 1200 steps within 100 ms -> 360 deg, 3600 deg/s */
    meas_reset(0, 0);
    bool upd = meas_update(1200, 100 * TICKS_PER_MS, 300 * TICKS_PER_MS);

    check(upd, "meas update after 300 ms");
    check(near(meas_get_angle(), 360.0), "meas angle 360");
    check(near(meas_get_velocity(), 3600.0), "meas velocity 3600");
}

static void test_meas_backward(void) {
    /* -300 steps within 1 s -> -90 deg, -90 deg/s */
    meas_reset(0, 0);
    meas_update(-300, 1000 * TICKS_PER_MS, 1000 * TICKS_PER_MS);

    check(near(meas_get_angle(), -90.0), "meas angle negative");
    check(near(meas_get_velocity(), -90.0), "meas velocity negative");
}

static void test_meas_standstill(void) {
    meas_reset(0, 0);
    bool upd1 = meas_update(0, 0, 500 * TICKS_PER_MS);
    bool upd2 = meas_update(0, 0, 3000 * TICKS_PER_MS);

    check(!upd1, "meas standstill waits");
    check(upd2, "meas update after 3 s");
    check(near(meas_get_velocity(), 0.0), "meas standstill velocity 0");
}

/* ---------- main test entry ---------- */

void test_run_all(void) {
    passed = 0;
    failed = 0;
    fail_line = 2;

    lcdSetFont(FONT_SIZE);

    test_forward();
    test_backward();
    test_no_change();
    test_first_sample();
    test_timestamp();
    test_all_transitions();

    test_error_handler();

    test_meas_too_early();
    test_meas_full_revolution();
    test_meas_backward();
    test_meas_standstill();

    /* leave modules in a clean state */
    pc_reset();
    err_clear();
    meas_reset(0, 0);

    snprintf(line_buf, sizeof(line_buf), "Tests: %d passed, %d failed",
             passed, failed);
    lcdGotoXY(0, 0);
    lcdPrintS(line_buf);
}

// EOF
