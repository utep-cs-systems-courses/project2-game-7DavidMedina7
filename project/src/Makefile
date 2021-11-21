# makfile configuration

COMMON_OBJECTS  =

CPU             = msp430g2553

CFLAGS          = -mmcu=${CPU} -I../h

LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)

CC              = msp430-elf-gcc

AS              = msp430-elf-as

all: button.elf assembly.elf

#additional rules for files

button.elf: ${COMMON_OBJECTS} dim_light.o p1_interrupt_handler.o p2_interrupt_handler.o led.o switches.o buttonMain.o stateMachines.o wdInterruptHandler.o buzzer.o ../lib/libTimer.a

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

assembly.elf: ${COMMON_OBJECTS} p1_interrupt_handler.o p2_interrupt_handler.o led.o switches.o buttonMain.o stateMachines.o wdInterruptHandler.o buzzer.o dim_light_assy.o ../lib/libTimer.a

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: button.elf
	msp430loader.sh button.elf

load-a: assembly.elf
	msp430loader.sh assembly.elf

clean:
	rm -f *.o *.elf

led.o: led.c led.h

dim_light_assy.o: stateMachines.h buzzer.h led.h switches.h

dim_light.o: stateMachines.h

wdInterruptHandler.o: stateMachines.h

stateMachines.o: led.h stateMachines.h

buzzer.c: buzzer.h
