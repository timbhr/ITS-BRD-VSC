/**
 ******************************************************************************
 * @file    stackops.c
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 1
 *          Stack operations for the RPN calculator on the ITS-Board.
 * @date    Oktober 2026
 ******************************************************************************
 */

#include <stdio.h>
#include "stackops.h"
#include "errorcodes.h"
#include "display.h"

#define STACK_SIZE 100 // Define the maximum size of the stack
#define INTEGER_STRING_SIZE 12 // Buffer size for an integer's string representation

static int stack[STACK_SIZE]; // Array to hold the stack values
static int top = -1; // Index of the top element in the stack, -1 indicates that the stack is empty 

int push(int value) {
    if (top >= STACK_SIZE - 1) {
        return ERR_STACK_OVERFLOW;
    }
    stack[++top] = value;
    return ERR_OK;
}

int pop(int *value) {
    if (top < 0) {
        return ERR_STACK_UNDERFLOW;
    }
    *value = stack[top--];
    return ERR_OK;
}

static int printer(int index) {
    char value[INTEGER_STRING_SIZE]; // Buffer to hold the string representation of the integer
    snprintf(value, sizeof(value), "%d", stack[index]); // Convert the value at the specified index to a string
    print_stdout(value);
    return ERR_OK;
}

int print_top(void) {
    if (top < 0) {
        return ERR_STACK_UNDERFLOW;
    }
    clear_stdout();
    printer(top);
    return ERR_OK;
}

int print_top3(void) {
    if (top < 0) {
        return ERR_STACK_UNDERFLOW;
    }
    clear_stdout();

    for (int i = top; i >= 0 && i > top - 3; i--) {
       printer(i);

        if (i > 0) {
            print_stdout("\n");
        }
    }
    return ERR_OK;
}

int clear_stk(void) {
    top = -1; // Reset the top index to indicate that the stack is empty
    return ERR_OK;
}

int dpl_top(void) {
    if (top < 0) {
        return ERR_STACK_UNDERFLOW;
    }
    if (top >= STACK_SIZE - 1) {
        return ERR_STACK_OVERFLOW;
    }

    return push(stack[top]);
}

int swap_top(void) {
    if (top < 1) {
        return ERR_STACK_UNDERFLOW;
    }

    int temp = stack[top];
    stack[top] = stack[top - 1];
    stack[top - 1] = temp;

    return ERR_OK;
}