#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"

void __interrupt_vec(WDT_VECTOR) WDT(){
  static char blink_count = 0;

  if (dim_light_on) {
    dim_light();
  }

  // This is the main interval at which the state machines are advanced
  if(++blink_count == 125){
    if(poweroff_on) {
      poweroff_machine();
    }
      
    if(whistle_down_on) {
      whistle_down();
    }

    else if(play_lavender_town_on) {
      play_lavender_town();
    }

    else if(play_c_major_scale_on) {
      play_c_major_scale();
    }
    blink_count = 0;

    /* Signifies half interval state (C major scale will play faster) */
  } else if(blink_count == 63) {
    if(play_c_major_scale_on) {
      play_c_major_scale();
    }
  } 
}
