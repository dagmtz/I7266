CC = avr-gcc
ASM = avra
OBJCP = avr-objcopy
AVRDUDE = avrdude
ASMFLAGS = -D F_CPU=16000000
DUDEFLAGS = -p $(TARGET) -c $(PROGRAMMER) -B$(PROGFREQ) -v 
OBJCPFLAGS = -O ihex
TARGET = atmega328p
PROGRAMMER = usbasp
PROGFREQ = 750kHz
CPPFLAGS = 
CFLAGS = -Os
AFLAGS = 

all: main.hex

main.map: main.asm
	$(ASM) $(ASMFLAGS) main.asm -m main.map

main.hex: main.asm
	$(ASM) $(ASMFLAGS) main.asm 

upload: main.hex
	sudo $(AVRDUDE) $(DUDEFLAGS) -U flash:w:main.hex 

clean: 
	rm -f main.elf main.i main.o main.hex
