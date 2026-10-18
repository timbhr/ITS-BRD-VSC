/**
 * @file stackops.h
 * @author Tim Behrens
 * @brief Header file for stack operations.
 * @date Oktober 2026
 *
 */

 #ifndef STACKOPS_H
 #define STACKOPS_H

/**
 * @brief Puts a value onto the stack.
 *
 * @param value The value to be pushed onto the stack.
 *
 * @retval ERR_OK Success
 * @retval ERR_STACK_OVERFLOW The stack is full
 */
int push(int value);

/**
 * @brief Pops a value from the stack.
 *
 * @param value Pointer to an integer where the popped value will be stored.
 *
 * @retval ERR_OK Success
 * @retval ERR_STACK_UNDERFLOW The stack is empty
 */
int pop(int *value);

/**
 * @brief Prints the top value of the stack, without changing the stack.
 * 
 * @retval ERR_OK Success
 * @retval ERR_STACK_UNDERFLOW The stack is empty
 */
int print_top(void);

/**
 * @brief Print the top 3 values of the stack, without changing the stack.
 * Incase there are fewer than 3 values on the stack, it will print as many as are available. 
 *
 * @retval ERR_OK Success
 * @retval ERR_STACK_UNDERFLOW The stack is empty
 */
int print_top3(void);

/**
 * @brief Clears the stack.
 *
 * @retval ERR_OK Success
 */
int clear_stk(void);

/**
  * @brief Duplicates the top value of the stack.
  *
  * @retval ERR_OK Success
  * @retval ERR_STACK_UNDERFLOW The stack is empty
  * @retval ERR_STACK_OVERFLOW The stack is full
  */
int dpl_top(void);

/**
 * @brief Swaps the top two values of the stack.
 * 
 * @retval ERR_OK Success
 * @retval ERR_STACK_UNDERFLOW The stack has fewer than 2 values
 */
int swap_top(void);

 #endif // STACKOPS_H
 // EOF