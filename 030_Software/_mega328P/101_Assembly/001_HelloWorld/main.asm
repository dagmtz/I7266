.include "m328pdef.inc"

	    .cseg
	    .org 	0x00
	    
		ldi		r16,0xFF		; load 00000001 into register 16
        out     DDRD,r16		; write register 16 to DDRD

loop:	ldi		r16,0b00000001	; load 00000001 into register 16
		out     PORTD,r16		; write register 16 to PORTD

		ldi		r16,0b00000010	; load 00000001 into register 16
		out     PORTD,r16		; write register 16 to PORTD

		rjmp    loop			; stay in infinite loop