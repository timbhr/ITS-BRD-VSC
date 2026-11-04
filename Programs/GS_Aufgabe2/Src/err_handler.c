/**
 ******************************************************************************
 * @file    err_handler.c
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Error handling for incremental encoder
 * @date    November 2026
 ******************************************************************************
 */

#include "err_handler.h"

static int active_error = ERR_OK;

void err_handler(int code) {
    if (code != ERR_OK && active_error == ERR_OK) {
        active_error = code;
    }
}

bool err_is_active(void) {
    return active_error != ERR_OK;
}

int err_get_code(void) {
    return active_error;
}

void err_clear(void) {
    active_error = ERR_OK;
}