;
; 	File:                   main.c
;   Author:                 Daniel Martinez
;                           dagmtzs@gmail.com
;
;   Created: 				21/09/2024 10:27:24 a. m.
;   Target:                 ATmega32A
;   Description:            This program is a "Hello World!" implementation for the 
;                           ATmega32A. It turns on an LED connected to PORTD7.
;

;.include "m32Adef.inc"

.equ	DDRD	= 0x11
.equ	PORTD	= 0x12

Start:
		ldi	R16, 0x80
		out DDRD, R16
		out PORTD, R16
End:	
		rjmp End	
