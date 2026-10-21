/**
 ******************************************************************************
 * @file    main.c
 * @author  Tim Behrens, Nishan Khatiwada
 * @brief   Aufgabe 1
 *          Main program for the RPN calculator on the ITS-Board.
 * @date    Oktober 2026
 ******************************************************************************
 */

#include <stdbool.h>
#include "arithops.h"
#include "display.h"
#include "errorcodes.h"
#include "init.h"
#include "scanner.h"
#include "stackops.h"
#include "token.h"

int main(void) {
   initITSboard();
   init_display();

   bool error_mode = false; // Disable error mode at the beginning

   while (1) {
      T_token token = next_token();

      if (error_mode && token.tok != CLEAR) {
         continue; // Ignore all tokens except CLEAR when in error mode
      }
      int status = ERR_OK;

      switch (token.tok) {
         case NUMBER:
            status = push(token.val);
            break;
         case PLUS:
            status = arith_add();
            break;
         case MINUS:
            status = arith_sub();
            break;
         case MULT:
            status = arith_mul();
            break;
         case DIV:
            status = arith_div();
            break;
         case PRT:
            status = print_top();
            break;
         case PRT_ALL:
            status = print_top3();
            break;
         case SWAP:
            status = swap_top();
            break;
         case DOUBLE:
            status = dpl_top();
            break;
         case CLEAR:
            status = clear_stk();
            set_normal_mode();
            error_mode = false; // Exit error mode when CLEAR is pressed
            break;
         case OVERFLOW:
            status = ERR_OVERFLOW_DURING_INPUT;
            break;
         case UNEXPECTED:
         default:
            status = ERR_UNEXPECTED_INPUT;
            break;
      }

      if (status != ERR_OK) {
         set_err_mode();
         error_mode = true; // Enter error mode on any error
         switch (status) {
            case ERR_STACK_OVERFLOW:
               print_stdout("Error: Stack overflow");
               break;
            case ERR_STACK_UNDERFLOW:
               print_stdout("Error: Stack underflow");
               break;
            case ERR_OUT_OF_RANGE:
               print_stdout("Error: Result out of range");
               break;
            case ERR_DIV_BY_0:
               print_stdout("Error: Division by zero");
               break;
            case ERR_OVERFLOW_DURING_INPUT:
               print_stdout("Error: Overflow during input");
               break;
            case ERR_UNEXPECTED_INPUT:
               print_stdout("Error: Unexpected input");
               break;
            default:
               print_stdout("Error: Unknown error");
               break;
         }
      }
   }
}

// EOF
