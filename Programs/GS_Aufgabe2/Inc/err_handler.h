/**
 ******************************************************************************
 * @file    err_handler.h
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 2
 *          Error handling for incremental encoder
 * @date    November 2026
 ******************************************************************************
 */

#ifndef ERR_HANDLER_H
#define ERR_HANDLER_H

#include <stdbool.h>

#define ERR_OK 0 // No error
#define ERR_PHASE_SKIPPED (-1) // phase_counter: Phase was skipped
#define ERR_DISPLAY_BUFFER (-2) // display_out: Formatted text exceeds display buffer

/** 
 * @brief Setting error code and activating error state.
 *        ERR_OK has no effect. Any other activates error state.
 *        Error state will stay active until err_clear() is called.
 *
 * @param code Errorcode
 */
void err_handle(int code);

/**
 * @brief Check if an error is active.
 * 
 * @return true if an error is active, false otherwise
 */
bool err_is_active(void);

/**
 * @brief Get the error code.
 *
 * @retval ERR_OK Success
 * @retval ERR_PHASE_SKIPPED Phase was skipped
 * @retval ERR_DISPLAY_BUFFER Formatted text exceeds display buffer
 */
int err_get_code(void);

/**
 * @brief Clear the error state.
 */
void err_clear(void);

#endif // ERR_HANDLER_H

// EOF