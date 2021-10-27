#include <msp430.h>
#include "switches.h"

/* Handle interrupts for switches #1 - #4 on port 2 */
void __interrupt_vec(PORT2_VECTOR) Port_2(){

  /* Call the interrupt handler when flag is changed in a switch */
  if (P2IFG & SW1) {
    P2IFG &= ~SW1;
    switch1_interrupt_handler();

  } else if (P2IFG & SW2) {
    P2IFG &= ~SW2;
    switch2_interrupt_handler();

  } else if (P2IFG & SW3) {
    P2IFG &= ~SW3;
    switch3_interrupt_handler();

  } else if (P2IFG & SW4) {
    P2IFG &= ~SW4;
    switch4_interrupt_handler();
  }
}
