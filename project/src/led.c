#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "stateMachines.h"

unsigned char red_on = 0, green_on = 0;
unsigned char led_changed = 0;

static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};

/* Function that will initialize the LEDS */
void led_init()
{
  P1DIR |= LEDS; /* Setting the LEDS as output */
  led_changed = 1;
  led_update();
}

/* Function that will update the LEDS in response to how the machine sets them */
void led_update(){
  char ledFlags = redVal[red_on] | greenVal[green_on];
  P1OUT &= (0xff^LEDS) | ledFlags; /* Clear the bits for off LEDS */
  P1OUT |= ledFlags;
  led_changed = 0; /* Set the bits for on LEDS */
}
