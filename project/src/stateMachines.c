#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

// all below except lights_on resemble the status of a machine. ex: siren_on = 1 -> siren machine is on
unsigned char poweroff_on = 0;
unsigned char whistle_down_on = 0;
unsigned char dim_light_on = 0;
unsigned char play_c_major_scale_on = 0;
unsigned char play_lavender_town_on = 0;



// uses the most recently pushed button as an indicator for which machine to turn on. All others are turned off

void select_machine()
{
  if(switchPoweroff_state_down) {
    poweroff_on = 1;
    whistle_down_on = 0;
    dim_light_on = 0;
    play_c_major_scale_on = 0;
    play_lavender_town_on = 0;
  }
    
  if(switch1_state_down){
    poweroff_on = 0;
    whistle_down_on = 1;
    dim_light_on = 0;
    play_c_major_scale_on = 0;
    play_lavender_town_on = 0;

  } else if(switch2_state_down){
    poweroff_on = 0;
    whistle_down_on = 0;
    dim_light_on = 1;
    play_c_major_scale_on = 0;
    play_lavender_town_on = 0;

  } else if(switch3_state_down){
    poweroff_on = 0;
    whistle_down_on = 0;
    dim_light_on = 0;
    play_c_major_scale_on = 1;
    play_lavender_town_on = 0;

  } else if(switch4_state_down){
    poweroff_on = 0;
    whistle_down_on = 0;
    dim_light_on = 0;
    play_c_major_scale_on = 0;
    play_lavender_town_on = 1;
  }
}

/* These functions will signal if either LED is on or off */
void turn_red_on()
{
  red_on = 1;
}

void turn_green_on()
{
  green_on = 1;
}

void turn_red_off()
{
  red_on = 0;
}

void turn_green_off()
{
  green_on = 0;
}

/* These functions are the states of the machines and what each one will do. */

/* This particular state machine will power off all the LEDS 
   and shut down the buzzer. This will be mapped out to
   switch P1.3 on the red board (SW_POWEROFF).
*/
void poweroff_machine()
{
  turn_red_off();
  turn_green_off();
  buzzer_set_period(0);
  led_changed = 1;
  led_update();
}

void whistle_down()
{
  static enum {R=0, G=1} color = G;
  static int period = 500;
  switch (color) {
  case R: turn_red_on(); turn_green_off(); period = period + 100; buzzer_set_period(period); color = G; break;
  case G: turn_red_off(); turn_green_on(); period = period + 100; buzzer_set_period(period); color = R; break;
  }
  led_changed = 1;
  led_update();
}

void greenControl(int on)
{
  if (on) {
    P1OUT |= LED_RED;
  } else {
    P1OUT &= ~LED_RED;
  }
}

static int blinkLimit = 5;
void blinkUpdate() // called every 1/250s to blink with duty cycle 1/blinkLimit
{
  static int blinkCount = 0; // state var representing blink state
  blinkCount ++;
  if (blinkCount >= blinkLimit) {
    blinkCount = 0;
    greenControl(1);
    //turn_red_off();
    //turn_green_on();
    //led_changed = 1;
    //led_update();
  } else
    greenControl(0);
    //turn_red_on();
  //turn_green_off();
    //led_changed = 1;
    //led_update();
}

void oncePerSecond() // repeatedly start bright and gradually lower duty cycle, one step/sec
{
  blinkLimit ++;  // reduce duty cycle
  if (blinkLimit >= 8)  // but don't let duty cycle go below 1/7.
    blinkLimit = 0;
}

void secondUpdate()
{
  static int secondCount = 0;
  secondCount++;
  if (secondCount >= 125) { // Once each second
    secondCount = 0;
    oncePerSecond();
  }
}

void dim_light()
{
  buzzer_set_period(0);
  static char dim_state = 0;
  switch (dim_state) {
  case 0: blinkUpdate(); secondUpdate(); dim_state = 1; break;
  case 1: blinkUpdate(); secondUpdate(); dim_state = 2; break;
  case 2: blinkUpdate(); secondUpdate(); dim_state = 3; break;
  case 3: dim_state = 0; break;
  }
  //buzzer_set_period(0);
  //blinkUpdate();
  //secondUpdate();
}

/* This state machine plays the major C scale forwards and back 
   infinitely while the green and red lights alternate mapped
   to switch #3 on the green board.
 */
void play_c_major_scale()
{
  static int period = 1046.50;
  static char scale_state = 0;

  switch (scale_state) {
    // C6
  case 0: turn_green_on(); turn_red_off(); period = 1046.50; scale_state = 1; break;

    // D6
  case 1: turn_green_off(); turn_red_on(); period = 1174.66; scale_state = 2; break;

    // E6
  case 2: turn_green_on(); turn_red_off(); period = 1318.51; scale_state = 3; break;

    // F6
  case 3: turn_green_off(); turn_red_on(); period = 1396.91; scale_state = 4; break;

    // G6
  case 4: turn_green_on(); turn_red_off(); period = 1567.98; scale_state = 5; break;

    // A6
  case 5: turn_green_off(); turn_red_on(); period = 1760; scale_state = 6; break;

    // B6
  case 6: turn_green_on(); turn_red_off(); period = 1975.53; scale_state = 7; break;

    // C7
  case 7: turn_green_off(); turn_red_on(); period = 2093; scale_state = 8; break;

    // B6
  case 8: turn_green_on(); turn_red_off(); period = 1975.53; scale_state = 9; break;

    // A6
  case 9: turn_green_off(); turn_red_on(); period = 1760; scale_state = 10; break;

    // G6
  case 10: turn_green_on(); turn_red_off(); period = 1567.98; scale_state = 11; break;

    // F6
  case 11: turn_green_off(); turn_red_on(); period = 1396.91; scale_state = 12; break;

    // E6
  case 12: turn_green_on(); turn_red_off(); period = 1318.51; scale_state = 13; break;

    // D6
  case 13: turn_green_off(); turn_red_on(); period = 1174.66; scale_state = 14; break;

    // Back to the top
  case 14: scale_state = 0; break;
  }

  buzzer_set_period(period);
  led_changed = 1;
  led_update();
}

/* This state machine plays the music loop of Lavender Town from Pokemon
   mapped to switch #4 on the green board.
 */
void play_lavender_town() // machine that does the same as the one above, with the exception that the lights move toward the right
{
  turn_green_off();
  turn_red_off();
  led_changed = 1;
  led_update();
  
  static int period = 1046.50;
  static char song_state = 0;
  
  switch (song_state) {
    // C6
  case 0: period = 1046.50; song_state = 1; break;

    // G6
  case 1: period = 1567.98; song_state = 2; break;

    // B6
  case 2: period = 1975.53; song_state = 3; break;

    // F#6
  case 3: period = 1479.98; song_state = 0; break;
  }

  buzzer_set_period(period);
}
