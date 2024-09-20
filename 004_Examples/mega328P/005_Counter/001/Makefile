CC = avr-gcc
OBJCP = avr-objcopy
AVRDUDE = avrdude
DUDEFLAGS = -p $(TARGET) -c $(PROGRAMMER) -B$(PROGFREQ) -v 
OBJCPFLAGS = -O ihex
TARGET = atmega328p
PROGRAMMER = usbasp
PROGFREQ = 750kHz
CPPFLAGS = 
CFLAGS = -Os
CDEFINES = -D F_CPU=16000000
AFLAGS = 

all: main.hex

debug: main.i main.s main.o main.elf

main.elf: main.c
	$(CC) main.c usart.c -mmcu=$(TARGET) $(CFLAGS) -o main.elf $(CDEFINES)
# 	avr-gcc main.c usart.c -mmcu=atmega328p -Os -o main.elf -D F_CPU=16000000

# main.i: main.c
# 	$(CC) main.c -mmcu=$(TARGET) $(CFLAGS) -E -o main.elf

# main.s: main.c
# 	$(CC) main.c -mmcu=$(TARGET) $(CFLAGS) -S -o main.elf

# main.o: main.c
# 	$(CC) main.c -mmcu=$(TARGET) $(CFLAGS) -c -o main.elf

main.hex: main.elf
	$(OBJCP) $(OBJCPFLAGS) main.elf main.hex
#	avr-objcopy -O ihex main.elf main.hex

upload: main.hex
	sudo $(AVRDUDE) $(DUDEFLAGS) -U flash:w:main.hex 
#	sudo avrdude -p atmega328p -c usbasp -B750kHz -v	

serial: 
	sudo screen /dev/ttyUSB0 115200

clean: 
	rm -f main.elf main.i main.s main.o main.hex
