/**
 ******************************************************************************
 * @file    arithops.c
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 1
 *          Arithmetic operations for the RPN calculator on the ITS-Board.
 * @date    Oktober 2026
 ******************************************************************************
 */
 
#include <limits.h>
#include <stdbool.h>
#include "arithops.h"
#include "stackops.h"
#include "errorcodes.h"


int arith_add(void) {
    int summand1;
    int summand2;
    if (pop(&summand1) != ERR_OK || pop(&summand2) != ERR_OK) {
        return ERR_STACK_UNDERFLOW;
    }

    if ((summand2 > 0 && summand1 > INT_MAX - summand2) || (summand2 < 0 && summand1 < INT_MIN - summand2)) {
        return ERR_OUT_OF_RANGE;
    }

    return push(summand1 + summand2);
}

int arith_sub(void) {
    int subtrahend;
    int minuend;
    if (pop(&subtrahend) != ERR_OK || pop(&minuend) != ERR_OK) {
        return ERR_STACK_UNDERFLOW;
    }

    if ((subtrahend > 0 && minuend < INT_MIN + subtrahend) || (subtrahend < 0 && minuend > INT_MAX + subtrahend)) {
        return ERR_OUT_OF_RANGE;
    }

    return push(minuend - subtrahend);
}

static bool mul_overflows(int factor1, int factor2) {
    if (factor1 == 0 || factor2 == 0) {
        return false; // Multiplication by zero never overflows
    }
    if (factor1 > 0) {
        if (factor2 > 0) {
            return factor1 > INT_MAX / factor2; // factor1 & factor2 are positive
        }
        return factor2 < INT_MIN / factor1; // factor1 is positive, factor2 is negative
    }
    if (factor2 > 0) {
        return factor1 < INT_MIN / factor2; // factor1 is negative, factor2 is positive
    }
    return factor2 < INT_MAX / factor1; // factor1 & factor2 are negative
}

int arith_mul(void) {
    int factor1;
    int factor2;
    if (pop(&factor1) != ERR_OK || pop(&factor2) != ERR_OK) {
        return ERR_STACK_UNDERFLOW;
    }

    if (mul_overflows(factor1, factor2)) {
        return ERR_OUT_OF_RANGE;
    }

    return push(factor1 * factor2);
}

int arith_div(void) {
    int divisor;
    int dividend;

    if (pop(&divisor) != ERR_OK || pop(&dividend) != ERR_OK) {
        return ERR_STACK_UNDERFLOW;
    }

    if (divisor == 0) {
        return ERR_DIV_BY_0;
    }

    if (dividend == INT_MIN && divisor == -1) {
        return ERR_OUT_OF_RANGE; // Unique case where division would overflow
    }

    return push(dividend / divisor); // Push the quotient onto the stack
}