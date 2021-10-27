#include <msp430.h>
#include "switches.h"

/* Handle interupts for port 1 poweroff swtich */
void __interrupt_vec(PORT1_VECTOR) Port_1() {
  if (P1IFG & SW_POWEROFF) {
    P1IFG &= ~SW_POWEROFF;
    switchPoweroff_interrupt_handler();
  }
}
