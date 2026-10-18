/**
 ******************************************************************************
 * @file    main.c
 * @author  Tim Behrens
 * @brief   Main program for the RPN calculator on the ITS-Board.
 * @date    Oktober 2026
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "arithops.h"
#include "display.h"
#include "errorcodes.h"
#include "init.h"
#include "scanner.h"
#include "stackops.h"
#include "token.h"
#include <stdio.h>

int main(void) {
   initITSboard();
   init_display();

   while (1) {
      T_token token = next_token();
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
            clear_stdout();
            break;
         case UNEXPECTED:
         default:
            // TODO
            break;
      }

      if (status != ERR_OK) {
         // TODO
      }
   }
}

// EOF
