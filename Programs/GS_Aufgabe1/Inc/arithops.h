/**
 * @file arithops.h
 * @author Tim Behrens, Nishan Khatiwada
 * @brief Aufgabe 1
 *        Header file for arithmetic operations.
 * @date Oktober 2026
 * 
 */

#ifndef ARITHOPS_H
#define ARITHOPS_H 

/**
 * @brief Takes the top 2 values from the stack, adds them and pushes the result back onto the stack.
 *
 * @retval ERR_OK Success
 * @retval ERR_STACK_UNDERFLOW Fewer than 2 values on the stack
 * @retval ERR_OUT_OF_RANGE The sum does not fit in an int
 */
int arith_add(void);

/**
 * @brief Takes the top 2 values from the stack, subtracts the first (top) value from the second (bottom) value and pushes the result back onto the stack.
 *
 * @retval ERR_OK Success
 * @retval ERR_STACK_UNDERFLOW Fewer than 2 values on the stack
 * @retval ERR_OUT_OF_RANGE The difference does not fit in an int
 */
int arith_sub(void);

/**
 * @brief Takes the top 2 values from the stack, multiplies them and pushes the result back onto the stack.
 *
 * @retval ERR_OK Success
 * @retval ERR_STACK_UNDERFLOW Fewer than 2 values on the stack
 * @retval ERR_OUT_OF_RANGE The product does not fit in an int
 */
int arith_mul(void);

/**
 * @brief Takes the top 2 values from the stack, divides the second (bottom) value by the first (top) value and pushes the result back onto the stack.
 *
 * @retval ERR_OK Success
 * @retval ERR_STACK_UNDERFLOW Fewer than 2 values on the stack
 * @retval ERR_OUT_OF_RANGE The quotient does not fit in an int (Only possible for INT_MIN / -1)
 * @retval ERR_DIV_BY_0 The first (top) value is 0
 */
int arith_div(void);

#endif // ARITHOPS_H
// EOF