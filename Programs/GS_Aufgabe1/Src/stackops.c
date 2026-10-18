#include "stackops.h"
#include "errorcodes.h"
#include "display.h"
#include <stdio.h>

#define STACK_SIZE 100 // Define the maximum size of the stack
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

int print_top(void) {
    if (top < 0) {
        return ERR_STACK_UNDERFLOW;
    }

    char value[12]; // Buffer to hold the string representation of the integer
    snprintf(value, sizeof(value), "%d", stack[top]); // Convert the top value to a string
    clear_stdout();
    print_stdout(value);
    return ERR_OK;
}

int print_top3(void) {
    if (top < 0) {
        return ERR_STACK_UNDERFLOW;
    }

    return ERR_OK;
}

int clear_stk(void) {
    top = -1; // Reset the top index to indicate that the stack is empty
    return ERR_OK;
}

int dpl_top(void) {
    return ERR_OK;
}

int swap_top(void) {
    return ERR_OK;
}