//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"

/* Defining all the LEDS */
#define LED_RED BIT6
#define LED_GREEN BIT0
#define LEDS (BIT0 | BIT6)

/* Defining all the swithces */
#define SW_POWEROFF BIT3
#define SWITCH SW_POWEROFF
#define SW_S1 BIT0
#define SW_S2 BIT1
#define SW_S3 BIT2
#define SW_S4 BIT3
#define SWITCHES (SW_S1 | SW_S2 | SW_S3 | SW_S4)

/* Function to initialize the buzzer */
void buzzer_init()
{
  timerAUpmode(); /* Used to drive speaker */
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; /* Enable output to speaker (P2.6) */
}

/* Function to set the buzzer period */
void buzzer_set_period(short cycles)
{
  CCR0 = cycles;
  CCR1 = cycles >> 1;
}

int main(void) {

  configureClocks(); /* setup master oscillator, CPU & perpheral clocks */
  
  P1DIR |= LEDS; /*  Configuring the LED outputs */
  P1OUT &= ~LEDS; /* LEDS initially off */

  /* SETTING UP POWEROFF SWTICH ON THE RED BOARD */
  P1REN |= SWITCH;
  P1IE |= SWITCH;
  P1OUT |= SWITCH;
  P1DIR &= ~SWITCH;
  
  /* SETTING UP SWITCHES ON THE GREENBOARD */
  P2REN |= SWITCHES; /* Enables resistors for switches */
  P2IE |= SWITCHES; /* Enables interrupts from switches */
  P2OUT |= SWITCHES; /* Pull-ups for switches */
  P2DIR &= ~SWITCHES; /* Set switches' bits for input */

  /* INITIALIZING THE BUZZER */
  buzzer_init();
  
  //enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}

void switch_interrupt_handler()
{
  char p1_in_read = P1IN; /* Read value for RED board switch */
  char p2_in_read = P2IN; /* Read value for GREEN board swtiches */

  /* TRANSITIONS FOR SWITCH IN THE RED BOARD */
  P1IES |= (p1_in_read & SWITCH); /* If switch is  up, check for transition to sense down */
  P1IES &= (p1_in_read | ~SWITCH); /* If switch is down, check for transition to sense up */
  
  /* TRANSITIONS FOR SWITCHES IN THE GREENBOARD */
  P2IES |= (p2_in_read & SWITCHES); /* If swtich is up, check for transition to sense down */
  P2IES &= (p2_in_read | ~SWITCHES); /* If switch is down, check for transition to sense up */

  /* If switch S1 is unpressed */
  if (p2_in_read & SW_S1) {
    /* DO NOTHING - Not pressed */
  } else {
    P1OUT ^= LED_GREEN; /* Toggle green LED */
  }

  /* If switch S2 is unpressed */
  if (p2_in_read & SW_S2) {
    /* DO NOTHING - Not pressed */
  } else {
    P1OUT ^= LED_RED; /* Toggle red LED */
  }

  /* If switch S3 is unpressed */ 
  if (p2_in_read & SW_S3) {
    /* DO NOTHING - Not pressed */ 
  } else {
    P1OUT ^= LEDS; /* Toggle both LEDs */
  }

  /* If switch S4 is unpressed */
  if (p2_in_read & SW_S4) {
    /* DO NOTHING - Not pressed */
  } else {
    // P1OUT &= ~LEDS; /* Toggle LEDs off */
    buzzer_set_period(4000); /* Start buzzing! */
  }

  /* If switch SW_POWEROFF is unpressed */
  if (p1_in_read & SW_POWEROFF) {
    /* DO NOTHING - Not pressed */
  } else {
    /* POWEROFF/RESET ALL OPERATIONS */
    P1OUT &= ~LEDS; /* Toggle LEDs off */
    buzzer_set_period(0); /* Stop buzzing! */
  }
}

void __interrupt_vec(PORT1_VECTOR) Port_1() {
  if (P1IFG & SWITCH) {
    P1IFG &= ~SWITCH;
    switch_interrupt_handler();
  }
}

void __interrupt_vec(PORT2_VECTOR) Port_2() { 
  if (P2IFG & SWITCHES) {
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}
