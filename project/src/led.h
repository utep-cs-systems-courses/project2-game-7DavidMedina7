# include <msp430.h>
#ifndef led_included
#define led_included
#define LED_RED BIT0 /* Red LED in port -> P1.0 */
#define LED_GREEN BIT6 /* Green LED in port -> P1.6 */
#define LEDS (BIT0 | BIT6) /* LEDS are LED_RED or LED_GREEN */

extern unsigned char red_on, green_on;
extern unsigned char led_changed;

void led_init();/* Initialize the LEDs */
void led_update();/* Update LEDs */

/* These will be used as boolean flags to signify the current state of the LEDs */
extern unsigned char leds_changed, green_led_state, red_led_state;

#endif
