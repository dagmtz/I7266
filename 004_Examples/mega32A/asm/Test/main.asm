;
; 000_Playground.asm
;
; Created: 21/09/2024 10:27:24 a. m.
; Author : dagmtz
;

;.include "m32Adef.inc"

.equ	DDRD	= 0x11
.equ	PORTD	= 0x12

; Replace with your application code
Start:
		ldi	R16, 0x80
		out DDRD, R16
		out PORTD, R16
End:	
		rjmp End	
