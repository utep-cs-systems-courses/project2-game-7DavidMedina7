#ifndef switches_included
#define switches_included

/* Defining all the switches */
#define SW_POWEROFF BIT3 /* Poweroff switch is in port p1.3 */
#define SWITCH SW_POWEROFF /* Poweroff switch is in the redboard */
#define SW1 BIT0 /* Switch #1 is in port p2.0 */
#define SW2 BIT1 /* Switch #2 is in port p2.1 */
#define SW3 BIT2 /* Switch #3 is in port p2.2 */
#define SW4 BIT3 /* Switch #4 is in port p2.3 */
#define SWITCHES (SW1 | SW2 | SW3 | SW4) /* Switches #1 - #4 on the greenboard */

void switch_init();
void switchPoweroff_interrupt_handler();
void switch1_interrupt_handler();
void switch2_interrupt_handler();
void switch3_interrupt_handler();
void switch4_interrupt_handler();

extern char switchPoweroff_state_down, switchPoweroff_state_changed,
  switch1_state_down, switch1_state_changed,
  switch2_state_down, switch2_state_changed,
  switch3_state_down, switch3_state_changed,
  switch4_state_down, switch4_state_changed;

#endif 
