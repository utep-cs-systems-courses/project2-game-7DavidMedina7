#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

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
