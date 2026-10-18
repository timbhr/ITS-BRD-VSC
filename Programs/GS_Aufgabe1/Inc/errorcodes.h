/**
 * @file errorcodes.h
 * @author Tim Behrens
 * @brief Header file for error codes.
 * @date Oktober 2026
 * 
 */

#ifndef ERRORCODES_H
#define ERRORCODES_H

#define ERR_OK 0 // Success
#define ERR_STACK_OVERFLOW (-1) // The stack is full
#define ERR_STACK_UNDERFLOW (-2) // Fewer than 2 values on the stack
#define ERR_OUT_OF_RANGE (-3) // The result does not fit in an int
#define ERR_DIV_BY_0 (-4) // The first (top) value is 0

#endif // ERRORCODES_H