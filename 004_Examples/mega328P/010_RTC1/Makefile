CC=avr-gcc
OBJCP=avr-objcopy
AVRDUDE=avrdude
DUDEFLAGS=-p $(TARGET) -c $(PROGRAMMER) -B$(PROGFREQ) -v 
OBJCPFLAGS=-O ihex
TARGET=atmega328p
PROGRAMMER=usbasp
PROGFREQ=750kHz
CPPFLAGS=
CFLAGS=-g -Wall -Os $(CDEFINES)
CDEFINES=-DF_CPU=16000000 -DBAUD_RATE=$(BAUDRATE)
LDFLAGS=
BAUDRATE=9600
IDIR=include
USBDEV=/dev/ttyUSB0

all: main.hex

# debug: main.i main.s main.o main.elf

main.hex: main.elf
	$(OBJCP) $(OBJCPFLAGS) $< $@

main.elf: main.o usart.o i2c.o ds3231.o
	$(CC) -mmcu=$(TARGET) $(CFLAGS) -o $@ $^

# main.i: main.c
# 	$(CC) main.c -mmcu=$(TARGET) $(CFLAGS) -E -o main.i

# main.s: main.c
# 	$(CC) main.c -mmcu=$(TARGET) $(CFLAGS) -S -o main.s

main.o: main.c
	$(CC) -mmcu=$(TARGET) $(CFLAGS) -c $<

usart.o: usart.c includes/usart.h
	$(CC) -mmcu=$(TARGET) $(CFLAGS) -c $<

i2c.o: i2c.c includes/i2c.h
	$(CC) -mmcu=$(TARGET) $(CFLAGS) -c $<

ds3231.o: ds3231.c includes/ds3231.h
	$(CC) -mmcu=$(TARGET) $(CFLAGS) -c $<

upload: main.hex
	sudo $(AVRDUDE) $(DUDEFLAGS) -U flash:w:$< 

serial: 
	sudo screen $(USBDEV) $(BAUDRATE)

clean: 
	rm -f *.o main.elf main.hex

