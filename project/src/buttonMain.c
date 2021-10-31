#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

void main(void)
{
  /* Initializing all necessary components */
  configureClocks();
  buzzer_init();
  switch_init();
  led_init();
  enableWDTInterrupts();
  
  or_sr(0x18);  // CPU off, GIE on
} 
