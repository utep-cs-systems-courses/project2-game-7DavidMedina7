# makfile configuration
COMMON_OBJECTS  = main.o  # Wdinterrupthandler.o 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Ih
LDFLAGS		= -L/opt/ti/msp430_gcc/include 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all:
	(cd timerLib && make install)

#additional rules for files
led.elf: ${COMMON_OBJECTS} 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ lib/libTimer.a

load: led.elf
	msp430loader.sh $^

clean:
	#(cd timerLib && make clean)
	rm -f *.o *.elf
	#rm -rf h lib

