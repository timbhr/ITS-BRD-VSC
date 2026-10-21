/**
 * @file errorcodes.h
 * @author Tim Behrens, Nishan Khatiwada
 * @brief Aufgabe 1
 *        Error codes for the RPN calculator on the ITS-Board.
 * @date Oktober 2026
 * 
 */

#ifndef ERRORCODES_H
#define ERRORCODES_H

#define ERR_OK 0 // Success
#define ERR_STACK_OVERFLOW (-1) // The stack is full
#define ERR_STACK_UNDERFLOW (-2) // Fewer than 2 values on the stack / The stack is empty
#define ERR_OUT_OF_RANGE (-3) // The result does not fit in an int
#define ERR_DIV_BY_0 (-4) // The first (top) value is 0
#define ERR_OVERFLOW_DURING_INPUT (-5) // Overflow during input of a number
#define ERR_UNEXPECTED_INPUT (-6) // An unexpected command / button was encountered

#endif // ERRORCODES_H