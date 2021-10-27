#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"

/* The following variables are boolean flags that will signify the status of a switch
   For instance:
       ~ switch#_state_down = TRUE means --> Switch # has been pressed
       ~ switch#_state_changed = TRUE means --> Swtich # has been enabled
*/
char switchPoweroff_state_down, switchPoweroff_state_changed,
  switch1_state_down, switch1_state_changed,
  switch2_state_down, switch2_state_changed,
  switch3_state_down, switch3_state_changed,
  switch4_state_down, switch4_state_changed;

/* The following methods detect a change in a switch(s) (pressed or unpressed) */
static char switchPoweroff_update_interrupt_sense()
{
  char p1val = P1IN;
  P1IES |= (p1val & SW_POWEROFF);
  P1IES &= (p1val | ~SW_POWEROFF);
  return p1val;
}

static char switch1_update_interrupt_sense()
{
  char p2val = P2IN;
  /* Update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SW1);/* If switch up, sense down */
  P2IES &= (p2val | ~SW1);/* If switch down, sense up */
  return p2val;
}

static char switch2_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SW2);
  P2IES &= (p2val | ~SW2);
  return p2val;
}

static char switch3_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SW3);
  P2IES &= (p2val | ~SW3);
  return p2val;
}

static char switch4_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SW4);
  P2IES &= (p2val | ~SW4);
  return p2val;
}

/* Function that will initialize the swtiches */
void switch_init()
{
  P1REN |= SWITCH;
  P1IE |= SWITCH;
  P1OUT |= SWITCH;
  P1DIR &= ~SWITCH;
  
  P2REN |= SWITCHES; /* Enables resistors for switches */
  P2IE |= SWITCHES; /* Enable interrupts from switches */
  P2OUT |= SWITCHES; /* Pull-ups for switches */
  P2DIR &= ~SWITCHES; /* Set switches' bits for input */

  /* Detect switch presses */
  switchPoweroff_update_interrupt_sense();
  switch1_update_interrupt_sense();
  switch2_update_interrupt_sense();
  switch3_update_interrupt_sense();
  switch4_update_interrupt_sense();
  led_update();
}

/* The following methods check the status of the each button in the state machine,
   selects a state machine sequence to execute, and updates the LEDS if necessary.
*/
void switchPoweroff_interrupt_handler()
{
  char p1val = switchPoweroff_update_interrupt_sense();
  switchPoweroff_state_down = (p1val & SW_POWEROFF) ? 0 : 1;
  switchPoweroff_state_changed = 1;
  select_machine();
  led_update();
}

void switch1_interrupt_handler()
{
  char p2val = switch1_update_interrupt_sense();
  switch1_state_down = (p2val & SW1) ? 0 : 1;
  switch1_state_changed = 1;
  select_machine();
  led_update();
}

void switch2_interrupt_handler()
{
  char p2val = switch2_update_interrupt_sense();
  switch2_state_down = (p2val & SW2) ? 0 : 1;
  switch2_state_changed = 1;
  select_machine();
  led_update();
}

void switch3_interrupt_handler()
{
  char p2val = switch3_update_interrupt_sense();
  switch3_state_down = (p2val & SW3) ? 0 : 1;
  switch3_state_changed = 1;
  select_machine();
  led_update();
}

void switch4_interrupt_handler()
{
  char p2val = switch4_update_interrupt_sense();
  switch4_state_down = (p2val & SW4) ? 0 : 1;
  switch4_state_changed = 1;
  select_machine();
  led_update();
}
