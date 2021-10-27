# David Medina - Computer Architecture: Lab 2

## Description
This particular project involves the implementation of a simple toy using that
of the MSP430 board. The toy utilizes switches, timers, and interrupts to
enable the selection of respective state machines all by which take on a
different task.

## Functionality

Poweroff switch (located at P1.3 on the red board): Turns off all current LEDs
that are on and shuts down the buzzer.

S1 (located at P2.0): Alternates between red and green LEDs and plays the
buzzer in a decrementing manner by reducing the frequency by 100 hertz (Hz).

S2 (located at P2.1): Dims the red LED.

S3 (located at P2.2): Plays the C major scale up and down while alternating
between the red and green LEDs.

S4 (located at P2.3): Plays Lavender Town intro song cycle from Pokemon.

## How to use
1) Ensure to have placed the green board correctly in the MSP430 to map out the
switches correctly.

2) Type *make* under the src directory to initilize the first use of the
project.

3) Type *make load* under the src directoy to upload the program onto the MSP430.
