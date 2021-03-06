#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

/* These variables resemble the status of each state machine */
unsigned char poweroff_on = 0;
unsigned char whistle_down_on = 0;
unsigned char dim_light_on = 0;
unsigned char play_c_major_scale_on = 0;
unsigned char play_lavender_town_on = 0;

/* This function will keep track of which state machine is currently
   on and in progress. Only 1 state machine can be on at a time.
 */
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

/* This state machine plays the buzzer and progressively increases the frequency
   creating a lower sound with each iteration. At the same time, the red and green
   LEDS are alternating. This will be mapped out to switch P2.0 on the green board.
 */
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


/* Variables that will help the dim_light method to keep track of the states */
int SecCnter = 0;
int DimCnter = 4;
int SecCnter2 = 0;

/* This particular method will dim both the green and red LEDS. 
   Specifically, the red LED will progressively get brighter while the green
   LED will get dimmer. This will be mapped out to switch P2.1 on the green board.
*/
/*
void dim_light()
{
  buzzer_set_period(0);
  SecCnter2++;
  if(SecCnter2 >= 256) {
    SecCnter2 = 0;
    if(DimCnter >= 4) {
      DimCnter = 0;
    } else {
      DimCnter++;
    }
  }

  if (SecCnter >= 4) {
    SecCnter = 0;
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
  } else {
    if (DimCnter >= SecCnter) {
      SecCnter++;
    } else {
      P1OUT &= ~LED_RED;
      P1OUT |= LED_GREEN;
      SecCnter++;
    }
 }  
}
*/
/* This state machine plays the major C scale forwards and back 
   infinitely while the green and red lights alternate mapped
   to switch p2.2 on the green board.
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
   mapped to switch P2.3 on the green board.
 */
void play_lavender_town()
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
