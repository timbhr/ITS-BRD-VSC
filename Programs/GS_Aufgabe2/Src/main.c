/**
 ******************************************************************************
 * @file    main.c
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Main program for incremental encoder
 * @date    November 2026
 ******************************************************************************
 */

#include "init.h"
#include "LCD_GUI.h"

#include "display_output.h"
#include "err_handler.h"
#include "input.h"
#include "led_output.h"
#include "measurement.h"
#include "phase_counter.h"
#include "timekeeping.h"
#include "types.h"
#include <stdbool.h>


int main(void) {
    initITSboard();
    GUI_init(DEFAULT_BRIGHTNESS);

    time_init();
    led_init();
    disp_init();
    pc_reset();
    err_clear();
    meas_reset(0, time_now());

        while (1) {
        // read inputs
        time_update();
        PhaseSample sample = input_read_phase();
        bool s6_pressed = input_is_s6_pressed();

        // process
        if (s6_pressed) {
            pc_reset();
            err_clear();
            meas_reset(0, time_now());
            err_handle(disp_set_values(0.0, 0.0));
        } else if (!err_is_active()) {
            int pc_result = pc_update(sample);
            err_handle(pc_result);

            if (!err_is_active()) {
                int32_t count = pc_get_count();
                uint64_t count_ts = pc_get_count_timestamp();
                uint64_t now = time_now();

                bool new_values = meas_update(count, count_ts, now);

                if (new_values) {
                    double angle = meas_get_angle();
                    double velocity = meas_get_velocity();

                    int disp_result = disp_set_values(angle, velocity);
                    err_handle(disp_result);
                }
            }
        }

        // write outputs
        led_show_count(pc_get_count());
        led_show_direction(pc_get_direction());
        led_show_error(err_is_active());
        disp_step();
    }
}

// EOF