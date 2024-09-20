CC = avr-gcc
OBJCP = avr-objcopy
AVRDUDE = avrdude
DUDEFLAGS = -p $(TARGET) -c $(PROGRAMMER) -B$(PROGFREQ) -v 
OBJCPFLAGS = -O ihex
TARGET = atmega328p
PROGRAMMER = usbasp
PROGFREQ = 750kHz
CPPFLAGS = 
#CFLAGS = -Os
AFLAGS = 

all: main.hex

debug: main.i main.s main.o main.elf

main.elf: main.c
	$(CC) main.c -mmcu=$(TARGET) $(CFLAGS) -o main.elf

main.i: main.c
	$(CC) main.c -mmcu=$(TARGET) $(CFLAGS) -E -o main.elf

main.s: main.c
	$(CC) main.c -mmcu=$(TARGET) $(CFLAGS) -S -o main.elf

main.o: main.c
	$(CC) main.c -mmcu=$(TARGET) $(CFLAGS) -c -o main.elf

main.hex: main.elf
	$(OBJCP) $(OBJCPFLAGS) main.elf main.hex

upload: main.hex
	sudo $(AVRDUDE) $(DUDEFLAGS) -U flash:w:main.hex 

clean: 
	rm -f main.elf main.i main.s main.o main.hex
