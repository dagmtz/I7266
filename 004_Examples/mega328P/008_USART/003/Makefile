CC = avr-gcc
OBJCP = avr-objcopy
AVRDUDE = avrdude
DUDEFLAGS = -p $(TARGET) -c $(PROGRAMMER) -B$(PROGFREQ) -v 
OBJCPFLAGS = -O ihex
TARGET = atmega328p
PROGRAMMER = usbasp
PROGFREQ = 750kHz
CPPFLAGS = 
CFLAGS = -g -Wall -Os
CDEFINES = -DF_CPU=16000000 -DBAUD_RATE=$(BAUDRATE)
AFLAGS = 
BAUDRATE = 19200

all: main.hex

debug: main.i main.s main.o main.elf

main.elf: main.o usart.o
	$(CC) -mmcu=$(TARGET) $(CFLAGS) $(CDEFINES) -o main.elf main.o usart.o

main.i: main.c
	$(CC) main.c -mmcu=$(TARGET) $(CFLAGS) -E -o main.i

main.s: main.c
	$(CC) main.c -mmcu=$(TARGET) $(CFLAGS) -S -o main.s

main.o: main.c
	$(CC) -mmcu=$(TARGET) $(CFLAGS) $(CDEFINES) -c main.c

usart.o: usart/usart.c usart/usart.h
	$(CC) -mmcu=$(TARGET) $(CFLAGS) $(CDEFINES) -c usart/usart.c

main.hex: main.elf
	$(OBJCP) $(OBJCPFLAGS) main.elf main.hex

upload: main.hex
	sudo $(AVRDUDE) $(DUDEFLAGS) -U flash:w:main.hex 

serial: 
	sudo screen /dev/ttyUSB0 $(BAUDRATE)

clean: 
	rm -f *.elf *.i *.o *.hex
